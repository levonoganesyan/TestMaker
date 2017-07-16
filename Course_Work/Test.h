#ifndef TEST___
#define TEST___


#include"Utils.h"

class Test
{
protected:
public:
	// typedef std::shared_ptr<Test> TOSPtr;
	Test() {}
	virtual void Generate() = 0;
	virtual void Print(std::ostream& = std::cout) const = 0;
	virtual Test * Add ( Test * ) 
	{
		throw std::runtime_error("Test: Can't add to a leaf");
	}
	virtual Test* Clone() const = 0;
	virtual ~Test() {}
};

#endif