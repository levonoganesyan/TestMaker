#include"Test.h"
#include"Range.h"
#include"RegEx.h"

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

RegEx::RegEx( const std::string& _regex, int _max_lenght ) : max_lenght_( _max_lenght ), regex_( _regex )
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
            unsigned int min_rep = 0, max_rep = max_lenght_;
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
                Expression *set_exp = NULL;
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
void RegEx::Generate()
{
    test_generated_ = true;
    regex_exp->Generate();
    current_string_ = regex_exp->Get();
}
std::string RegEx::Get()
{
	THROW(!test_generated_, "Get() must be called after Generate()");
    return current_string_;
}
void RegEx::Print( std::ostream& _out ) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	_out << current_string_;
}
void RegEx::MaxLenght( int _max_lenght )
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