#ifndef RANDOM_SET___
#define RANDOM_SET___


#include"Test.h"

/// \class RandomTestSet.\n
/// Must be used when need get random test from set of tests.\n

class RandomTestSet : public Test
{
	std::vector<Test*> random_set_;
	Test* current_test_;
public:
	/// RandomTestSet.
	/// Here is an example for RandomTestSet. You can try it by taking it from RandomTestSet.h
	/*!
	\code
	int main()
	{
		PrimitiveTest<int>* number = CreateElement(3, 5);
		PrimitiveTest<char>* character = CreateElement('a', 'z');
		Array* arr = new Array(CreateElement(1, 10), CreateElement(5));
		RandomTestSet* random_set = new RandomTestSet();
		random_set->Add(number)->Add(character)->Add(arr)->Add((new ConstStringSet())->Add("SomeRandomWord"));
		random_set->Generate();
		random_set->Print();
		delete random_set;
		delete arr;
		delete character;
		delete number;
	}
	\endcode
	*/
	RandomTestSet();
	/// Adds test in set. 
	/// \param _test - test to add
	/// \returns this
	virtual RandomTestSet* Add(Test * _test);
	/// Gets fixed test from the set. 
	/// \returns this
	virtual Test* Get();
	/// Fixes a random test and call Generate() above them
	/// \returns this
	virtual RandomTestSet* Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual RandomTestSet* Clone() const;
	virtual ~RandomTestSet();
};

#endif