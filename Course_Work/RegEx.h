#ifndef REG_EX___
#define REG_EX___

#include "Test.h"
#include "ConstStringSet.h"
#include "RangePrimitiveTest.h"




class RegEx : public Test
{
protected:
	class Expression
	{
	public:
		virtual void Generate() = 0;
		virtual std::string Get() = 0;
	};
	class Terminal : public Expression
	{
		std::string regex_;
		ConstStringSet* css_;
		void add_to_css_by_escaped_char(std::set<char>& _chars_to_adding, char _ch)
		{
			if (_ch == 's')
			{
				_chars_to_adding.insert(' ');
				_chars_to_adding.insert('\t');
				_chars_to_adding.insert('\n');
			}
			else if (_ch == 'S')
			{
				for (int i = 0; i < 256; i++)
				{
					if (i != ' ' && i != '\t' && i != '\n')
					{
						_chars_to_adding.insert(i);
					}
				}
			}
			else if (_ch == 'd')
			{
				for (char i = '0'; i <= '9'; i++)
				{
					_chars_to_adding.insert(i);
				}
			}
			else if (_ch == 'D')
			{
				for (int i = 0; i < 256; i++)
				{
					if (i < '0' || i > '9')
					{
						_chars_to_adding.insert(i);
					}
				}
			}
			else if (_ch == 'w')
			{
				for (char i = 'a'; i <= 'z'; i++)
				{
					_chars_to_adding.insert(i);
				}
				for (char i = 'A'; i <= 'Z'; i++)
				{
					_chars_to_adding.insert(i);
				}
				for (char i = '0'; i <= '9'; i++)
				{
					_chars_to_adding.insert(i);
				}
			}
			else if (_ch == 'W')
			{
				for (int i = 0; i < 256; i++)
				{
					if ((i < '0' || i > '9') && (i < 'a' || i > 'z') && (i < 'A' || i > 'Z'))
					{
						_chars_to_adding.insert(i);
					}
				}
			}
			else
			{
				throw std::runtime_error((std::string)"Incorrect escaped character \\" + _ch);
			}
		}
	public:
		Terminal(const std::string& _regex)
			: regex_(_regex)
			, css_(new ConstStringSet())
		{
			if (regex_[0] != '[' || regex_.back() != ']' || regex_.size() <= 2 || regex_[regex_.size() - 2] == '\\')
			{
				throw std::logic_error("Terminal regex is incorrect");
			}
			bool backslash = false;
			bool negation = false;
			std::set<char> chars_to_adding;
			for (int i = 1; i < regex_.size() - 1; i++)
			{
				if (i == 1 && regex_[i] == '^')
				{
					negation = true;
					continue;
				}
				if (backslash)
				{
					std::string escaped_characters = "tn0\\/.?^$[]{}()|sSdDwW";
					bool character_found = false;
					for (int j = 0; j < escaped_characters.size(); j++)
					{
						if (regex_[i] == escaped_characters[j])
						{
							std::string temp = "\\";
							temp += regex_[i];
							if (GetEscapedCharByString(temp) != ' ')
							{
								chars_to_adding.insert(GetEscapedCharByString(temp));
							}
							else if (!isalpha(regex_[i]))
							{
								chars_to_adding.insert(regex_[i]);
							}
							else
							{
								add_to_css_by_escaped_char(chars_to_adding, regex_[i]);
							}
							character_found = true;
							break;
						}
					}
					if (!character_found)
					{
						throw std::logic_error("Incorrect escaped character \\" + regex_[i]);
					}
					backslash = false;
					continue;
				}
				if (regex_[i] == '.' && backslash == false)
				{
					for (int ch = 0; ch < 256; ch++)
					{
						css_->Add(ch);
					}
				}
				if (i < regex_.size() - 3 && regex_[i + 1] == '-')
				{
					for (char j = regex_[i]; j <= regex_[i + 2]; j++)
					{
						chars_to_adding.insert(j);
					}
					i += 2;
				}
				else if (regex_[i] != '\\')
				{
					chars_to_adding.insert(regex_[i]);
				}
				else
				{
					backslash = true;
				}
			}
			/*if (regex_[regex_.size() - 3] != '-')
			{
				if (regex_[regex_.size() - 3] != '\\')
				{
					if (regex_[regex_.size() - 2] == '.')
					{
						for (int ch = 0; ch < 256; ch++)
						{
							css_->Add(ch);
						}
					}
					else
					{
						chars_to_adding.insert(regex_[regex_.size() - 3]);
						chars_to_adding.insert(regex_[regex_.size() - 2]);
					}
				}
				else
				{
					if (regex_[regex_.size() - 2] == '.' )
					{
						css_->Add('.');
					}
					if (!isalpha(regex_[regex_.size() - 2]))
					{
						chars_to_adding.insert(regex_[regex_.size() - 2]);
					}
					else
					{
						add_to_css_by_escaped_char(chars_to_adding, regex_[regex_.size() - 2]);
					}
				}
			}*/

			for (int ch = 0; ch < 256; ch++)
			{
				if (negation)
				{
					if (chars_to_adding.find(ch) == chars_to_adding.end())
					{
						css_->Add(ch);
					}
				}
				else
				{
					if (chars_to_adding.find(ch) != chars_to_adding.end())
					{
						css_->Add(ch);
					}
				}
			}

		}
		void Generate()
		{
			css_->Generate();
		}
		std::string Get()
		{
			return css_->Get();
		}
		~Terminal()
		{
			delete css_;
		}
	};
	class Operation : public Expression
	{
	protected:
		std::vector<Expression*> subexps_;
	public:
		virtual void Generate() = 0;
		virtual std::string Get() = 0;
	};
	class Repeat : public Operation
	{
	protected:
		Expression* exp_;
		PrimitiveTest<int>* count_;
	public:
		Repeat(Expression* _exp, PrimitiveTest<int>* _count)
			: exp_(_exp)
			, count_(_count)
		{

		}
		virtual void Generate()
		{
			count_->Generate();
			exp_->Generate();
		}
		virtual std::string Get()
		{
			std::string word = "";
			for (int i = 0; i < count_->Get(); i++)
			{
				exp_->Generate();
				word += exp_->Get();
			}
			return word;
		}
	};
	class And : public Operation
	{
	protected:
		Expression* left_exp_;
		Expression* right_exp_;
	public:
		And(Expression* _left_exp, Expression* _right_exp)
			: left_exp_(_left_exp)
			, right_exp_(_right_exp)
		{
		}
		virtual void Generate()
		{
			left_exp_->Generate();
			right_exp_->Generate();
		}
		virtual std::string Get()
		{
			return left_exp_->Get() + right_exp_->Get();
		}
	};
	class Or : public Operation
	{
	protected:
		std::vector<Expression*> subexps_;
		int current_element_;
	public:
		Or()
		{
		}
		void Add(Expression* _exp)
		{
			subexps_.push_back(_exp);
		}
		virtual void Generate()
		{
			current_element_ = Rand() % subexps_.size();
			subexps_[current_element_]->Generate();
		}
		virtual std::string Get()
		{
			return subexps_[current_element_]->Get();
		}
	};

	std::stack<char> operations_;
	std::stack<Expression*> expressions_;

	std::string regex_;
	std::string current_string_;

	int max_lenght_;

public:

	RegEx(const std::string&, int = 1000);
	virtual void Generate();
	virtual std::string Get();
	virtual void Print(std::ostream& = std::cout) const;
	virtual void MaxLenght(int _max_size);
	virtual RegEx* Clone() const;
	virtual ~RegEx();
};

#endif