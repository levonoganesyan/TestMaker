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
	current_test_ = random_set_[Rand() % (random_set_.size())];
	current_test_->Generate();

	std::ostringstream out;
	current_test_->Print(out);
	result_ = out.str();

	Test::Generate();
	return this;
}

void RandomTestSet::Print(std::ostream & _out) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	_out << result_;
}

RandomTestSet* RandomTestSet::Clone() const
{
	RandomTestSet* set_to_return = new RandomTestSet();
	for (unsigned int i = 0; i < random_set_.size(); i++)
	{
		set_to_return->Add(random_set_[i]);
	}
	set_to_return->Generate();
	set_to_return->postprocess_function_ = postprocess_function_;
	return set_to_return;
}

RandomTestSet::~RandomTestSet()
{
}
