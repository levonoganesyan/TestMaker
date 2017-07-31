#include"ConstStringSet.h"

ConstStringSet::ConstStringSet()
{
}
ConstStringSet* ConstStringSet::Add( std::string _word )
{
	set_.push_back(_word);
	if ( set_.size() == 1 )
	{
		current_string_ = set_ [ 0 ];
	}
	return this;
} 
std::string ConstStringSet::Get()
{
	return current_string_;
}
void ConstStringSet::Generate()
{
	test_generated_ = true;
	current_string_ = set_ [ Rand()%( set_.size() ) ];
}
void ConstStringSet::Print(std::ostream& _out) const
{
	if (!test_generated_)
	{
		throw std::runtime_error("Print() must be called after Generate() in ConstStringGenerator.");
	}
	_out << current_string_;
}
ConstStringSet* ConstStringSet::Clone() const
{
	ConstStringSet set_to_return;
	for (unsigned int i = 0; i < set_.size(); i++)
	{
		set_to_return.Add(set_[i]);
	}
	set_to_return.Generate();
	return new ConstStringSet( set_to_return );
}
ConstStringSet::~ConstStringSet() 
{

}