#ifndef ARRAY___
#define ARRAY___

#include"Test.h"
#include"Range.h"

class Array : public Test
{
protected:
	//Test* example_;
	std::function<Test*()> generation_function_;
	Test* example_;
	PrimitiveTest<int>* array_size_;
	std::vector<Test*> array_;
	std::string delimiter_;
	std::string line_breaker_;
public:
	// Array( char );
	Array(PrimitiveTest<int>*, std::function<Test*()>, std::string = " ", std::string = "\n");
	Array(PrimitiveTest<int>*, Test*, std::string = " ", std::string = "\n");
	virtual void Generate();
	virtual void Print(std::ostream& = std::cout) const;
	//virtual void Sort() const;
	virtual Array* Clone() const;
	virtual ~Array();
	Test* operator[](int i);
};

#endif