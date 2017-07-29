//#include "TestLibrary.h"
//// ToString
//
//
//class Expression : public CompositeTest
//{
//	int depth_;
//	int current_depth_;
//public:
//	Expression(int _depth) : depth_(_depth), current_depth_(_depth) { this->Generate(); }
//	void E()
//	{
//		if (current_depth_ == 0)
//		{
//			this->Add(CreateNumber(1, 100));
//			return;
//		}
//		current_depth_--;
//		int rng = rand() & 1;
//		if (!rng)
//		{
//			ConstStringSet* css = new ConstStringSet();
//			css->Add("+")
//				->Add("*")
//				->Add("-")
//				->Add("/");
//			E();
//			this->Add(css);
//			E();
//			delete css;
//		}
//		else
//		{
//			ConstPrimitiveTest<char>* left_bracket = new ConstPrimitiveTest<char>('(');
//			ConstPrimitiveTest<char>* right_bracket = new ConstPrimitiveTest<char>(')');
//			this->Add(left_bracket);
//			E();
//			this->Add(right_bracket);
//			delete right_bracket;
//			delete left_bracket;
//		}
//	}
//	void Generate()
//	{
//		this->tests_.clear();
//		current_depth_ = depth_;
//		E();
//	}
//
//};
//
//class BinaryTree : public CompositeTest
//{
//	int depth_;
//	int current_depth_;
//public:
//	BinaryTree(int _depth) : depth_(_depth), current_depth_(_depth) { this->Generate(); }
//	void E()
//	{
//		ConstPrimitiveTest<char>* left_bracket = new ConstPrimitiveTest<char>('(');
//		ConstPrimitiveTest<char>* right_bracket = new ConstPrimitiveTest<char>(')');
//		if (current_depth_ == 0)
//		{
//			this->Add(left_bracket);
//			this->Add(right_bracket);
//			return;
//		}
//		current_depth_--;
//		int rng = rand() % 4;
//		ConstPrimitiveTest<char>* semicolon = new ConstPrimitiveTest<char>(';');
//
//		this->Add(left_bracket);
//		this->Add(CreateNumber(1, 100));
//		this->Add(semicolon);
//		if (rng & 2)
//		{
//			E();
//		}
//		else
//		{
//			this->Add(left_bracket);
//			this->Add(right_bracket);
//		}
//		this->Add(semicolon);
//		if (rng & 1)
//		{
//			E();
//		}
//		else
//		{
//			this->Add(left_bracket);
//			this->Add(right_bracket);
//		}
//		this->Add(right_bracket);
//	}
//	void Generate()
//	{
//		current_depth_ = depth_;
//		this->tests_.clear();
//		E();
//	}
//
//};
//
//class Time : public CompositeTest
//{
//public:
//	Time()
//	{
//		//CompositeTest::Generator.set(&Time::Generate); 
//	}
//	virtual void Generate()
//	{
//		// 		std::for_each( tests_.begin(), tests_.end(), []( const TOSPtr& testObj ) { testObj->Generate(); } );
//		// 		while ( dynamic_cast<Int*>(tests_[2].get())->Get()%10 != dynamic_cast<Int*>(tests_[4].get())->Get()%10 )
//		// 		{
//		// 			tests_[4]->Generate();
//		// 		}
//	}
//	Time * Time::Clone() const
//	{
//		std::vector<Test *> tests;
//		for (unsigned int i = 0; i < tests_.size(); i++)
//		{
//			tests.push_back(tests_[i]->Clone());
//		}
//		Time cto;
//		cto.tests_ = tests;
//		return new Time(cto);
//	}
//};
//
//class MyCompositeTest : public CompositeTest
//{
//public:
//	// MyCompositeTest(CompositeTest * ct) : CompositeTest(*ct) {}
//	/*MyCompositeTest * MyCompositeTest::Clone() const
//	{
//	std::vector<TOSPtr> tests;
//	for ( auto it = tests_.begin() ; it != tests_.end() ; it++ )
//	{
//	tests.push_back(TOSPtr(it->get()->Clone()));
//	}
//	MyCompositeTest cto;
//	cto.tests_ = tests;
//	return new MyCompositeTest ( cto );
//	}*/
//};
//
//
//void main() {
//	srand(time(0));
//	try
//	{
//		//CompositeTest * mct = new MyCompositeTest();
//		//mct->Add(CreateNumber(new ConstPrimitiveTest<int>(1), new ConstPrimitiveTest<int>(100)));
//		//CompositeTest * mct1 = mct->Clone();
//
//		//PrimitiveTest<int> * bound1 = new ConstPrimitiveTest<int>(1);
//		//PrimitiveTest<int> * bound2 = new ConstPrimitiveTest<int>(100);
//		//Range<int>* range = new Range<int>(bound1, bound2);
//		//PrimitiveTest<int> * integer1 = new RangePrimitiveTest<int>(*range);
//		//Range<int>* range2 = new Range<int>(bound1, integer1);
//		//PrimitiveTest<int> * integer2 = new RangePrimitiveTest<int>(*range2);
//		//Range<int>* range3 = new Range<int>(integer1, integer2);
//		//PrimitiveTest<int> * integer3 = new RangePrimitiveTest<int>(*range3);
//
//
//
//
//		//CompositeTest * test = new CompositeTest();
//
//		//test->Add(bound1)
//		//	->Add(new_line_delimiter)
//		//	->Add(bound2)
//		//	->Add(new_line_delimiter)
//		//	->Add(integer1)
//		//	->Add(new_line_delimiter)
//		//	->Add(integer2)
//		//	->Add(new_line_delimiter)
//		//	->Add(integer3)
//		//	->Add(new_line_delimiter);
//		//	while (1)
//		//{
//		//	test->Print();
//		//	test->Generate();
//		//	system("pause");
//		//	system("cls");
//		//}
//		//return;
//
//
//		// 	Range<int> range_lenght_of_line ( 1, 20 );
//		// 	Int lenght_of_line ( range_lenght_of_line );
//		// 	Range<int> range_number_of_queries ( 0, 50 );
//		// 	Int number_of_queries ( range_number_of_queries );
//		// 
//		// 	Range<int> range_a(1, lenght_of_line.Get());
//		// 	Int a ( range_a );
//		// 	Range<int> range_b(a.Get(), lenght_of_line.Get());
//		// 	Int b ( range_b );
//		// 	ConstStringSet string_set;
//		// 	string_set.Add("odd");
//		// 	string_set.Add("even");
//		// 
//		// 	CompositeTest* query = new CompositeTest();
//		// 	query->Add(&a)
//		// 		 ->Add(&space_delimiter)
//		// 		 ->Add(&b)
//		// 		 ->Add(&space_delimiter)
//		// 		 ->Add(&string_set)
//		// 		 ->Add(&new_line_delimiter);
//		// 
//		// 	Array array_of_queries ( number_of_queries, query, "" );
//		// 
//		// 
//		// 	CompositeTest* test = new CompositeTest();
//		// 	test->Add(&lenght_of_line)
//		// 		->Add(&new_line_delimiter)
//		// 		->Add(&array_of_queries);
//		// 
//		// 	test->Print();
//		//PrimitiveTest<int>* start_n = one; 
//		//PrimitiveTest<int>* end_n = milliard; 
//
//		//Range<int> n_range( start_n , end_n );
//		//PrimitiveTest<int>* n = new RangePrimitiveTest<int>(n_range);
//
//
//		//std::function<Test*()> query_generator = [&start_n, &n]() -> Test* {	
//
//		//	Range<int> a_range( start_n , n );
//		//	PrimitiveTest<int>* a = new RangePrimitiveTest<int>(a_range);
//		//	Range<int> b_range( a , n );
//		//	PrimitiveTest<int>* b = new RangePrimitiveTest<int>(b_range);
//
//		//	ConstStringSet* string_set = new ConstStringSet();
//		//	string_set->Add("odd")->Add("even");
//
//		//	CompositeTest* query = new CompositeTest();
//		//	query->Add(a)
//		//		->Add(space_delimiter)
//		//		->Add(b)
//		//		->Add(space_delimiter)
//		//		->Add(string_set)
//		//		->Add(new_line_delimiter);
//
//		//	return query;
//		//};
//
//		//PrimitiveTest<int>* start_queries_number = one;
//		//PrimitiveTest<int>* end_queries_number = ten_thousands; 
//		//Range<int> queries_number_range( start_queries_number , end_queries_number );
//		//PrimitiveTest<int>* queries_number = new RangePrimitiveTest<int>(queries_number_range);
//
//		//Array* array_of_queries = new Array ( queries_number, query_generator, "" );
//
//
//		//CompositeTest* test = new CompositeTest();
//		//test->Add(n)
//		//	->Add(new_line_delimiter)
//		//	->Add(array_of_queries);
//
//		//for ( int i = 0 ; i < 10 ; i++ ) {
//		//	test->Generate();
//		//	test->Print();
//		//}
//
//
//		//PrimitiveTest<int>* start_n = new ConstPrimitiveTest<int>(1); 
//		//PrimitiveTest<int>* end_n = new ConstPrimitiveTest<int>(100); 
//		//
//		//Range<int> n_range ( start_n , end_n );
//		//PrimitiveTest<int>* n = new RangePrimitiveTest<int>(n_range);
//
//		//Range<int> a_range ( start_n , n );
//		//PrimitiveTest<int>* a = new RangePrimitiveTest<int>(a_range);
//		//
//		//Range<int> b_range ( a , n );
//		//PrimitiveTest<int>* b = new RangePrimitiveTest<int>(b_range);
//		//for ( int i = 0 ; i < 10 ; i++ ) {
//		//	n->Generate();
//		//	a->Generate();
//		//	b->Generate();
//		//}
//
//		//for ( int i = 0 ; i < 1000; i++ )
//		//{
//		//	std::cout << i << std::endl;
//		//}
//
//		//PrimitiveTest<int>* n = CreateNumber(one, ten)->Clone();
//
//
//		//std::function<Test*()> elements_generator = []() -> Test* {	
//		//	return CreateNumber(one, new ConstPrimitiveTest<int>(5000))->Clone();
//		//};
//		//
//		//Array* array_of_elements = new Array ( n, elements_generator, "\n" );
//
//		//ConstStringSet* css = new ConstStringSet();
//		//css->Add("###");
//
//
//		//PrimitiveTest<int>* queries_number = CreateNumber(one, ten)->Clone();
//
//		//std::function<Test*()> query_generator = [&n]() -> Test* {	
//		//	return CreateNumber(one, n)->Clone();
//		//};
//
//		//Array* array_of_queries = new Array ( queries_number, query_generator, "\n" );
//
//
//		//CompositeTest* test = new CompositeTest();
//		//test->Add(array_of_elements)
//		//	->Add(css)
//		//	->Add(new_line_delimiter)
//		//	->Add(array_of_queries);
//
//		//for ( int i = 0 ; i < 1000 ; i++ ) {
//		//	test->Generate();
//		//	test->Print();
//		//	system("pause");
//		//	system("cls");
//		//}
//
//		/*PrimitiveTest<int>* v = new ConstPrimitiveTest<int>(10);
//		PrimitiveTest<int>* e = new ConstPrimitiveTest<int>(100);
//		Graph *graph = new Graph(v, e);
//		graph->Buckle(true)->Oriented(true);*/
//		//for (int i = 0; i < 1000; i++) {
//		//	graph->Buckle(false)->Oriented(false);
//		//	graph->Generate();
//		//	graph->PrintType(Graph::PRINT_TYPE::CONNECTION_MATRIX);
//		//	graph->Print();
//		//	graph->PrintType(Graph::PRINT_TYPE::CONNECTION_LIST);
//		//	graph->Print();
//		//	graph->PrintType(Graph::PRINT_TYPE::LIST_OF_EDGES);
//		//	graph->Print(); 
//		//	/*graph->Buckle(true)->Oriented(false);
//		//	graph->Generate();
//		//	graph->Buckle();
//		//	graph->PrintType(Graph::PRINT_TYPE::CONNECTION_MATRIX);
//		//	graph->Print();
//		//	graph->PrintType(Graph::PRINT_TYPE::CONNECTION_LIST);
//		//	graph->Print();
//		//	graph->PrintType(Graph::PRINT_TYPE::LIST_OF_EDGES);
//		//	graph->Print();*/
//		//	/*graph->Buckle(true)->Oriented(true);
//		//	graph->Generate();
//		//	graph->PrintType(Graph::PRINT_TYPE::CONNECTION_MATRIX);
//		//	graph->Print();
//		//	graph->PrintType(Graph::PRINT_TYPE::CONNECTION_LIST);
//		//	graph->Print();
//		//	graph->PrintType(Graph::PRINT_TYPE::LIST_OF_EDGES);
//		//	graph->Print();*/
//		//	system("pause");
//		//	system("cls");
//		//}
//
//		// PrimitiveTest<int>* start = new ConstPrimitiveTest<int>(4);
//		// PrimitiveTest<int>* end = new ConstPrimitiveTest<int>(40);
//		/*PrimitiveTest<int>* v = new ConstPrimitiveTest<int>(10);
//		PrimitiveTest<int>* e = new ConstPrimitiveTest<int>(200);
//		Graph *graph = new DirectedGraph(v, e);
//		graph->Acyclic()->PrintType(Graph::LIST_OF_EDGES);
//		Test* test = new CompositeTest();
//		test->Add(graph);
//		TestCreator tc(test, 1000, "D:/tests", "graph", ".txt");
//		tc.Make();*/
//
//		//int depth = 5;
//		//Expression* a = new Expression(depth);
//		//int n = 100;
//		//while (n--)
//		//{
//		//	a->Generate();
//		//	a->Print();
//		//	std::cout << std::endl;
//		//}
//		BinaryTree* bt = new BinaryTree(1000);
//		int n = 10000;
//		while (n--)
//		{
//			system("cls");
//			bt->Generate();
//			bt->Print();
//			std::cout << std::endl;
//			system("pause");
//		}
//
//
//	}
//	catch (std::runtime_error _err)
//	{
//		std::cout << _err.what() << std::endl;
//	}
//}