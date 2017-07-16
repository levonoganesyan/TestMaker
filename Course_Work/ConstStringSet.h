#ifndef CONST_STRING_SET__
#define CONST_STRING_SET__

#include"Test.h"

class ConstStringSet : public Test 
{
protected:
	std::vector<std::string> set_;
	std::string current_string_;
public:
	ConstStringSet();
	ConstStringSet* Add( std::string );
	std::string Get();
	virtual void Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual ConstStringSet* Clone() const;
	virtual ~ConstStringSet();
};

#endif