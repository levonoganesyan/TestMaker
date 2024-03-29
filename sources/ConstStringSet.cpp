#include"ConstStringSet.h"

ConstStringSet::ConstStringSet()
{
}
ConstStringSet* ConstStringSet::Add(const std::string& _string)
{
	set_.insert(_string);
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
ConstStringSet* ConstStringSet::Generate()
{
	if ( elements.size() == 0 )
		elements.assign(set_.begin(), set_.end());
	current_string_ = elements[ Rand()%( set_.size() ) ];
	result_ = current_string_;
	Test::Generate();
	return this;
}
void ConstStringSet::Print(std::ostream& _out) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	_out << result_;
}
ConstStringSet* ConstStringSet::Clone() const
{
	ConstStringSet* set_to_return = new ConstStringSet();
	for (auto it : set_)
	{
		set_to_return->Add(it);
	}
	set_to_return->Generate();
	set_to_return->postprocess_function_ = postprocess_function_;
	return set_to_return;
}
ConstStringSet::~ConstStringSet() 
{

}