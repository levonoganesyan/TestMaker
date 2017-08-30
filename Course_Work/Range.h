#ifndef RANGE___
#define RANGE___
#pragma warning(disable : 4244)

#include"PrimitiveTest.h"

template <typename T>
class Range : public Test
{
private:
	void generate_helper()
	{
 		begin_->Generate();
 		end_->Generate();
	}
	//long long get_time()
	//{
	//	int lo, hi; 
	//	__asm { 
	//		rdtsc
	//		mov lo, eax
	//		mov hi, edx
	//	}
	//	return (((long long)hi) << 32LL) | lo;	
	//}
protected:
	PrimitiveTest<T> *begin_, *end_;
public:
	Range() : begin_(NULL), end_(NULL) { }
	Range(PrimitiveTest<T>* _begin, PrimitiveTest<T>* _end) : begin_(_begin), end_(_end) {}
	//Range(T _begin) : begin_(_begin), end_(_begin) {}
	T Get() {};
	Range* Clone() const
	{
		Range* range = new Range(begin_, end_);
		return range;
	}
	virtual void Generate()
	{
		generate_helper();
		RangeValidation();
	}
	virtual void Print(std::ostream& _out) const
	{
		_out << "[" << begin_->Get() << ", " << end_->Get() << "]";
	}
	// 	Range* Clone()
// 	{
// 		return new Range(begin_->Clone(), end_->Clone());
// 	}
	void RangeValidation()
	{
		if (begin_ == NULL || end_ == NULL)
		{
			throw std::runtime_error("begin and end must be specified in Range");
		}
		if (begin_->Get() > end_->Get())
		{
			throw std::runtime_error("Begin can't be greater than end in Range");
		}
	}
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
	return Rand() % (end_->Get() - begin_->Get() + 1) + begin_->Get();
}
template<>
int Range<int>::Get() {
	return Rand() % (end_->Get() - begin_->Get() + 1) + begin_->Get();
}
template<>
double Range<double>::Get(){
	double random_double = (double)Rand() / (RAND_MAX*RAND_MAX);
	return ( random_double) * ( end_->Get() - begin_->Get() ) + begin_->Get();
}
template<>
char Range<char>::Get(){
	return (char)(Rand()%( end_->Get() - begin_->Get() + 1 ) + begin_->Get());
}

#endif