#ifndef TEST_LIBRARY__
#define TEST_LIBRARY__

#include"Test.h"
#include"PrimitiveTest.h"
#include"CompositeTest.h"
#include"Range.h"
#include"Array.h"
#include"Matrix.h"
#include"Delimiter.h"
#include"RandomTestSet.h"
#include"ConstStringSet.h"
#include"ConstPrimitiveTest.h"
#include"RangePrimitiveTest.h"

#include"Graph.h"

#include"RegEx.h"
#include"Grammar.h"

#include"TestCreator.h"


// global helpful variables
Delimiter* space_delimiter = new Delimiter(" ");
Delimiter* new_line_delimiter = new Delimiter("\n");
PrimitiveTest<int>* one = new ConstPrimitiveTest<int>(1);
PrimitiveTest<int>* ten = new ConstPrimitiveTest<int>(10);
PrimitiveTest<int>* hundred = new ConstPrimitiveTest<int>(100);
PrimitiveTest<int>* thousand = new ConstPrimitiveTest<int>(1000);
PrimitiveTest<int>* ten_thousands = new ConstPrimitiveTest<int>(10000);
PrimitiveTest<int>* hundred_thousands = new ConstPrimitiveTest<int>(100000);
PrimitiveTest<int>* million = new ConstPrimitiveTest<int>(1000000);
PrimitiveTest<int>* ten_millions = new ConstPrimitiveTest<int>(10000000);
PrimitiveTest<int>* hundred_millions = new ConstPrimitiveTest<int>(100000000);
PrimitiveTest<int>* milliard = new ConstPrimitiveTest<int>(1000000000);

// global helpful functions
template <typename T>
inline PrimitiveTest<T>* CreateElement(PrimitiveTest<T>* _start, PrimitiveTest<T>* _end)
{
	PrimitiveTest<T>* start_number = _start->Clone();
	PrimitiveTest<T>* end_number = _end->Clone();
	Range<T>* number_range = new Range<T>(start_number, end_number);
	number_range->AddDeleteResponsibility(start_number);
	number_range->AddDeleteResponsibility(end_number);
	PrimitiveTest<T>* number = new RangePrimitiveTest<T>(number_range);
	number->AddDeleteResponsibility(number_range);
	return number;
}

template <typename T = int>
inline PrimitiveTest<T>* CreateElement(T _start, T _end)
{
	ConstPrimitiveTest<T>* start_number = new ConstPrimitiveTest<T>(_start);
	ConstPrimitiveTest<T>* end_number = new ConstPrimitiveTest<T>(_end);
	PrimitiveTest<T>* number = CreateElement<T>(start_number, end_number);
	number->AddDeleteResponsibility(start_number);
	number->AddDeleteResponsibility(end_number);
	return number;
}

template <typename T = int>
inline PrimitiveTest<T>* CreateElement(T _number)
{
	return CreateElement(_number, _number);
}

#endif