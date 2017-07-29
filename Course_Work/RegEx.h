#ifndef REG_EX___
#define REG_EX___

#include "Test.h"

class RegEx : public Test
{
protected:
	std::string regex_;
public:

	RegEx();
	virtual void Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual RegEx* Clone() const;
	virtual ~RegEx();
};

#endif