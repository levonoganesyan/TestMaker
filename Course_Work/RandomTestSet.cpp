#include "RandomTestSet.h"

RandomTestSet::RandomTestSet()
{
}

RandomTestSet * RandomTestSet::Add(Test * _test)
{
	random_set_.push_back(_test);
	return this;
}

Test * RandomTestSet::Get()
{
	THROW(!test_generated_, "Get() must be called after Generate()");
	return current_test_;
}

RandomTestSet* RandomTestSet::Generate()
{
	test_generated_ = true;
	current_test_ = random_set_[Rand() % (random_set_.size())];
	return this;
}

void RandomTestSet::Print(std::ostream & _out) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	current_test_->Print(_out);
}

RandomTestSet* RandomTestSet::Clone() const
{
	RandomTestSet set_to_return;
	for (unsigned int i = 0; i < random_set_.size(); i++)
	{
		set_to_return.Add(random_set_[i]);
	}
	set_to_return.Generate();
	return new RandomTestSet(set_to_return);
}

RandomTestSet::~RandomTestSet()
{
}