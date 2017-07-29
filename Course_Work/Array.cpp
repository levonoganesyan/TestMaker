#include"Test.h"
#include"Range.h"
#include"Array.h"

Array::Array(PrimitiveTest<int>* _array_size_to, std::function<Test*()> _generation_function, std::string _delimiter, std::string _line_breaker)
	: array_size_(_array_size_to), generation_function_(_generation_function), delimiter_(_delimiter), line_breaker_(_line_breaker)
{
	//std::shared_ptr<Int> s_ptr_io();
	//array_size_ = _array_size_to;
	//std::shared_ptr<Int> _array_size_into(io);
	this->Generate();
}
Array::Array(PrimitiveTest<int>* _array_size_to, Test* _example, std::string _delimiter, std::string _line_breaker)
	: array_size_(_array_size_to), example_(_example), delimiter_(_delimiter), line_breaker_(_line_breaker)
{
	//std::shared_ptr<Int> s_ptr_io();
	//array_size_ = _array_size_to;
	//std::shared_ptr<Int> _array_size_into(io);
	this->Generate();
}
void Array::Generate() 
{
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
	_out << array_.size() << line_breaker_;
	for (unsigned int i = 0 ; i < array_.size() ; i++ )
	{
		array_[ i ]->Print();
		if ( i != array_.size() - 1 ) 
			_out << delimiter_;
	}
	_out << line_breaker_;
}
Array* Array::Clone() const
{ 
	return new Array(array_size_, generation_function_, delimiter_, line_breaker_);
}
Test* Array::operator[]( int i ) 
{
	return array_ [ i ];
}
Array::~Array()
{
	for (unsigned int i = 0; i < array_.size(); i++)
	{
		delete array_[i];
	}
}