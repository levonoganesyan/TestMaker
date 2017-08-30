#include"Test.h"
#include"Range.h"
#include"Array.h"

Array::Array(PrimitiveTest<int>* _array_size_to, std::function<Test*()> _generation_function, std::string _delimiter, std::string _line_breaker)
	: array_size_(_array_size_to), generation_function_(_generation_function), example_(NULL), delimiter_(_delimiter), line_breaker_(_line_breaker)
{
	//std::shared_ptr<Int> s_ptr_io();
	//array_size_ = _array_size_to;
	//std::shared_ptr<Int> _array_size_into(io);
	// this->Generate();
}
Array::Array(PrimitiveTest<int>* _array_size_to, Test* _example, std::string _delimiter, std::string _line_breaker)
	: array_size_(_array_size_to), example_(_example), delimiter_(_delimiter), line_breaker_(_line_breaker)
{
	//std::shared_ptr<Int> s_ptr_io();
	//array_size_ = _array_size_to;
	//std::shared_ptr<Int> _array_size_into(io);
	// this->Generate();
}
void Array::Generate() 
{
	test_generated_ = true;
	array_size_->Generate();
	array_.resize(array_size_->Get());
	for ( int i = 0 ; i < array_size_->Get() ; i++ )
	{
		if (example_ != NULL)
		{
			array_[i] = example_->Clone();
		}
		if (generation_function_)
		{
			array_[i] = generation_function_();
		}
		if (array_[i] == NULL)
		{
			throw std::runtime_error("Array element is not assigned. In function Array::Generate()");
		}
		array_[ i ]->Generate();
	}
}
void Array::Print(std::ostream& _out) const
{
	if (!test_generated_)
	{
		throw std::runtime_error("Print() must be called after Generate() in Array.");
	}
	if (print_size_)
	{
		_out << array_.size() << line_breaker_;
	}
	for (unsigned int i = 0 ; i < array_.size() ; i++ )
	{
		array_[ i ]->Print(_out);
		if ( i != array_.size() - 1 ) 
			_out << delimiter_;
	}
	_out << line_breaker_;
}
Array* Array::Clone() const
{ 
	Array* arr = new Array(array_size_, generation_function_, delimiter_, line_breaker_);
	if (example_ != NULL)
	{
		delete arr;
		arr = new Array(array_size_, example_, delimiter_, line_breaker_);
	}
	arr->print_size_ = print_size_;
	return arr;
}
int Array::Size()
{
	return array_size_->Get();
}
Test* Array::operator[]( int i ) 
{
	return array_ [ i ];
}
void Array::PrintSize(bool _print_size)
{
	print_size_ = _print_size;
}
Array::~Array()
{
	for (unsigned int i = 0; i < array_.size(); i++)
	{
		delete array_[i];
	}
}