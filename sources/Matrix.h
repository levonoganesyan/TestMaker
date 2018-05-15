#ifndef MATRIX___
#define MATRIX___

#include "PrimitiveTest.h"
/// \class Matrix\n
/// This is for generating Matrix of a tests\n
/// Here is an example for Matrix. You can try it by taking it from Matrix.h\n
/*!
\code
int main()
{
	// Creates square Matrix with size [1,10]x[1,10] (count of columns and rows can be different) with custom IP Test
	Test* ip = new CompositeTest();
	ip->Add(CreateElement(0, 255))->Add(CreateElement('.'))
	->Add(CreateElement(0, 255))->Add(CreateElement('.'))
	->Add(CreateElement(0, 255))->Add(CreateElement('.'))
	->Add(CreateElement(0, 255));
	Matrix* matrix = new Matrix(CreateElement(1, 10), CreateElement(1, 10), ip);
	matrix->Generate()->Print();
	delete matrix;
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
	// Creates square Matrix with size [1,10]x[1,10] (size is always fixed in square case) with [100, 200]
	Matrix* matrix = new Matrix(CreateElement(1, 10), CreateElement(100, 200));
	matrix->Generate()->Print();
	delete matrix;
}
\endcode
*/
class Matrix : public Test
{
protected:
	/// \cond
	std::function<Test*()> generation_function_;
	Test* example_;
	PrimitiveTest<int> *n_, *m_;
	std::vector<std::vector<Test*> > matrix_;
	std::string delimiter_;
	std::string line_breaker_;
	bool print_size_;
	bool print_size_as_square_;
	/// \endcond
public:
	/// If you have a test with dependent variables, 
	/// you need to pass to the Matrix the way to constracting that Test, 
	/// because Matrix invokes Generate() function on your example for self-filling, 
	/// and after that all dependencies are broken down.
	/// So you need to pass to the Array the generator function, 
	/// which should return your test. The function can be lambda.
	/// \param _n - count of rows in matrix
	/// \param _m - count of columns in matrix
	/// \param _generation_function - generation function
	/// \param _delimiter - delimiter for elements
	/// \param _line_breaker - delimiter after size printing
	Matrix(PrimitiveTest<int>* _n, PrimitiveTest<int>* _m, std::function<Test*()> _generation_function, std::string _delimiter = " ", std::string _line_breaker = "\n");
	/// If you do not have a test with dependent variables, 
	/// you may pass to the Matrix the example test, 
	/// which will be used for self-filling (through Generate() invocation)
	/// \param _n - count of rows in matrix
	/// \param _m - count of columns in matrix
	/// \param _example - test to generation
	/// \param _delimiter - delimiter for elements
	/// \param _line_breaker - delimiter after size printing
	Matrix(PrimitiveTest<int>* _n, PrimitiveTest<int>* _m, Test* _example, std::string _delimiter = " ", std::string _line_breaker = "\n");
	/// If you have a test with dependent variables, 
	/// you need to pass to the Matrix the way to constracting that Test, 
	/// because Matrix invokes Generate() function on your example for self-filling, 
	/// and after that all dependencies are broken down.
	/// So you need to pass to the Array the generator function, 
	/// which should return your test. The function can be lambda.
	/// \param _n - count of rows and columns in matrix
	/// \param _generation_function - generation function
	/// \param _delimiter - delimiter for elements
	/// \param _line_breaker - delimiter after size printing
	Matrix(PrimitiveTest<int>* _n, std::function<Test*()> _generation_function, std::string _delimiter = " ", std::string _line_breaker = "\n");
	/// If you do not have a test with dependent variables, 
	/// you may pass to the Matrix the example test, 
	/// which will be used for self-filling (through Generate() invocation)
	/// \param _n - count of rows and columns in matrix
	/// \param _example - test to generation
	/// \param _delimiter - delimiter for elements
	/// \param _line_breaker - delimiter after size printing
	Matrix(PrimitiveTest<int>* _n, Test* _example, std::string _delimiter = " ", std::string _line_breaker = "\n");
	/// Generates and fixes the Matrix assuming the generation way
	/// \returns this
	virtual Matrix* Generate();
	virtual void Print(std::ostream& = std::cout) const;
	/// Specifies are you need print the Matrix size while printing
	/// \param _print_size - specify printing mode
	void PrintSize(bool);
	/// \returns Fixed Matrix size
	std::pair<int, int> Size();
	virtual Matrix* Clone() const;
	virtual ~Matrix();
	/// Getter by index
	/// \param _index - element index to get
	/// \returns Element with index _index
	std::vector<Test*> operator[](int i);
};





#endif