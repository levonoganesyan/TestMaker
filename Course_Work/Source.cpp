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
namespace Problem_Quadrilateral
{
	class Point : public Test
	{
		PrimitiveTest<double> *x_, *y_;
	public:
		Point()
		{
			x_ = CreateNumber<double>(-1000.0, 1000.0);
			y_ = CreateNumber<double>(-1000.0, 1000.0);
		}
		void Generate()
		{
			test_generated_ = true;
			x_->Generate();
			y_->Generate();
		}
		void Print(std::ostream& _out) const
		{
			if (!test_generated_)
			{
				throw "TEST IS NOT GENERATED YET! Point:Print";
			}
			x_->Print(_out);
			_out << ":";
			y_->Print(_out);
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
	
	
	class Quadrilateral : public Test
	{
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
		virtual void Generate()
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
}
namespace Problem_BG
{
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
			members = CreateNumber<int>(1, 50);
			count = CreateNumber<int>(1, 50);
			css = new ConstStringSet();
			css->Add("B");
			css->Add("G");
			arr = new Array(members, css, "");
			arr->PrintSize(false);
			//test = new CompositeTest();
			//test->Add(members)->Add(space_delimiter)->Add(count)->Add(new_line_delimiter)->Add(arr);
		}
		virtual void Generate()
		{
			members->Generate();
			count->Generate();
			arr->Generate();
			//test->Generate();
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
}
namespace Problem_Forest
{
	class Forest : public Test
	{
		std::vector<int> available_vertexes_;
		PrimitiveTest<int>* number_of_vertices_;
		PrimitiveTest<int>* number_of_edges_;
		class MyGraph : public NonDirectedGraph
		{
			std::map<int, int> vertices_map_;
			std::vector<int> available_vertexes_;
			virtual void Print(std::ostream& _out) const
			{
			}
		public:
			MyGraph(std::vector<int>& _available_vertexes, PrimitiveTest<int>* _number_of_vertices, PrimitiveTest<int>* _number_of_edges, PrimitiveTest<int>* _weights, bool _acyclic, bool _buckle)
				: NonDirectedGraph(_number_of_vertices, _number_of_edges, _weights, _acyclic, _buckle)
				, available_vertexes_(_available_vertexes)
			{
				Generate();
				current_number_of_vertices_ = VerticesCount();
				for (int i = 0; i < current_number_of_vertices_; i++)
				{
					vertices_map_[i] = _available_vertexes.back();
					_available_vertexes.pop_back();
				}
			}
			
			virtual void Print(std::ostream& _out)
			{
				std::vector<std::pair<int, int> > list_of_edges = ListOfEdges();
				for (unsigned int i = 0; i < list_of_edges.size(); i++)
				{
					_out << vertices_map_[list_of_edges[i].first] + 1 << ' ' 
						 << vertices_map_[list_of_edges[i].second] + 1 << std::endl;
				}
			}
			virtual Test* Clone()
			{
				MyGraph* graph = new MyGraph(available_vertexes_, number_of_vertices_, number_of_edges_, NULL, true, false);
				return graph;
			}
		};
		std::vector<MyGraph*> graphs_;
		int used_vertices_;
		int used_edges_;
	public:
		Forest(PrimitiveTest<int>* _number_of_vertices, PrimitiveTest<int>* _number_of_edges)
			: number_of_vertices_(_number_of_vertices)
			, number_of_edges_(_number_of_edges)
		{
		}
		virtual void Generate()
		{
			for (int i = 0; i < graphs_.size(); i++)
			{
				delete graphs_[i];
			}
			graphs_.clear();
			number_of_vertices_->Generate();
			number_of_edges_->Generate();
			int current_number_of_vertices = number_of_vertices_->Get();
			int current_number_of_edges = number_of_edges_->Get();
			available_vertexes_.clear();
			available_vertexes_.resize(current_number_of_vertices);
			for (int i = 0; i < current_number_of_vertices; i++)
			{
				available_vertexes_[i] = i;
			}
			std::random_shuffle(available_vertexes_.begin(), available_vertexes_.end());
			while (current_number_of_vertices != 0)
			{
				int number_of_vertices_current_tree = Rand() % (current_number_of_vertices + 1);
				while (number_of_vertices_current_tree == 0)
				{
					number_of_vertices_current_tree = Rand() % (current_number_of_vertices + 1);
				}
				current_number_of_vertices -= number_of_vertices_current_tree;
				int number_of_edges_current_tree = Rand() % (current_number_of_edges + 1);
				graphs_.push_back(
					new MyGraph(
						available_vertexes_,
						CreateNumber(number_of_vertices_current_tree, number_of_vertices_current_tree),
						CreateNumber(number_of_edges_current_tree, number_of_edges_current_tree),
						nullptr,
						true,
						false
					)
				);
				current_number_of_edges -= graphs_.back()->VerticesCount();
			}
			used_vertices_ = number_of_vertices_->Get() - current_number_of_vertices;
			used_edges_ = number_of_edges_->Get() - current_number_of_edges;
		}
		virtual void Print(std::ostream& _out) const
		{
			_out << used_vertices_ << ' ' << used_edges_ << std::endl;
			for (int i = 0; i < graphs_.size(); i++)
			{
				graphs_[i]->Print(_out);
			}
		}
		virtual Test* Clone() const
		{
			return new Forest(number_of_vertices_, number_of_edges_);
		}

	};
}
class Palindrome : public Test
{
	std::vector<RangePrimitiveTest<char>*> word_;
	PrimitiveTest<int>* count_;
public:
	Palindrome(PrimitiveTest<int>* _count)
		: count_(_count)
	{
			
	}
	virtual void Generate()
	{
		count_->Generate();
		word_.clear();
		for (int i = 0; i < count_->Get(); i++)
		{
			word_.push_back(new RangePrimitiveTest<char>('a', 'z'));
			word_.back()->Generate();
		}
	}
	virtual void Print(std::ostream& _out) const
	{
		for (int i = 0; i < word_.size(); i++)
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
void run_code()
{
	// Problem_Forest::Forest* q = new Problem_Forest::Forest(CreateNumber(10), CreateNumber(100));
	Palindrome* q = new Palindrome(CreateNumber(1, 100));
	TestCreator tc(q, 10, "D:/tests");
	tc.Make();
}