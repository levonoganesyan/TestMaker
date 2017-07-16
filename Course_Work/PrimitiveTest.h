#ifndef PRIMITIVE_TEST___
#define PRIMITIVE_TEST___

#include"Test.h"

template< typename T >
class PrimitiveTest : public Test 
{
public:
	// typedef std::shared_ptr<PrimitiveTest<T>> PTOSPtr;
	PrimitiveTest() {};
	virtual T Get() = 0;
	virtual void Generate() = 0;
	virtual void Print(std::ostream& = std::cout) const = 0;
	virtual PrimitiveTest* Clone() const = 0;
	virtual ~PrimitiveTest() {};
};

#endif