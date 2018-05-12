#ifndef COMPOSITE_TEST___
#define COMPOSITE_TEST___

#include "Test.h"

/// CompositeTest class \n
/// Class that allows work with multiple tests as one.\n
/// Implements the Composite pattern\n
/// About that pattern you can read here: https://en.wikipedia.org/wiki/Composite_pattern \n
class CompositeTest : public Test
{
protected:
	std::vector<Test *> tests_;
public:

	CompositeTest();
	/// Add function\n
	/// This function need to be used when need to add test into test collection\n
	/// \param _test - Test to be add
	/// \returns this
	virtual Test * Add( Test * _test );
	virtual void Clear();
	virtual CompositeTest* Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual CompositeTest* Clone() const;
	virtual ~CompositeTest();
};

#endif