#ifndef TEST_CREATOR___
#define TEST_CREATOR___


#include"Test.h"
#include<string>
#include<fstream>
#include<thread>

/// TestCreator class
/// Class that allows generate 
class TestCreator
{
protected:
	Test* test_;
	std::string path_;
	int times_;
	int number_of_threads_;
	std::string file_name_prefix_;
	std::string extension_;
	int start_from_;
	void TestGenerating(int interval_start, int interval_end);
public:

	TestCreator(Test* _test, int _times, std::string _path, int _number_of_threads = 1, std::string _file_name_prefix = std::string(), std::string _extension = ".txt", int _start_from = 0);
	void Make();
};

#endif