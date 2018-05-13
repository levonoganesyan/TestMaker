#ifndef RANGE_PRIMITIVE_TEST___
#define RANGE_PRIMITIVE_TEST___

#include"PrimitiveTest.h"
#include"Range.h"
#include"ConstPrimitiveTest.h"

/// RangePrimitiveTest\n
/// Class describes a primitive test, that can take in constructor Ranges\n
/// Use this class for numbers with floating edges\n
///
/// An example
///
/*!
\code
int main()
{
	ConstPrimitiveTest<int>* a = new ConstPrimitiveTest<int>(10);
	ConstPrimitiveTest<int>* b = new ConstPrimitiveTest<int>(20);
	Range<int>* r1 = new Range<int>(a, b);
	RangePrimitiveTest<int>* c = new RangePrimitiveTest<int>(r1); // [10, 20]
	Range<int>* r2 = new Range<int>(a, c);
	RangePrimitiveTest<int>* d = new RangePrimitiveTest<int>(r2); // [10, [10, 20]]
	d->Generate()->Print();
	delete a; delete b; delete c; delete d; delete r1; delete r2;
}
\endcode
*/
///
/// A shorter example that did same thing as example above
///
/*!
\code
int main()
{
	CreateElement(CreateElement(10), CreateElement(10, 20))->Generate()->Print();
}
\endcode
*/
template< typename T >
class RangePrimitiveTest : public PrimitiveTest<T>
{
	Range<T>* range_;
	T current_value_;
public:
	/// \note Constructor do not take ownership over Range object
	/// \param _range - range to construct
	RangePrimitiveTest(Range<T>* _range)
		: range_(_range)
	{
	}
	/// There is a more simple way to construct RangePrimitiveTest by passing [start, end] interval.\n
	/// ConstPrimitiveTest and Range creating inside this constructor\n
	/// \note This constructor creates Range, which will be deleted with AddDeleteResponsibility function of Test.\n
	/// \param _start - start of range
	RangePrimitiveTest(int _start = 0, int _end = 0)
		: range_(new Range<T>(new ConstPrimitiveTest<T>(_start), new ConstPrimitiveTest<T>(_end)))
	{
		AddDeleteResponsibility(range_);
	}
	virtual T Get()
	{
		THROW(!test_generated_, "Get() must be called after Generate()");
		return current_value_;
	}
	virtual RangePrimitiveTest* Generate()
	{
		range_->Generate();
		current_value_ = range_->Get();
		result_ = std::to_string(current_value_);
		Test::Generate();
		return this;
	}
	virtual void Print(std::ostream& _out = std::cout) const
	{
		THROW(!test_generated_, "Print() must be called after Generate()");
		_out << result_;
	};
	virtual RangePrimitiveTest * Clone() const
	{
		return new RangePrimitiveTest(range_);
	}
	
	/// \cond
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
	/// \endcond
	virtual ~RangePrimitiveTest () {};
};

#endif