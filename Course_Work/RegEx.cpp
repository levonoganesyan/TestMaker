#include"Test.h"
#include"Range.h"
#include"RegEx.h"

void RegEx::Terminal::add_to_css_by_escaped_char(std::set<char>& _chars_to_adding, char _ch)
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
		THROW(true, "Incorrect escaped character \\" + _ch);
	}
}
RegEx::Terminal::Terminal(char c)
	: Terminal(std::string(1, c)) 
{ 
}
RegEx::Terminal::Terminal(const std::string& _regex)
	: regex_(_regex)
	, css_(new ConstStringSet())
{
	bool backslash = false;
	bool negation = false;
	std::set<char> chars_to_adding;
	for (unsigned int i = 0; i < regex_.size(); i++)
	{
		if (i == 0 && regex_[i] == '^')
		{
			negation = true;
			continue;
		}
		if (backslash)
		{
			std::string escaped_characters = "tn0\\/.?^$[]{}()|sSdDwW";
			bool character_found = false;
			for (unsigned int j = 0; j < escaped_characters.size(); j++)
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
			THROW(!character_found, "Incorrect escaped character \\" + regex_[i]);
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
		if (i < regex_.size() - 2 && regex_[i + 1] == '-')
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
void RegEx::Terminal::Generate()
{
	css_->Generate();
}
std::string RegEx::Terminal::Get()
{
	return css_->Get();
}
RegEx::Terminal::~Terminal()
{
	delete css_;
}

RegEx::Repeat::Repeat(Expression* _exp, PrimitiveTest<int>* _count)
	: exp_(_exp)
	, count_(_count)
{

}
void RegEx::Repeat::Generate()
{
	count_->Generate();
	exp_->Generate();
}
std::string RegEx::Repeat::Get()
{
	std::string word = "";
	for (int i = 0; i < count_->Get(); i++)
	{
		exp_->Generate();
		word += exp_->Get();
	}
	return word;
}

RegEx::And::And(Expression* _left_exp, Expression* _right_exp)
	: left_exp_(_left_exp)
	, right_exp_(_right_exp)
{
}
void RegEx::And::Generate()
{
	left_exp_->Generate();
	right_exp_->Generate();
}
std::string RegEx::And::Get()
{
	return left_exp_->Get() + right_exp_->Get();
}

RegEx::Or::Or() {}
void RegEx::Or::Add( Expression* _exp) 
{
	subexps_.push_back(_exp);
}
void RegEx::Or::Generate()
{
	current_element_ = (int)(Rand() % subexps_.size());
	subexps_[current_element_]->Generate();
}
std::string RegEx::Or::Get()
{
	return subexps_[current_element_]->Get();
}



RegEx::SymbolType RegEx::get_symbol_type( char c ) const
{
    switch ( c ) {
    case '|':
        // case '&':
        return BinaryOperation;
    case '*':
    case '+':
    case '?':
    case '{':
    case '}':
        return UnaryOperation;
    case '(':
    case ')':
    case '[':
    case ']':
        return SpecialOp;
    default:
        return Term;
    }
}
RegEx::RegEx( const std::string& _regex, int _max_depth) : max_depth_(_max_depth), regex_( _regex )
{
    regex_exp = str_to_expression( 0, (unsigned int)regex_.size() );
}
RegEx::Expression* RegEx::str_to_expression( unsigned int start, unsigned int end )
{
    Or *expression = new Or();
    std::stack<Expression*> expressions;
    for ( unsigned int i = start; i < end; i++ )
    {
        SymbolType type = get_symbol_type( regex_[ i ] );
        if ( regex_[ i ] == '\\' )
        {
			THROW(i + 1 >= end, "Incorrect \\ in the position" + std::to_string(i));
            i++;
            expressions.push( new Terminal( std::string("\\") + regex_[ i ] ) );
        }
        else if ( type == Term  )
        {
            expressions.push( new Terminal( regex_[ i ] ) );
        }
        else if ( type == UnaryOperation )
        {
            unsigned int min_rep = 0, max_rep = max_depth_;
            if ( regex_[ i ] == '*' )
            {
            }
            else if ( regex_[ i ] == '+' )
            {
                min_rep = 1;
            }
            else if ( regex_[ i ] == '?' )
            {
                max_rep = 1;
            }
            else if ( regex_[ i ] == '{' )
            {
                unsigned int closing_bracket = (unsigned int)regex_.find( '}', i + 1 );
				THROW(closing_bracket == std::string::npos, "No closing bracket for bracket " + std::to_string(i));
                std::istringstream iss( regex_.substr(i, closing_bracket - i + 1) );
                char temp_value;
				iss >> temp_value;
				iss >> min_rep;
                iss >> temp_value;
				if (temp_value != '}')
				{
					iss >> max_rep;
					THROW(temp_value != ',', "In figure brackets delimeter must be a comma");
				}
				else
				{
					max_rep = min_rep;
				}
				i = closing_bracket;
            }
			THROW(expressions.empty(), "Expressions must not be empty! At position " + std::to_string(i));
            Expression *current_exp = expressions.top();
            expressions.pop();
            expressions.push( new Repeat( current_exp, new RangePrimitiveTest<int>( min_rep, max_rep ) ) );
        }
        else if ( type == BinaryOperation )
        {
            expression->Add( AndAllExpression( expressions ) );
        }
        else if ( type == SpecialOp )
        {
            if ( regex_[ i ] == '(' )
            {
                unsigned int brackets_count = 1;
                unsigned int last_bracket_pos = i + 1;
                for ( last_bracket_pos; last_bracket_pos < regex_.size() && brackets_count; last_bracket_pos++ ) 
				{
                    if ( regex_[ last_bracket_pos ] == '\\' ) 
					{
                        ++last_bracket_pos;
                    }
                    else if ( regex_[ last_bracket_pos ] == '(' ) 
					{
                        ++brackets_count;
                    }
                    else if ( regex_[ last_bracket_pos ] == ')' ) 
					{
                        --brackets_count;
                    }
                }
				THROW(brackets_count != 0, "Wrong quantity of braceses from " + std::to_string(i));
                expressions.push( str_to_expression( i + 1, last_bracket_pos - 1 ) );
                i = last_bracket_pos - 1;
            }
            if ( regex_[ i ] == '[' )
            {
                Expression *set_exp = nullptr;
                for ( unsigned int j = i + 1; j < regex_.size(); j++ ) 
				{
                    if ( regex_[ j ] == '\\' ) 
					{
                        ++j;
                    }
                    else if ( regex_[ j ] == ']' ) 
					{
                        set_exp = new Terminal( regex_.substr( i + 1, j - i - 1 ) );
                        i = j;
                        break;
                    }
                }
                if ( set_exp ) 
				{
                    expressions.push( set_exp );
                }
                else 
				{
					THROW(true, "Wrong quantity of brackets from " + std::to_string(i));
                }
            }
        }
    }
    if ( !expressions.empty() ) 
	{
        expression->Add( AndAllExpression( expressions ) );
    }
    return expression;
}
RegEx::Expression * RegEx::AndAllExpression( std::stack<RegEx::Expression*>& _exp_stack )
{
	THROW(_exp_stack.empty(), "There are no expressions in stack");
    Expression *result_exp = _exp_stack.top();
    _exp_stack.pop();
    while ( !_exp_stack.empty() ) 
	{
        result_exp = new And( _exp_stack.top(), result_exp );
        _exp_stack.pop();
    }
    return result_exp;
}
RegEx* RegEx::Generate()
{
    test_generated_ = true;
    regex_exp->Generate();
    current_string_ = regex_exp->Get();
	result_ = current_string_;
	return this;
}
std::string RegEx::Get()
{
	THROW(!test_generated_, "Get() must be called after Generate()");
    return current_string_;
}
void RegEx::Print( std::ostream& _out ) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	_out << result_;
}
void RegEx::MaxDepth( int _max_depth)
{
	max_depth_ = _max_depth;
}
RegEx* RegEx::Clone() const
{
    return nullptr;
}
RegEx::~RegEx()
{
}