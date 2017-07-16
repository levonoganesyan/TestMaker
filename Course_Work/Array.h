#ifndef ARRAY___
#define ARRAY___

#include"Test.h"
#include"Range.h"

class Array : public Test 
{
protected:
	//Test* example_;
	std::function<Test*()> generation_function_;
	PrimitiveTest<int>* array_size_;
	std::vector<Test*> array_;
	std::string delimiter_;
	std::string line_breaker_;
public:
	// Array( char );
	Array( PrimitiveTest<int>* _array_size_to, std::function<Test*()> _generation_function, std::string _delimiter = " ", std::string _line_breaker = "\n" );
	virtual void Generate();
	virtual void Print(std::ostream& = std::cout) const;
	//virtual void Sort() const;
	virtual Array* Clone() const;
	virtual ~Array();
	Test* operator[]( int i );
};

#endif