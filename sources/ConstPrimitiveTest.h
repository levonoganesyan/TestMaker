#ifndef CONST_PRIMITIVE_TEST___
#define CONST_PRIMITIVE_TEST___

#include"PrimitiveTest.h"


/// \class ConstPrimitiveTest\n
/// Class that describes constants in library context\n
template< typename T >
class ConstPrimitiveTest : public PrimitiveTest<T> 
{
protected:
	T current_value_;
public:
	/// Test constructor\n
	/// \param _value - constant, 0 by default
	ConstPrimitiveTest( T _value = 0 ) 
		: current_value_(_value)
	{
	}
	/// Getter function  
	/// \returns current value
	virtual T Get()
	{
		return current_value_;
	}
	virtual ConstPrimitiveTest* Generate() 
	{
		Test::Generate();
		return this;  
	}
	virtual void Print(std::ostream& _out = std::cout) const 
	{ 
		_out << current_value_; 
	}
	virtual ConstPrimitiveTest* Clone() const
	{
		return new ConstPrimitiveTest(current_value_);
	}
	virtual ~ConstPrimitiveTest() {}
	ConstPrimitiveTest<T>& operator= (T _current_value)
	{
		current_value_ = _current_value;
		return *this;
	}
};

#endif