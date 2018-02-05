#include"Test.h"
#include"Range.h"
#include"Array.h"

Array::Array(PrimitiveTest<int>* _array_size_to, std::function<Test*()> _generation_function, std::string _delimiter, std::string _line_breaker)
	: array_size_(_array_size_to)
	, generation_function_(_generation_function)
	, example_(nullptr)
	, delimiter_(_delimiter)
	, line_breaker_(_line_breaker)
	, print_size_(true)
{
}
Array::Array(PrimitiveTest<int>* _array_size_to, Test* _example, std::string _delimiter, std::string _line_breaker)
	: array_size_(_array_size_to)
	, generation_function_(nullptr)
	, example_(_example)
	, delimiter_(_delimiter)
	, line_breaker_(_line_breaker)
	, print_size_(true)
{
}
Array* Array::Generate() 
{
	array_size_->Generate();
	for (int i = 0; i < array_.size(); i++)
		delete array_[i];
	int n = array_size_->Get();
	THROW(n <= 0, "Array size must be strongly positive");
	array_.resize(n);
	for ( int i = 0 ; i < n ; i++ )
	{
		if (example_ != nullptr)
		{
			array_[i] = example_->Clone();
		}
		if (generation_function_)
		{
			array_[i] = generation_function_();
		}
		THROW(array_[i] == nullptr, "Array element is not assigned");
		array_[ i ]->Generate();
	}
	{
		std::ostringstream out;
		if (print_size_)
		{
			out << array_.size() << line_breaker_;
		}
		for (unsigned int i = 0; i < array_.size(); i++)
		{
			array_[i]->Print(out);
			if (i != array_.size() - 1)
				out << delimiter_;
		}
		out << line_breaker_;
		result_ = out.str();
	}
	Test::Generate();
	return this;
}
void Array::Print(std::ostream& _out) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	_out << result_;
}
Array* Array::Clone() const
{ 
	Array* array_to_return;
	if (example_ == nullptr)
	{
		array_to_return = new Array(array_size_, generation_function_, delimiter_, line_breaker_);
	}
	else
	{
		array_to_return = new Array(array_size_, example_, delimiter_, line_breaker_);
	}
	array_to_return->print_size_ = print_size_;
	array_to_return->postprocess_function_ = postprocess_function_;
	return array_to_return;
}
int Array::Size()
{
	return array_size_->Get();
}
Test* Array::operator[]( int _index)
{
	return array_ [_index];
}
Array* Array::PrintSize(bool _print_size)
{
	print_size_ = _print_size;
	return this;
}
Array::~Array()
{
	for (unsigned int i = 0; i < array_.size(); i++)
	{
		delete array_[i];
	}
}