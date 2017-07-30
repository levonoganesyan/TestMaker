#include "Utils.h"


std::function<int()> RNG::rng_function_ = std::bind(&::rand);
RNG::RNG() {};
int RNG::Rand()
{
	return rng_function_();
}
void RNG::RandomFunction(std::function<int()> _rng_function)
{
	rng_function_ = _rng_function;
}
void RNG::RandomSeed(unsigned int _seed)
{
	srand(_seed);
}

