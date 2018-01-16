#ifndef UTILS__
#define UTILS__
#pragma warning(disable: 4244)

#include<cstdlib>
#include<memory>
#include<stdexcept>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<sstream>
#include<iomanip>
#include<functional>
#include<chrono>
#include<random>
#include<type_traits>

// long long get_time()
// {
// 	int lo, hi; 
// 	__asm { 
// 		rdtsc
// 			mov lo, eax
// 			mov hi, edx
// 	}
// 	return (((long long)hi) << 32LL) | lo;	
// }

//bool IsEscapedCharacterLetter(char letter)
//{
//	if (letter == 't' || letter == 'n' || letter == 'v' || letter == 'f' || letter == 'r' || letter == '0' || letter == '.' ||
//		letter == '\\' || letter == '+' || letter == '*' || letter == '?' || letter == '^' || letter == '$' || letter == '{' ||
//		letter == '}' || letter == '(' || letter == ')' || letter == '[' || letter == ']' || letter == '|' || letter == '/')
//	{
//		return true;
//	}
//	return false;
//}
//

/*!
 \def THROW(condition,error_message)
 Throw function
 if condition is true throws std::runtime_error
 \param condition - condition to check
 \param error_message - message to print on raise
 \exception raises std::runtime_error
*/
#define THROW(condition,error_message) if(condition) {\
	throw std::runtime_error(std::string("\nFile_name: ") + __FILE__ + "\nLine: " + std::to_string(__LINE__) + "\nError message: " + error_message );\
}\

inline static char GetEscapedCharByString(std::string character)
{
	if (character == "\\t")
		return '\t';
	else if (character == "\\n")
		return '\n';
	else if (character == "\\0")
		return '\0';
	else if (character == "\\\\")
		return '\\';
	else if (character == "\\/")
		return '/';
	return ' ';
}
class RNG
{
	static std::function<int()> rng_function_;
	static unsigned long long seed_;
	static std::mt19937_64 generator_;
public:
	RNG();
	static unsigned long long Rand();
	static void RandomSeed(unsigned int _seed);
	static unsigned long long Max();
	static unsigned long long Min();
};
inline unsigned long long Rand()
{
	return RNG::Rand();
}
inline unsigned long long Rand_with_mod( unsigned long long mod )
{
	return RNG::Rand() % mod;
}

#endif