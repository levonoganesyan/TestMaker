#ifndef ARRAY___
#define ARRAY___

#include"Test.h"
#include"Range.h"

/// \class Array\n
/// This is for generating sequences of a tests\n
/// Here is an example for Array. You can try it by taking it from Array.h\n
/*!
\code
int main()
{
	PrimitiveTest<int>* number = CreateElement(3, 5);
	PrimitiveTest<char>* character = CreateElement('a', 'z');
	Array* arr = new Array(CreateElement(1, 10), CreateElement(5));
	RandomTestSet* random_set = new RandomTestSet();
	random_set->Add(number)->Add(character)->Add(arr)->Add((new ConstStringSet())->Add("SomeRandomWord"));
	random_set->Generate();
	random_set->Print();
	delete random_set;
	delete arr;
	delete character;
	delete number;
}
\endcode
*/
///
/// The shorter example
///
/*!
\code
int main()
{
	Array* arr = new Array(CreateElement(1, 10), CreateElement(100, 100));
	arr->Generate()->Print();
	delete arr;
}
\endcode
*/
class Array : public Test
{
protected:
	/// \cond
	std::function<Test*()> generation_function_;
	Test* example_;
	PrimitiveTest<int>* array_size_;
	std::vector<Test*> array_;
	std::string delimiter_;
	std::string line_breaker_;
	bool print_size_;
	/// \endcond
public:
	/// If you have a test with dependent variables, 
	/// you need to pass to the Array the way to constracting that Test, 
	/// because Array invokes Generate() function on your example for self-filling, 
	/// and after that all dependencies are broken down.
	/// So you need to pass to the Array the generator function, 
	/// which should return your test. The function can be lambda.
	/// \param _array_size_to - array size
	/// \param _generation_function - generation function
	/// \param _delimiter - delimiter for elements
	/// \param _line_breaker - delimiter after size printing
	Array(PrimitiveTest<int>* _array_size_to, std::function<Test*()> _generation_function, const std::string& _delimiter = " ", const std::string& _line_breaker = "\n");
	/// If you do not have a test with dependent variables, 
	/// you may pass to the Array the example test, 
	/// which will be used for self-filling (through Generate() invocation)
	/// \param _array_size_to - array size
	/// \param _example - test to generation
	/// \param _delimiter - delimiter for elements
	/// \param _line_breaker - delimiter after size printing
	Array(PrimitiveTest<int>* _array_size_to, Test* _example, const std::string& _delimiter = " ", const std::string& _line_breaker = "\n");
	/// Generates and fixes the Array assuming the generation way
	/// \returns this
	virtual Array* Generate();
	virtual void Print(std::ostream& = std::cout) const;
	/// Specifies are you need print the Array size while printing
	/// \param _print_size - specify printing mode
	Array* PrintSize(bool _print_size);
	/// \returns Fixed Array size
	int Size();
	virtual Array* Clone() const;
	virtual ~Array();
	/// Getter by index
	/// \param _index - element index to get
	/// \returns Element with index _index
	Test* operator[](int _index);
};

#endif