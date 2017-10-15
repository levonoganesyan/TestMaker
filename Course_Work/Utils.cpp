#include "Utils.h"


unsigned long long RNG::seed_ = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937_64 RNG::generator_(RNG::seed_);
RNG::RNG() {};
unsigned long long RNG::Rand()
{ 
	// std::cout << "Maximum: " << generator_.max() << std::endl;
	// std::cout << "Minimum: " << generator_.min() << std::endl;
	return generator_();
}
void RNG::RandomSeed(unsigned int _seed)
{
	generator_.seed(_seed);
}
unsigned long long RNG::Max()
{
	return generator_.max();
}
unsigned long long RNG::Min()
{
	return generator_.min();
}
