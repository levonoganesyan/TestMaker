#ifndef COMPOSITE_TEST___
#define COMPOSITE_TEST___

#include "Test.h"

class CompositeTest : public Test
{
protected:
	std::vector<Test *> tests_;
public:

	CompositeTest();
	virtual Test * Add( Test * );
	virtual void Clear();
	virtual CompositeTest* Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual CompositeTest* Clone() const;
	virtual ~CompositeTest();
};

#endif