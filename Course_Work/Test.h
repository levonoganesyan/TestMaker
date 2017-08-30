#ifndef TEST___
#define TEST___


#include"Utils.h"

class Test
{
protected:
	bool test_generated_;
	std::vector<Test*> objects_with_delete_responsibility_;
public:
	// typedef std::shared_ptr<Test> TOSPtr;
	Test() : test_generated_(false) {}
	virtual void Generate() = 0;
	virtual void Print(std::ostream& = std::cout) const = 0;
	virtual Test* Clone() const = 0;
	virtual Test * Add ( Test * )
	{
		throw std::runtime_error("Test: Can't add to a leaf");
	}
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