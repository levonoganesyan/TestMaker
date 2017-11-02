#ifndef RANGE___
#define RANGE___
#pragma warning(disable : 4244)

#include"PrimitiveTest.h"

template <typename T>
class Range : public Test
{
private:
	void RangeValidation()
	{
		THROW(begin_ == nullptr || end_ == nullptr, "Begin and end must be specified");
		THROW(begin_->Get() > end_->Get(), "Begin can't be greater than end");
	}
protected:
	PrimitiveTest<T> *begin_, *end_;
public:
	Range() : begin_(nullptr), end_(nullptr) { }
	Range(PrimitiveTest<T>* _begin, PrimitiveTest<T>* _end) : begin_(_begin), end_(_end) {}
	T Get() {};
	Range* Clone() const
	{
		Range* range = new Range(begin_, end_);
		return range;
	}
	virtual Range* Generate()
	{
		test_generated_ = true;
		begin_->Generate();
		end_->Generate();
		RangeValidation();
		result_ = std::string("[") + std::to_string(begin_->Get()) + ", " + std::to_string(end_->Get()) + "]";
		return this;
	}
	virtual void Print(std::ostream& _out) const
	{
		THROW(!test_generated_, "Print() must be called after Generate()");
		_out << result_;
	}
	// 	Range* Clone()
// 	{
// 		return new Range(begin_->Clone(), end_->Clone());
// 	}
	Range<T>& operator= (T _current_value)
	{
		_range.begin_ = new ConstPrimitiveTest<T>(_current_value);
		_range.end_ = new ConstPrimitiveTest<T>(_current_value);
		return _range;
	}
	friend Range<T>& operator> (Range<T>& _range, T _lower)
	{
		_range.begin_ = new ConstPrimitiveTest<T>(_lower);
		return _range;
	}
	friend Range<T>& operator< (T _lower, Range<T>& _range)
	{
		_range.begin_ = new ConstPrimitiveTest<T>(_lower);
		return _range;
	}
	friend Range<T>& operator> (T _greater, Range<T>& _range)
	{
		_range.end_ = new ConstPrimitiveTest<T>(_greater);
		return _range;
	}
	friend Range<T>& operator< (Range<T>& _range, T _greater)
	{
		_range.end_ = new ConstPrimitiveTest<T>(_greater);
		return _range;
	}
};

template<>
long long Range<long long>::Get() {
	THROW(!test_generated_, "Get() must be called after Generate()");
	return Rand() % (end_->Get() - begin_->Get() + 1) + begin_->Get();
}
template<>
int Range<int>::Get() {
	THROW(!test_generated_, "Get() must be called after Generate()");
	return Rand() % (end_->Get() - begin_->Get() + 1) + begin_->Get();
}
template<>
double Range<double>::Get(){
	THROW(!test_generated_, "Get() must be called after Generate()");
	double random_double = (double)Rand() / RNG::Max();
	return ( random_double) * ( end_->Get() - begin_->Get() ) + begin_->Get();
}
template<>
char Range<char>::Get(){
	THROW(!test_generated_, "Get() must be called after Generate()");
	return (char)(Rand()%( end_->Get() - begin_->Get() + 1 ) + begin_->Get());
}

#endif