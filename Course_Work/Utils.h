#ifndef UTILS__
#define UTILS__

#include<cstdlib>
#include<memory>
#include<stdexcept>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<iomanip>
#include<functional>

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
//char GetEscapedCharByString(std::string character)
//{
//	if (character == "\t")
//		return '\t';
//	else if (character == "\n")
//		return '\n';
//	else if (character == "\v")
//		return '\v';
//	else if (character == "\f")
//		return '\f';
//	else if (character == "\r")
//		return '\r';
//	else if (character == "\0")
//		return '\0';
//	else if (character == "\.")
//		return '\.';
//	else if (character == "\\")
//		return '\\';
//	else if (character == "\+")
//		return '\+';
//	else if (character == "\*")
//		return '\*';
//	else if (character == "\?")
//		return '\?';
//	else if (character == "\^")
//		return '\^';
//	else if (character == "\$")
//		return '\$';
//	else if (character == "\{")
//		return '\{';
//	else if (character == "\}")
//		return '\}';
//	else if (character == "\(")
//		return '\(';
//	else if (character == "\)")
//		return '\)';
//	else if (character == "\[")
//		return '\[';
//	else if (character == "\]")
//		return '\]';
//	else if (character == "\|")
//		return '\|';
//	else if (character == "\/")
//		return '\/';
//}

#endif