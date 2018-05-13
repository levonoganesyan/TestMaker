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
		this->Add(CreateElement(1, 100));
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
	BinaryTree* Generate()
	{
		current_depth_ = depth_;
		this->Clear();
		E();
		return this;
	}

};
void run_code();
void main(int argc, char** argv) {
	double execution_start_time = clock();
	try
	{
		if (argc >= 3 && strcmp(argv[1], "-seed"))
		{
			RNG::RandomSeed(std::stoi(argv[2]));
		}
		else
		{
			RNG::RandomSeed(time(0));
		}
		run_code();
	}
	catch (std::runtime_error _err)
	{
		std::cout << "Runtime Error: " << _err.what() << std::endl;
	}
	catch (std::logic_error _err)
	{
		std::cout << "Logic Error: " << _err.what() << std::endl;
	}
	std::cout << "Programm execution time: " << (clock() - execution_start_time) / CLOCKS_PER_SEC << std::endl;
}

#include<map>

class Quadrilateral : public Test
{
	class Point : public Test
	{
		PrimitiveTest<double> *x_, *y_;
	public:
		Point()
		{
			x_ = CreateElement<double>(-10.0, 10.0);
			y_ = CreateElement<double>(-10.0, 10.0);
		}
		Point* Generate()
		{
			test_generated_ = true;
			x_->Generate();
			y_->Generate();
			return this;
		}
		void Print(std::ostream& _out) const
		{
			if (!test_generated_)
			{
				throw "TEST IS NOT GENERATED YET! Point:Print";
			}
			_out << x_->Get() * 100;
			_out << ":";
			_out << y_->Get() * 100;
		}
		virtual Test* Clone() const
		{
			Point* point = new Point();
			point->x_ = x_->Clone();
			point->y_ = y_->Clone();
			return point;
		}
		std::pair<double, double> Get()
		{
			return std::make_pair(x_->Get(), y_->Get());
		}
		~Point()
		{
			delete x_;
			delete y_;
		}
	};
	std::vector<Point*> points;
	const int count;
	inline int area(Point* a, Point* b, Point* c) {
		return (b->Get().first - a->Get().first) * (c->Get().second - a->Get().second) - (b->Get().second - a->Get().second) * (c->Get().first - a->Get().first);
	}

	inline bool intersect_1(int a, int b, int c, int d) {
		if (a > b)  std::swap(a, b);
		if (c > d)  std::swap(c, d);
		return std::max(a, c) <= std::min(b, d);
	}

