#ifndef DELIMITER___
#define DELIMITER___

#include"Test.h"
#include"Range.h"

class Delimiter : public Test 
{
protected:
	std::string delimiter_;
public:
	Delimiter( std::string );
	std::string Get();
	virtual void Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual Delimiter* Clone() const;
	virtual ~Delimiter();
};

#endif