#ifndef REG_EX___
#define REG_EX___

#include "Test.h"
#include "ConstStringSet.h"

class Terminal
{
	std::string regex_;
	ConstStringSet* css_;
	void add_to_css_by_escaped_char(char _ch)
	{
		if (_ch == 's')
		{
			css_->Add(' ');
			css_->Add('\t');
			css_->Add('\n');
		}
		else if (_ch == 'S')
		{
			for (int i = 0; i < 256; i++)
			{
				if (i != ' ' && i != '\t' && i != '\n')
				{
					css_->Add(i);
				}
			}
		}
		else if (_ch == 'd')
		{
			for (char i = '0'; i <= '9'; i++)
			{
				css_->Add(i);
			}
		}
		else if (_ch == 'D')
		{
			for (int i = 0; i < 256; i++)
			{
				if (i < '0' || i > '9')
				{
					css_->Add(i);
				}
			}
		}
		else if (_ch == 'w')
		{
			for (char i = 'a'; i <= 'z'; i++)
			{
				css_->Add(i);
			}
			for (char i = 'A'; i <= 'Z'; i++)
			{
				css_->Add(i);
			}
			for (char i = '0'; i <= '9'; i++)
			{
				css_->Add(i);
			}
		}
		else if (_ch == 'W')
		{
			for (int i = 0; i < 256; i++)
			{
				if ((i < '0' || i > '9') && (i < 'a' || i > 'z') && (i < 'A' || i > 'Z'))
				{
					css_->Add(i);
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
		for (int i = 1; i < regex_.size() - 3; i++)
		{
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
							css_->Add(GetEscapedCharByString(temp));
						}
						else if (!isalpha(regex_[i]))
						{
							css_->Add(regex_[i]);
						}
						else
						{
							add_to_css_by_escaped_char(regex_[i]);
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
			if (regex_[i + 1] == '-')
			{
				for (char j = regex_[i]; j <= regex_[i + 2]; j++)
				{
					css_->Add(j);
				}
				i += 2;
			}
			else if (regex_[i] != '\\')
			{
				css_->Add(regex_[i]);
			}
			else
			{
				backslash = true;
			}
		}
		if (regex_[regex_.size() - 3] != '-')
		{
			if (regex_[regex_.size() - 3] != '\\')
			{
				css_->Add(regex_[regex_.size() - 3]);
				css_->Add(regex_[regex_.size() - 2]);
			}
			else
			{
				if (!isalpha(regex_[regex_.size() - 2]))
				{
					css_->Add(regex_[regex_.size() - 2]);
				}
				else
				{
					add_to_css_by_escaped_char(regex_[regex_.size() - 2]);
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

class RegEx : public Test
{
protected:
	
	struct Node
	{
		std::map<std::string, Node*> neighbors_;
	};
	std::string regex_;
	std::string current_string_;
	Node* root;

	void regex_parsing(Node*, std::string);
public:

	RegEx(const std::string&);
	virtual void Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual RegEx* Clone() const;
	virtual ~RegEx();
};

#endif