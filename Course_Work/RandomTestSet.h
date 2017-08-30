#ifndef RANDOM_SET___
#define RANDOM_SET___


#include"Test.h"

class RandomTestSet : public Test
{
	std::vector<Test*> random_set_;
	Test* current_test_;
public:
	RandomTestSet();
	virtual RandomTestSet* Add(Test*);
	virtual Test* Get();
	virtual void Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual RandomTestSet* Clone() const;
	virtual ~RandomTestSet();
};

#endif