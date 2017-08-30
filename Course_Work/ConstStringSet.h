#ifndef CONST_STRING_SET__
#define CONST_STRING_SET__

#include"Test.h"

class ConstStringSet : public Test 
{
protected:
	std::set<std::string> set_;
	std::vector<std::string> elements;
	std::string current_string_;
public:
	ConstStringSet();
	virtual ConstStringSet* Add(std::string);
	virtual ConstStringSet* Add( char );
	virtual std::string Get();
	virtual void Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual ConstStringSet* Clone() const;
	virtual ~ConstStringSet();
};

#endif