#ifndef TEST___
#define TEST___


#include"Utils.h"
/// \class Test class \n
/// Base class for all classes.\n
/// Implements the Composite pattern\n
/// About that pattern you can read here: https://en.wikipedia.org/wiki/Composite_pattern \n
class Test
{
protected:
	bool test_generated_;
	std::vector<Test*> objects_with_delete_responsibility_;
public:
	/// Test constructor\n
	/// Initializes the variable test_generated_ as false, so that Test can not be generated if Generate() has not yet been called.\n
	Test() : test_generated_(false) {}
	/// Function to generating test\n
	/// When Generate() is called for any object, it calls same function for all dependent objects, and so on.\n
	/// Each class inherits and implements their logic of Test Generating.\n
	/// Must be implemented in any inherited classes.\n
	/// Can be overridden by client, but it is not recommended.\n
	/// \returns this
	virtual Test* Generate() = 0;
	/// Print function\n
	/// This function may used to output the Test to standart or custom stream.\n
	/// Must be implemented in any inherited classes.\n
	/// \param _stream - stream to output. Default: std::cout.\n
	virtual void Print(std::ostream& _stream = std::cout) const = 0;
	/// Clone function\n
	/// Implements the Prototype pattern. \n
	/// About that pattern you can read here: https://en.wikipedia.org/wiki/Prototype_pattern.\n
	/// Must be implemented in any inherited classes.\n
	/// \returns New object which has same state as current class
	virtual Test* Clone() const = 0;
	/// Clone function\n
	/// Implements the composite test logic.\n
	/// Must be implemented in any inherited classes.\n
	/// \param _test - test to add in composite test
	/// \returns this
	virtual Test * Add ( Test * _test )
	{
		THROW(true, "Can't add to a leaf");
	}
	/// Responsibility function\n
	/// Provides an opportunity to inform the object of its ownership.\n
	/// if there in any owned object it must be deleted in destructor.\n
	/// \param _object - object to delete
	virtual void AddDeleteResponsibility(Test* _object)
	{
		objects_with_delete_responsibility_.push_back(_object);
	}
	virtual ~Test() 
	{
		for (auto it : objects_with_delete_responsibility_)
		{
			delete it;
		}
	}
};

#endif