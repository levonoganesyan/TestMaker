#ifndef RANGE_PRIMITIVE_TEST___
#define RANGE_PRIMITIVE_TEST___

#include"PrimitiveTest.h"
#include"Range.h"

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
		return current_value_;
	}
	virtual void Generate()
	{
		test_generated_ = true;
		current_value_ = range_->Generate();
	}
	virtual void Print(std::ostream& _out = std::cout) const
	{
		if (!test_generated_)
		{
			throw std::runtime_error("Print() must be called after Generate() in RangePrimitiveTest.");
		}
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