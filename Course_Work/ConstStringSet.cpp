#include"ConstStringSet.h"

ConstStringSet::ConstStringSet()
{
}
ConstStringSet* ConstStringSet::Add(std::string _word)
{
	set_.insert(_word);
	if (set_.size() == 1)
	{
		current_string_ = *set_.begin();
	}
	elements.clear();
	return this;
}
ConstStringSet* ConstStringSet::Add(char _char)
{
	std::string temp = "";
	temp += _char;
	set_.insert(temp);
	if (set_.size() == 1)
	{
		current_string_ = *set_.begin();
	}
	elements.clear();
	return this;
}
std::string ConstStringSet::Get()
{
	THROW(!test_generated_, "Get() must be called after Generate()");
	return current_string_;
}
void ConstStringSet::Generate()
{
	test_generated_ = true;
	if ( elements.size() == 0 )
		elements.assign(set_.begin(), set_.end());
	current_string_ = elements[ Rand()%( set_.size() ) ];
}
void ConstStringSet::Print(std::ostream& _out) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	_out << current_string_;
}
ConstStringSet* ConstStringSet::Clone() const
{
	ConstStringSet set_to_return;
	for (auto it : set_)
	{
		set_to_return.Add(it);
	}
	set_to_return.Generate();
	return new ConstStringSet( set_to_return );
}
ConstStringSet::~ConstStringSet() 
{

}