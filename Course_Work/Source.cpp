#include "TestLibrary.h"


class BinaryTree : public CompositeTest
{
	int depth_;
	int current_depth_;
public:
	BinaryTree(int _depth) : depth_(_depth), current_depth_(_depth) { this->Generate(); }
	void E()
	{
		ConstPrimitiveTest<char>* left_bracket = new ConstPrimitiveTest<char>('(');
		ConstPrimitiveTest<char>* right_bracket = new ConstPrimitiveTest<char>(')');
		if (current_depth_ == 0)
		{
			this->Add(left_bracket);
			this->Add(right_bracket);
			return;
		}
		current_depth_--;
		int rng = Rand() % 4;
		ConstPrimitiveTest<char>* semicolon = new ConstPrimitiveTest<char>(';');

		this->Add(left_bracket);
		this->Add(CreateNumber(1, 100));
		this->Add(semicolon);
		if (rng & 2)
		{
			E();
		}
		else
		{
			this->Add(left_bracket);
			this->Add(right_bracket);
		}
		this->Add(semicolon);
		if (rng & 1)
		{
			E();
		}
		else
		{
			this->Add(left_bracket);
			this->Add(right_bracket);
		}
		this->Add(right_bracket);
	}
	void Generate()
	{
		current_depth_ = depth_;
		this->Clear();
		E();
	}

};
#include <chrono>

void main() {
	try
	{
		RNG::RandomSeed(time(0));

		RangePrimitiveTest<int> integer;
		10 < integer < 19;
		integer.Generate();
		integer.Print();

		std::cout << "Generating graphs with V vertices and E edges with weights with output in file.\n";
		int count_threads = 5;
		while (count_threads --> 1)
		{
			long long start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			for (int v = 10000; v <= 10000; v *= 10)
			{
				for (int e = v * 100 ; e <= v * 100; e *= 10)
				{
					Graph* ndgraph = new NonDirectedGraph(CreateNumber(v, v), CreateNumber(e, e), CreateNumber(v, e));
					ndgraph->Buckle(false)->PrintType(Graph::LIST_OF_EDGES);
					Test* test = new CompositeTest();
					test->Add(ndgraph)->Add(new_line_delimiter);

					TestCreator* tc = new TestCreator(test, 4, "D:/tests", count_threads, "out_" + std::to_string(v) + "_" + std::to_string(e));
					tc->Make();
					// std::cout << "V = " << v << ", E = " << e << ". Executing time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - start_time << "ms." << std::endl;
					delete ndgraph;
				}
			}
			std::cout << "Count of threads: " << count_threads << ". Executing time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - start_time << "ms." << std::endl;
		}
	}
	catch (std::runtime_error _err)
	{
		std::cout << _err.what() << std::endl;
	}
}