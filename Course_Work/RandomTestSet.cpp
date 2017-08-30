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
	if (!test_generated_)
	{
		throw std::runtime_error("Get() must be called after Generate() in RandomTestSet.");
	}
	return current_test_;
}

void RandomTestSet::Generate()
{
	test_generated_ = true;
	current_test_ = random_set_[Rand() % (random_set_.size())];
}

void RandomTestSet::Print(std::ostream & _out) const
{
	if (!test_generated_)
	{
		throw std::runtime_error("Print() must be called after Generate() in RandomTestSet.");
	}
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
