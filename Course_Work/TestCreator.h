#ifndef TEST_CREATOR___
#define TEST_CREATOR___


#include"Test.h"
#include <string>
#include <fstream>

class TestCreator
{
protected:
	Test* test_;
	std::string path_;
	int times_;
	std::string file_name_prefix_;
	std::string extension_;
public:
	TestCreator(Test* _test, int _times, std::string _path, std::string _file_name_prefix = std::string(), std::string _extension = ".txt" )
	{
		test_ = _test;
		path_ = _path;
		times_ = _times;
		file_name_prefix_ = _file_name_prefix;
		extension_ = _extension;
	}
	void Make()
	{
		for (int i = 1; i <= times_; i++)
		{
			std::filebuf fb;
			fb.open(path_ + "\\" + file_name_prefix_ + std::to_string(i) + extension_, std::ios::out);
			std::ostream os(&fb);
			test_->Generate();
			test_->Print(os);
		}
	}
};

#endif