#ifndef TEST_LIBRARY__
#define TEST_LIBRARY__

#include"Test.h"
#include"CompositeTest.h"
#include"Range.h"
#include"Array.h"
#include"Delimiter.h"
#include"ConstStringSet.h"
#include"PrimitiveTest.h"
#include"ConstPrimitiveTest.h"
#include"RangePrimitiveTest.h"

#include"Graph.h"
#include"NonDirectedGraph.h"
#include"DirectedGraph.h"

#include"RegEx.h"
#include"Grammar.h"

#include"TestCreator.h"


// global helpful variables
Delimiter* space_delimiter = new Delimiter ( " " );
Delimiter* new_line_delimiter = new Delimiter ( "\n" );
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

// must to call clone() ??? 
inline PrimitiveTest<int>* CreateNumber(PrimitiveTest<int>* _start, PrimitiveTest<int>* _end)
{
	PrimitiveTest<int>* start_number = _start->Clone();
	PrimitiveTest<int>* end_number = _end->Clone();
	Range<int>* number_range = new Range<int>(start_number, end_number);
	PrimitiveTest<int>* number = new RangePrimitiveTest<int>(number_range);
	return number;
}

inline PrimitiveTest<int>* CreateNumber(int _start, int _end)
{
	ConstPrimitiveTest<int>* start_number = new ConstPrimitiveTest<int>(_start);
	ConstPrimitiveTest<int>* end_number = new ConstPrimitiveTest<int>(_end);
	return CreateNumber(start_number, end_number);
}

#endif