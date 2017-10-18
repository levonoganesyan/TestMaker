#include "CompositeTest.h"


CompositeTest::CompositeTest() 
{

}

Test * CompositeTest::Add( Test * _test )
{
	THROW(_test == this, "Can't add itself");
	tests_.push_back(_test->Clone());
	return this;
}
void CompositeTest::Clear()
{
	for (unsigned int i = 0; i < tests_.size(); i++)
		delete tests_[i];
	tests_.clear();
}
CompositeTest* CompositeTest::Generate()
{
	test_generated_ = true;
	for ( unsigned int i = 0 ; i < tests_.size() ; i++ )
		tests_[ i ]->Generate();
	//std::for_each( tests_.begin(), tests_.end(), []( const TOSPtr& testObj ) { testObj->Generate(); } );
	return this;
}
void CompositeTest::Print(std::ostream& _out) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	for ( unsigned int i = 0 ; i < tests_.size() ; i++ )
		tests_[ i ]->Print(_out);
	//std::for_each( tests_.begin(), tests_.end(), []( const TOSPtr& testObj ) { testObj->Print(); } );
}
CompositeTest * CompositeTest::Clone() const 
{
	std::vector<Test *> tests;
	for ( unsigned int i = 0 ; i < tests_.size() ; i++ )
	{
		tests.push_back(tests_[ i ]->Clone());
	}
	CompositeTest* cto = new CompositeTest();
	cto->tests_ = tests;
	return cto;
}
CompositeTest::~CompositeTest() 
{
	Clear();
}