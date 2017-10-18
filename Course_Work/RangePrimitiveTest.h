#ifndef RANGE_PRIMITIVE_TEST___
#define RANGE_PRIMITIVE_TEST___

#include"PrimitiveTest.h"
#include"Range.h"
#include"ConstPrimitiveTest.h"

template< typename T >
class RangePrimitiveTest : public PrimitiveTest<T>
{
	Range<T>* range_;
	T current_value_;
public:
	RangePrimitiveTest(Range<T>* _range)
		: range_(_range)
	{
		// this->Generate();
	}
	RangePrimitiveTest(int _start = 0, int _end = 0)
		: range_(new Range<T>(new ConstPrimitiveTest<T>(_start), new ConstPrimitiveTest<T>(_end)))
	{
	}
	virtual T Get()
	{
		THROW(!test_generated_, "Get() must be called after Generate()");
		return current_value_;
	}
	virtual RangePrimitiveTest* Generate()
	{
		test_generated_ = true;
		range_->Generate();
		current_value_ = range_->Get();
		return this;
	}
	virtual void Print(std::ostream& _out = std::cout) const
	{
		THROW(!test_generated_, "Print() must be called after Generate()");
		_out << current_value_;
	};
	virtual RangePrimitiveTest * Clone() const
	{
		return new RangePrimitiveTest(range_);
	}
	
	friend RangePrimitiveTest<T>& operator> (RangePrimitiveTest<T>& _rpt, T _lower)
	{
		*(_rpt.range_) > _lower;
		return _rpt;
	}
	friend RangePrimitiveTest<T>& operator< (T _lower, RangePrimitiveTest<T>& _rpt)
	{
		_lower < *(_rpt.range_);
		return _rpt;
	}
	friend RangePrimitiveTest<T>& operator> (T _greater, RangePrimitiveTest<T>& _rpt)
	{
		_greater > *(_rpt.range_);
		return _rpt;
	}
	friend RangePrimitiveTest<T>& operator< (RangePrimitiveTest<T>& _rpt, T _greater)
	{
		*(_rpt.range_) < _greater;
		return _rpt;
	}
	virtual ~RangePrimitiveTest () {};
};

#endif