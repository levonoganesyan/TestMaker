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
	RangePrimitiveTest ( Range<T>* _range )
		: range_(_range)
	{
		this->Generate();
	}
	virtual T Get()
	{
		return current_value_;
	}
	virtual void Generate() 
	{
		current_value_ = range_->Generate();
	}
	virtual void Print(std::ostream& _out = std::cout) const 
	{ 
		_out << current_value_; 
	};
	virtual RangePrimitiveTest * Clone() const
	{
		return new RangePrimitiveTest ( range_ );
	}
	virtual ~RangePrimitiveTest () {};
};

#endif