	bool intersect(Point* a, Point* b, Point* c, Point* d) {
		return intersect_1(a->Get().first, b->Get().first, c->Get().first, d->Get().first)
			&& intersect_1(a->Get().second, b->Get().second, c->Get().second, d->Get().second)
			&& area(a, b, c) * area(a, b, d) <= 0
			&& area(c, d, a) * area(c, d, b) <= 0;
	}
public:
	Quadrilateral() : count(4)
	{
		for (int i = 0; i < count; i++)
		{
			points.push_back(new Point());
		}
	}
	virtual Quadrilateral* Generate()
	{
		test_generated_ = true;
		while (1)
		{
			for (int i = 0; i < count; i++)
			{
				points[i]->Generate();
			}
			std::sort(points.begin(), points.end(), [](Point* a, Point* b) -> bool { return atan(b->Get().second / b->Get().first) < atan(a->Get().second / a->Get().first); });
			if (!intersect(points[0], points[1], points[2], points[3]) && !intersect(points[0], points[3], points[2], points[1]))
				break;
		}
		return this;
	}
	virtual void Print(std::ostream& _out) const
	{
		if (!test_generated_)
		{
			throw "TEST IS NOT GENERATED YET! Quadrilateral:Print";
		}
		for (int i = 0; i < count; i++)
		{
			points[i]->Print(_out);
			_out << std::endl;
		}
	}
	virtual Test* Clone() const
	{
		Quadrilateral* q = new Quadrilateral();
		q->points = points;
		return q;
	}
};
class BG : public Test
{
	//CompositeTest* test;
	PrimitiveTest<int> *members;
	PrimitiveTest<int> *count;
	ConstStringSet* css;
	Array* arr;
public:
	BG()
	{
		members = CreateElement<int>(1, 50);
		count = CreateElement<int>(1, 50);
		css = new ConstStringSet();
		css->Add("B");
		css->Add("G");
		arr = new Array(members, css, "");
		arr->PrintSize(false);
		//test = new CompositeTest();
		//test->Add(members)->Add(space_delimiter)->Add(count)->Add(new_line_delimiter)->Add(arr);
	}
	virtual BG* Generate()
	{
		members->Generate();
		count->Generate();
		arr->Generate();
		//test->Generate();
		return this;
	}
	virtual void Print(std::ostream& _out) const
	{
		members->Print(_out);
		space_delimiter->Print(_out);
		count->Print(_out);
		new_line_delimiter->Print(_out);
		arr->Print(_out);
	}
	virtual Test* Clone() const
	{
		BG * bg = new BG();
		bg->members = members->Clone();
		bg->count = count->Clone();
		bg->css = bg->css;
		bg->arr = new Array(bg->members, bg->css, "");
		bg->arr->PrintSize(false);
		arr->PrintSize(false);
		return bg;
	}
	~BG()
	{
		delete members;
		delete count;
		delete css;
		delete arr;
	}
};
//class Forest : public Test
//{
//	std::vector<int> available_vertexes_;
//	PrimitiveTest<int>* number_of_vertices_;
//	PrimitiveTest<int>* number_of_edges_;
//	class MyGraph : public NonDirectedGraph
//	{
//		std::map<int, int> vertices_map_;
//		std::vector<int> available_vertexes_;
//		virtual void Print(std::ostream& _out) const
//		{
//		}
//	public:
//		MyGraph(std::vector<int>& _available_vertexes, PrimitiveTest<int>* _number_of_vertices, PrimitiveTest<int>* _number_of_edges, PrimitiveTest<int>* _weights, bool _acyclic, bool _buckle)
//			: NonDirectedGraph(_number_of_vertices, _number_of_edges, _weights, _acyclic, _buckle)
//			, available_vertexes_(_available_vertexes)
//		{
//			Generate();
//			current_number_of_vertices_ = VerticesCount();
//			for (int i = 0; i < current_number_of_vertices_; i++)
//			{
//				vertices_map_[i] = _available_vertexes.back();
//				_available_vertexes.pop_back();
//			}
//		}
//
//		virtual void Print(std::ostream& _out)
//		{
//			std::vector<std::pair<int, int> > list_of_edges = ListOfEdges();
//			for (unsigned int i = 0; i < list_of_edges.size(); i++)
//			{
//				_out << vertices_map_[list_of_edges[i].first] + 1 << ' '
//					<< vertices_map_[list_of_edges[i].second] + 1 << std::endl;
//			}
//		}
//		virtual Test* Clone()
//		{
//			MyGraph* graph = new MyGraph(available_vertexes_, number_of_vertices_, number_of_edges_, nullptr, true, false);
//			return graph;
//		}
//	};
//	std::vector<MyGraph*> graphs_;
//	int used_vertices_;
//	int used_edges_;
//public:
//	Forest(PrimitiveTest<int>* _number_of_vertices, PrimitiveTest<int>* _number_of_edges)
//		: number_of_vertices_(_number_of_vertices)
//		, number_of_edges_(_number_of_edges)
//	{
//	}
//	virtual void Generate()
//	{
//		for ( unsigned int i = 0; i < graphs_.size(); i++)
//		{
//			delete graphs_[i];
//		}
//		graphs_.clear();
//		number_of_vertices_->Generate();
//		number_of_edges_->Generate();
//		int current_number_of_vertices = number_of_vertices_->Get();
//		int current_number_of_edges = number_of_edges_->Get();
//		available_vertexes_.clear();
//		available_vertexes_.resize(current_number_of_vertices);
//		for (int i = 0; i < current_number_of_vertices; i++)
//		{
//			available_vertexes_[i] = i;
//		}
//		std::random_shuffle(available_vertexes_.begin(), available_vertexes_.end());
//		while (current_number_of_vertices != 0)
//		{
//			int number_of_vertices_current_tree = Rand() % (current_number_of_vertices + 1);
//			while (number_of_vertices_current_tree == 0)
//			{
//				number_of_vertices_current_tree = Rand() % (current_number_of_vertices + 1);
//			}
//			current_number_of_vertices -= number_of_vertices_current_tree;
//			int number_of_edges_current_tree = Rand() % (current_number_of_edges + 1);
//			graphs_.push_back(
//				new MyGraph(
//					available_vertexes_,
//					CreateElement(number_of_vertices_current_tree, number_of_vertices_current_tree),
//					CreateElement(number_of_edges_current_tree, number_of_edges_current_tree),
//					nullptr,
//					true,
//					false
//				)
//			);
//			current_number_of_edges -= graphs_.back()->EdgesCount();
//		}
//		used_vertices_ = number_of_vertices_->Get() - current_number_of_vertices;
//		used_edges_ = number_of_edges_->Get() - current_number_of_edges;
//	}
//	virtual void Print(std::ostream& _out) const
//	{
//		_out << used_vertices_ << ' ' << used_edges_ << std::endl;
//		for (unsigned int i = 0; i < graphs_.size(); i++)
//		{
//			graphs_[i]->Print(_out);
//		}
//	}
//	virtual Test* Clone() const
//	{
//		return new Forest(number_of_vertices_, number_of_edges_);
//	}
//
//};
class Palindrome : public Test
{
	std::vector<RangePrimitiveTest<char>*> word_;
	PrimitiveTest<int>* count_;
public:
	Palindrome(PrimitiveTest<int>* _count)
		: count_(_count)
	{

	}
	virtual Palindrome* Generate()
	{
		count_->Generate();
		word_.clear();
		for (int i = 0; i < count_->Get(); i++)
		{
			word_.push_back(new RangePrimitiveTest<char>('a', 'z'));
			word_.back()->Generate();
		}
		return this;
	}
	virtual void Print(std::ostream& _out) const
	{
		for ( unsigned int i = 0; i < word_.size(); i++)
		{
			_out << word_[i]->Get();
		}
	}
	virtual Test* Clone() const
	{
		Palindrome* p = new Palindrome(count_);
		return p;
	}
};
void problem_a()
{
	RNG::RandomSeed(time(0));
	ConstStringSet* css = new ConstStringSet();
	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		css->Add(ch);
	}
	Array* word = new Array(CreateElement(1, 32), css, "", "");
	word->PrintSize(false);
	Array* test = new Array(CreateElement(1, 100000), word, "\n");
	test->PrintSize(true);
	TestCreator tc(test, 20, "D:/tests/a/tests", 1, "", ".in");
	tc.Make();
}
void problem_b()
{
	Test* test = new CompositeTest();
	test->Add(CreateElement(1, 100))->Add(space_delimiter)->Add(CreateElement(0, 900));
	TestCreator tc(test, 200, "D:/tests/b/tests", 1, "", ".in");
	tc.Make();
}
void problem_c()
{
	for (int i = 2; i <= 16; i++)
	{
		TestCreator tc(CreateElement(i), 1, "D:/tests/c/tests", 1, "", std::to_string(i) + ".in", 2);
		tc.Make();
	}
}
void problem_d()
{
	// Problem_Forest::Forest* q = new Problem_Forest::Forest(CreateElement(1000), CreateElement(1000));
	Palindrome* palindrome = new Palindrome(CreateElement(1, 100));
	TestCreator tc(palindrome, 100, "D:/tests/d/tests", 1, "", ".in");
	tc.Make();
}
void problem_e()
{
	Test* test = new CompositeTest();
	test->Add(CreateElement<long long>(1, 1000000000000000000ll))->Add(space_delimiter)->Add(CreateElement<long long>(1, 1000000000000000000ll))->Add(new_line_delimiter);
	TestCreator tc(test, 200, "D:/tests/e/tests", 1, "", ".in");
	tc.Make();
}
void problem_f()
{
	BG* test = new BG();
	TestCreator tc(test, 200, "D:/tests/f/tests", 1, "", ".in");
	tc.Make();
}
//void problem_h()
//{
//	Forest* test1 = new Forest(CreateElement(1, 100000), CreateElement(1, 100000));
//	TestCreator tc1(test1, 50, "D:/tests/h/tests", 1, "", ".in");
//	tc1.Make();
//	Graph* test2 = new NonDirectedGraph(CreateElement(1, 100000), CreateElement(1, 100000));
//	test2->PrintType(Graph::LIST_OF_EDGES);
//	TestCreator tc2(test2, 50, "D:/tests/h/tests", 1, "", ".in", 50);
//	tc2.Make();
//}
void problem_g()
{
	Quadrilateral* test = new Quadrilateral();
	TestCreator tc(test, 50, "D:/tests/g/tests", 1, "", ".in", 0);
	tc.Make();
}

