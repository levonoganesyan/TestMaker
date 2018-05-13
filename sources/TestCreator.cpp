#include"TestCreator.h"

void TestCreator::TestGenerating(int interval_start, int interval_end)
{
	Test* local_thread = test_->Clone();
	for (int i = interval_start; i < interval_end; i++)
	{
		std::filebuf fb;
		std::string string_to_append = (start_from_ + i < 100) ? ((start_from_ + i < 10) ? "0" : "") + std::string("0") : "";
		fb.open(path_ + "\\" + file_name_prefix_ + string_to_append + std::to_string(start_from_ + i) + extension_, std::ios::out);
		std::ostream os(&fb);
		local_thread->Generate();
		local_thread->Print(os);
	}
}

TestCreator::TestCreator(Test * _test, int _times, std::string _path, int _number_of_threads, std::string _file_name_prefix, std::string _extension, int _start_from)
	: test_(_test)
	, path_(_path)
	, times_(_times)
	, number_of_threads_(_number_of_threads)
	, file_name_prefix_(_file_name_prefix)
	, extension_(_extension)
	, start_from_(_start_from)
{

}

void TestCreator::Make()

{
	std::vector<std::thread> threads(number_of_threads_);

	int count_of_tests_per_thread = (times_ + number_of_threads_ - 1) / number_of_threads_;
	for (int i = 0; i < number_of_threads_; i++)
	{
		threads[i] = std::thread(&TestCreator::TestGenerating, this, i * count_of_tests_per_thread, std::min((i + 1) * count_of_tests_per_thread, times_));
	}
	for (int i = 0; i < number_of_threads_; i++)
	{
		threads[i].join();
	}
}