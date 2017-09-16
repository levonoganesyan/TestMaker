#include"Test.h"
#include"Range.h"
#include"RegEx.h"
std::string ReplaceString(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
RegEx::RegEx(const std::string& _regex, int _max_lenght) : regex_(_regex), max_lenght_(_max_lenght)
{
	bool backslash = false;
	for (int i = 0; i < regex_.size(); i++)
	{
		if (backslash)
		{
			backslash = false;
			Expression* term = new Terminal(std::string("[") + regex_[i] + std::string("]"));
			continue;
		}
		if (regex_[i] == '\\')
		{
			backslash = true;
		}
		else if (regex_[i] == '(')
		{
			operations_.push('(');
		}
		else if (regex_[i] == ')')
		{
			if (operations_.size() == 0 )
			{
				throw std::runtime_error("Closing bracket occurs without opening bracket");
			}

			Or* or_operation = NULL;
			if (expressions_.empty())
			{
				throw std::runtime_error("There shouldn't be empty brackets");
			}
			// or_operation->Add(expressions_.top());
			// expressions_.pop();
			while (operations_.top() != '(')
			{
				if (operations_.size() == 0)
				{
					throw std::runtime_error("Closing bracket occurs without opening bracket");
				}
				char op = operations_.top();
				operations_.pop();
				if (!operations_.empty())
				{
					if (operations_.top() == '(' && op == '&' )
					{
						continue;
					}
				}
				if (op != '|' && op != '&')
				{
					throw std::runtime_error("Is anyone here except Or and And?");
				}
				if (op == '&')
				{
					if (or_operation != NULL)
					{
						expressions_.push(or_operation);
					}
					or_operation = NULL;
					if (expressions_.size() < 2)
					{
						throw std::runtime_error("And must be used on 2 Expressions");
					}
					Expression* first = expressions_.top();
					expressions_.pop();
					Expression* second = expressions_.top();
					expressions_.pop();
					expressions_.push(new And(second, first));

				}
				else if (op == '|')
				{
					if (or_operation == NULL)
						or_operation = new Or();
					or_operation->Add(expressions_.top());
					expressions_.pop();
				}
			}
			operations_.pop();
		}
		else if (regex_[i] == '[')
		{
			int start_point = i++;
			while (regex_[i] != ']' && regex_[i-1] != '\\')
			{
				i++;
				if (regex_.size() == i)
				{
					throw std::runtime_error("There is no closing square bracket");
				}
			}
			int end_point = i;
			Expression* term = new Terminal(regex_.substr(start_point, end_point - start_point + 1));
			expressions_.push(term);
		}
		else if (regex_[i] == '{')
		{
			int start_point = i;
			while (regex_[i] != '}')
			{
				i++;
				if (regex_.size() == i)
				{
					throw std::runtime_error("There is no closing figure bracket");
				}
			}
			int end_point = i;
			std::string repeat_str = regex_.substr(start_point, end_point - start_point + 1);
			std::istringstream iss(repeat_str);
			char temp;
			int start, end;
			iss >> temp;
			iss >> start;
			iss >> temp;
			if (temp != ',')
			{
				throw std::runtime_error("Comma must be used in figure brackets");
			}
			iss >> end;
			iss >> temp;
			/*if (iss.str() != "")
			{
				throw std::runtime_error("Something wrong in figure brackets. Remaining string: " + iss.str());
			}*/
			if (expressions_.empty())
			{
				throw std::runtime_error("There shouldn't be figure brackets in the start");
			}
			RangePrimitiveTest<int>* count = new RangePrimitiveTest<int>(start, end);
			Expression* repeat = new Repeat(expressions_.top(), count);
			expressions_.pop();
			expressions_.push(repeat);
		}
		else if (regex_[i] == '|')
		{
			while (operations_.top() == '&')
			{
				if (expressions_.size() < 2)
				{
					throw std::runtime_error("And must be used on 2 Expressions");
				}
				operations_.pop();
				Expression* first = expressions_.top();
				expressions_.pop();
				Expression* second = expressions_.top();
				expressions_.pop();
				expressions_.push(new And(first, second));
			}
			operations_.push('|');
		}
		else if (regex_[i] == '+')
		{
			RangePrimitiveTest<int>* count = new RangePrimitiveTest<int>(1, max_lenght_);
			Expression* repeat = new Repeat(expressions_.top(), count);
			expressions_.pop();
			expressions_.push(repeat);
		}
		else if (regex_[i] == '*')
		{
			RangePrimitiveTest<int>* count = new RangePrimitiveTest<int>(0, max_lenght_);
			Expression* repeat = new Repeat(expressions_.top(), count);
			expressions_.pop();
			expressions_.push(repeat);
		}
		else if (regex_[i] == '?')
		{
			RangePrimitiveTest<int>* count = new RangePrimitiveTest<int>(0, 1);
			Expression* repeat = new Repeat(expressions_.top(), count);
			expressions_.pop();
			expressions_.push(repeat);
		}
		else
		{
			if ( i != 0 )
				operations_.push('&');
			expressions_.push(new Terminal(std::string("[") + regex_[i] + std::string("]")));
		}
	}
	Expression* first = expressions_.top();
	expressions_.pop();
	while( !expressions_.empty() )
	{
		first = new And(expressions_.top(), first);
		expressions_.pop();
	}
	expressions_.push(first);
	if (expressions_.size() != 1 || operations_.size() != 0)
	{
		throw std::runtime_error("There must be only one element into the regex stack");
	}
}
void RegEx::Generate()
{
	test_generated_ = true;
	expressions_.top()->Generate();
	current_string_ = expressions_.top()->Get();
}
std::string RegEx::Get()
{
	if (!test_generated_)
	{
		throw std::runtime_error("Print() must be called after Generate() in RegEx.");
	}
	return current_string_;
}
void RegEx::Print(std::ostream& _out) const
{
	_out << current_string_;
}
void RegEx::MaxLenght(int _max_lenght)
{
	max_lenght_ = _max_lenght;
}
RegEx* RegEx::Clone() const
{
	return NULL;
}
RegEx::~RegEx()
{
}