void regexPostProcess1(std::string& _result)
{
	_result.replace(0, _result.find('\n'), std::string(_result.find('\n'), 'a'));
}
void regexPostProcess(std::string& _result)
{
	for (size_t i = 0; i < _result.size(); i++)
	{
		_result[i]++;
	}
}
void matrixPostProcess(std::string& _result)
{
	std::istringstream is(_result);
	std::ostringstream os;
	int n;
	is >> n;
	std::vector<std::vector<int>> vec(n, std::vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			is >> vec[i][j];
	for (int i = 0; i < n; i++)
		vec[i][i] = 0;
	os << n << std::endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			os << vec[i][j] << " ";
		os << std::endl;
	}
	_result = os.str();
}
void run_code()
{

	ConstPrimitiveTest<double>* pi = new ConstPrimitiveTest<double>(3.14);
	while (1)
	{
		RegEx* regex = new RegEx("[a-z]+(\\.[a-z]+)*@[a-z]+(\\.[a-z]+)*", 10);
		TestCreator* tc = new TestCreator(regex, 10, "d:\\Users\\Loki\\Desktop\\Tests", 1, "regex", ".txt", 12);
		tc->Make();
		// regex->Generate()->Print();

		/*Grammar* gr = new Grammar("({1,2,3}, {a,b,c}, P, 1)", "${1}->${2}${3}\n${2}->a${2}\n${2}->${3}\n${3}->${3}b\n${3}->e");
		gr->Generate()->Print();
		*/system("pause");
		system("cls");
		/*Graph* g1 = new Graph(CreateElement(3), CreateElement(2));
		g1->PrintType(Graph::LIST_OF_EDGES)->Generate()->Print(std::cout);
		std::cout << std::endl;
		Graph* g2 = new Graph(CreateElement(3), CreateElement(2));
		g2->PrintType(Graph::LIST_OF_EDGES)->Generate()->Print(std::cout);
		std::cout << std::endl;
		GraphMerger* gm = new GraphMerger(g1, g2, g1, g2, g1, g2);
		GraphMerger* gm1 = new GraphMerger(g1, g2);
		gm1->PrintType(Graph::LIST_OF_EDGES)->Generate()->Print(std::cout);
		system("pause");
		system("cls");*/
		/*RegEx* regex = new RegEx("([a-zA-Z]{100}\n)*", 100);
		regex->SetPostprocessFunction(regexPostProcess1)->Generate()->Print();
		system("pause");
		system("cls");*/

		/*auto a = CreateElement(0, 99);
		std::vector<int> vec(100);
		for (int i = 0; i < 100000000; i++)
		{
			a->Generate();
			vec[a->Get()]++;
		}
		for (int i = 0; i < 100; i++)
		{
			std::cout << i << "\t" << vec[ i ] << std::endl;
		}
		return;
		*/
		/*Matrix* matrix = new Matrix(CreateElement(5), CreateElement(10));
		matrix->SetPostprocessFunction(matrixPostProcess)->Generate()->Print();
		system("pause");
		system("cls");*/
		//PrimitiveTest<int>* vertices_count = CreateElement(3, 5);
		//PrimitiveTest<int>* edges_count = CreateElement(5, 10);
		//Graph* graph = new Graph(vertices_count, edges_count);
		//graph->Buckle()->Directed();
		//graph->PrintType(Graph::LIST_OF_EDGES);
		//graph->Generate();
		//graph->Print();
		//delete graph;
		//delete edges_count;
		//delete vertices_count;
		/*Graph* graph = new Graph(CreateElement(3, 5), CreateElement(5, 10));
		graph->Buckle()->Directed()->PrintType(Graph::LIST_OF_EDGES)->Generate()->Print();
		delete graph;
		system("pause");
		system("cls");*/
		/*RegEx* regex = new RegEx("[12]*", 100);
		std::cout << "Printing...\n";
		regex->SetPostprocessFunction(regexPostProcess2);
		regex->Generate();
		regex->Print();
		std::cout << "\nPrinted...\n";
		delete regex;
		system("pause");
		system("cls");*/
        /*PrimitiveTest<int>* size_of_matrix = CreateElement( 6, 6 );
        Array* arr1 = new Array( size_of_matrix, CreateElement( 10, 20 ) );
		arr1->PrintSize(false);
        Array* arr2 = new Array( size_of_matrix, arr1, "");
        arr2->Generate();
        arr2->Print();
        system( "pause" );
        system( "cls" );*/
	}
}
