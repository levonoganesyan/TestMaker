#ifndef CONST_STRING_SET__
#define CONST_STRING_SET__

#include"Test.h"


/// \class ConstStringSet.\n
/// Must be used when need get random string from set of strings.\n
/// 
class ConstStringSet : public Test 
{
protected:
	std::set<std::string> set_;
	std::vector<std::string> elements;
	std::string current_string_;
public:
	/// Here is an example for ConstStringSet. You can try it by taking it from ConstStringSet.h
	/*!
	\code
	int main()
	{
		ConstStringSet* string_set = new ConstStringSet();
		string_set->Add("one");
		string_set->Add("two");
		string_set->Add("three");
		string_set->Generate()->Print();
		delete string_set;
	}
	\endcode
	*/
	ConstStringSet();
	/// Add function
	/// \param _string - string to add in set
	virtual ConstStringSet* Add(const std::string& _string);
	/// Add function
	/// \param _char - char to add in set
	virtual ConstStringSet* Add(char _char);
	virtual std::string Get();
	virtual ConstStringSet* Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual ConstStringSet* Clone() const;
	virtual ~ConstStringSet();
};

#endif