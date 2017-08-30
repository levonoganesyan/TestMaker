#include"Test.h"
#include"Range.h"
#include"RegEx.h"
std::string ReplaceString(std::string subject, const std::string& search,
	const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
RegEx::RegEx(const std::string& _regex) : regex_(_regex)
{
	
}
void RegEx::regex_parsing(Node* _node, std::string _regex)
{

}
void RegEx::Generate()
{
}
std::string Get()
{
	return " ";
}
void RegEx::Print(std::ostream& _out) const
{
}
RegEx* RegEx::Clone() const
{
	return NULL;
}
RegEx::~RegEx()
{
}