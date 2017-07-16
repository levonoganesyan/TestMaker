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

	current_string_ = set_ [ rand()%( set_.size() ) ];
}
void ConstStringSet::Print(std::ostream& _out) const
{
	_out << current_string_;
}
ConstStringSet* ConstStringSet::Clone() const
{
	ConstStringSet set_to_return;
	for (int i = 0; i < set_.size(); i++)
	{
		set_to_return.Add(set_[i]);
	}
	return new ConstStringSet( set_to_return );
}
ConstStringSet::~ConstStringSet() 
{

}