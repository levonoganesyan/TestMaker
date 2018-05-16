#ifndef REG_EX___
#define REG_EX___

#include "Test.h"
#include "ConstStringSet.h"
#include "RangePrimitiveTest.h"



/// \class RegEx\n
/// This is for generating tests via RegEx\n
/// Here is an example for RegEx. You can try it by taking it from RegEx.h\n
///
/// A short example
///
/*!
\code
int main()
{
	// Generating <= 100 strings with length equals to 100
	RegEx* regex = new RegEx("([a-zA-Z]{100}\n)*", 100);
	regex->Generate()->Print();
	delete regex;
}
\endcode
*/
///
/// Another example
///
/*!
\code
int main()
{
	// Generating something like IP, but without caring about limitations
	RegEx* regex = new RegEx("\\d{3}(\\.\\d{3}){3}", 10);
	regex->Generate()->Print();
	delete regex;
}
\endcode
*/
class RegEx : public Test
{

private:
	/// \cond
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
		void add_to_css_by_escaped_char(std::set<char>& _chars_to_adding, char _ch);
	public:
		Terminal(char c);
		Terminal(const std::string& _regex);
		void Generate();
		std::string Get();
		~Terminal();
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
		Repeat(Expression* _exp, PrimitiveTest<int>* _count);
		virtual void Generate();
		virtual std::string Get();
	};
	class And : public Operation
	{
	protected:
		Expression* left_exp_;
		Expression* right_exp_;
	public:
		And(Expression* _left_exp, Expression* _right_exp);
		virtual void Generate();
		virtual std::string Get();
	};
	class Or : public Operation
	{
	protected:
		std::vector<Expression*> subexps_;
		int current_element_;
	public:
		Or();
		void Add(Expression* _exp);
		virtual void Generate();
		virtual std::string Get();
	};

	enum SymbolType {
		Term,
		BinaryOperation,
		UnaryOperation,
		SpecialOp
	};
	SymbolType get_symbol_type(char c) const;
	Expression* str_to_expression(unsigned int start, unsigned int end);
	Expression* AndAllExpression(std::stack<Expression*>& exp_stack);
    
protected:
	Expression* regex_exp;
	std::string regex_;
	std::string current_string_;

	int max_depth_;
	/// \endcond

public:
	/// If you think that your test case is too simple and you can write a regular expression for it, then this class is for you!\n
	/// This class will parse your expression and generate for you a test that matches this regular expression\n
	/// \param _regex - regex ifself
	/// \param _max_depth - maximal depth for infinite operations like * or +
	/// \n
	/// \note RegEx parses given in constructor expression.
	RegEx(const std::string& _regex, int _max_depth = 1000);
	/// After parsing, there is a simple Expression, which we can use for generation.
	/// Generate() simply invokes the corresponding method in Expression and fix the string, that matches given regex.
	/// \returns this
	virtual RegEx* Generate();

	/// \returns Generated string
	virtual std::string Get();
	virtual void Print(std::ostream& = std::cout) const;
	/// Setter for max depth 
	/// \param _max_depth - maximal depth for infinite operations like * or +
	virtual void MaxDepth(int _max_depth);
	virtual RegEx* Clone() const;
	virtual ~RegEx();
};

#endif