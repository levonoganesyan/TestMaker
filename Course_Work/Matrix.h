#ifndef __MATRIX
#define __MATRIX

#include "PrimitiveTest.h"

class Matrix : public Test
{
protected:
	//Test* example_;
	std::function<Test*()> generation_function_;
	Test* example_;
	PrimitiveTest<int> *n_, *m_;
	std::vector<std::vector<Test*> > matrix_;
	std::string delimiter_;
	std::string line_breaker_;
	bool print_size_;
	bool print_size_as_square_;
public:
	// Matrix( char );
	Matrix(PrimitiveTest<int>* _n, PrimitiveTest<int>* _m, std::function<Test*()> _generation_function, std::string _delimiter = " ", std::string _line_breaker = "\n");
	Matrix(PrimitiveTest<int>* _n, PrimitiveTest<int>* _m, Test* _example, std::string _delimiter = " ", std::string _line_breaker = "\n");
	Matrix(PrimitiveTest<int>* _n, std::function<Test*()> _generation_function, std::string _delimiter = " ", std::string _line_breaker = "\n");
	Matrix(PrimitiveTest<int>* _n, Test* _example, std::string _delimiter = " ", std::string _line_breaker = "\n");
	virtual Matrix* Generate();
	virtual void Print(std::ostream& = std::cout) const;
	void PrintSize(bool);
	std::pair<int, int> Size();
	//virtual void Sort() const;
	virtual Matrix* Clone() const;
	virtual ~Matrix();
	std::vector<Test*> operator[](int i);
};





#endif