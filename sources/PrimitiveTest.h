#ifndef PRIMITIVE_TEST___
#define PRIMITIVE_TEST___

#include"Test.h"

/// PrimitiveTest \n
/// Base class for all primitive types\n
/// Implements the Composite pattern\n
/// About that pattern you can read here: https://en.wikipedia.org/wiki/Composite_pattern \n
template< typename T >
class PrimitiveTest : public Test 
{
public:
	PrimitiveTest() {};
	virtual T Get() = 0;
	virtual PrimitiveTest* Generate() = 0;
	virtual void Print(std::ostream& = std::cout) const = 0;
	virtual PrimitiveTest* Clone() const = 0;
	virtual ~PrimitiveTest() {};
};

#endif