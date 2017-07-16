#ifndef RANGE___
#define RANGE___
#pragma warning(disable : 4244)

#include"PrimitiveTest.h"

template <typename T>
class Range{
private:
	void generate_helper()
	{
// 		begin_->Generate();
// 		end_->Generate();
// 		while ( begin_->Get() > end_->Get() )
// 		{
// 			begin_->Generate();
// 			end_->Generate();
// 		}
	}
	long long get_time()
	{
		int lo, hi; 
		__asm { 
			rdtsc
			mov lo, eax
			mov hi, edx
		}
		return (((long long)hi) << 32LL) | lo;	
	}
protected:
	//std::shared_ptr<
	PrimitiveTest<T> *begin_, *end_;
public:
	Range() { }
	Range(PrimitiveTest<T>* _begin, PrimitiveTest<T>* _end) : begin_(_begin), end_(_end) {}
	//Range(T _begin) : begin_(_begin), end_(_begin) {}
	T Generate() {};
// 	Range* Clone()
// 	{
// 		return new Range(begin_->Clone(), end_->Clone());
// 	}
};

template<>
int Range<int>::Generate(){
	generate_helper();
	return rand()%( end_->Get() - begin_->Get() + 1 ) + begin_->Get();
}
template<>
double Range<double>::Generate(){
	generate_helper();
	double random_double = (double)rand() / RAND_MAX;
	return ( (double)rand() / RAND_MAX ) * ( end_->Get() - begin_->Get() ) + begin_->Get();
}
template<>
char Range<char>::Generate(){
	generate_helper();
	return (char)(rand()%( end_->Get() - begin_->Get() + 1 ) + begin_->Get());
}

#endif