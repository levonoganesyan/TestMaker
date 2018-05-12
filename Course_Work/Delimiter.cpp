#include "Delimiter.h"
Delimiter::Delimiter(char _delimiter)
	: delimiter_(1, _delimiter)
{
}
Delimiter::Delimiter(const std::string& _delimiter)
	: delimiter_(_delimiter)
{
}
std::string Delimiter::Get()
{
	return delimiter_;
}
Delimiter* Delimiter::Generate()
{
	result_ = delimiter_;
	Test::Generate();
	return this;
}
void Delimiter::Print(std::ostream& _out) const
{
	_out << result_;
}
Delimiter* Delimiter::Clone() const
{
	return new Delimiter(delimiter_);
}
Delimiter::~Delimiter() 
{

}