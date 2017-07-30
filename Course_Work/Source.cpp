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

void main() {
	try
	{
		RNG::RandomSeed(time(0));
		Graph* ndgraph = new NonDirectedGraph(CreateNumber(40, 100), CreateNumber(10, 100), CreateNumber(1000, 500));
		ndgraph->Buckle(false)->PrintType(Graph::LIST_OF_EDGES)->Acyclic(true);
		Graph* dgraph = new DirectedGraph(CreateNumber(40, 100), CreateNumber(10000, 10000));
		dgraph->Buckle(false)->PrintType(Graph::CONNECTION_MATRIX)->Acyclic(true);

		Test* test = new CompositeTest();
		test->Add(ndgraph)->Add(new_line_delimiter)->Add(dgraph);

		TestCreator* tc = new TestCreator(test, 5, "D:/tests", "out");
		tc->Make();
	}
	catch (std::runtime_error _err)
	{
		std::cout << _err.what() << std::endl;
	}
}