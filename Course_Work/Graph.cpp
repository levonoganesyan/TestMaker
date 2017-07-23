
#include"Graph.h"
#include"ConstPrimitiveTest.h"
#include"RangePrimitiveTest.h"
#include<memory>

Graph::Graph(PrimitiveTest<int>* _number_of_vertices, PrimitiveTest<int>* _number_of_edges, PrimitiveTest<int>* _weights, bool _acyclic, bool _buckle)
	: number_of_vertices_(_number_of_vertices)
	, number_of_edges_(_number_of_edges)
	, weight_(_weights)
	, acyclic_(_acyclic)
	, buckle_(_buckle)
	, print_type_(PRINT_TYPE::CONNECTION_MATRIX)
	, print_function_(std::bind(&Graph::PrintConnectionMatrix, this, std::placeholders::_1))
{
}
std::vector<std::vector<bool> > Graph::ConnectionMatrix()
{
	if (current_number_of_vertices_ > 1000)
		throw "Number of vertices must be less or equal 1000";
	std::vector < std::vector < bool > > connection_matrix(current_number_of_vertices_, std::vector< bool >(current_number_of_vertices_));
	for (int i = 0; i < current_number_of_vertices_; i++)
	{
		std::set<int>::iterator it = graph_[i].begin();
		std::set<int>::iterator eit = graph_[i].end();
		for (; it != eit; it++)
		{
			connection_matrix[i][*it] = true;
		}
	}
	return connection_matrix;
}
void Graph::PrintConnectionMatrix(std::ostream& _out)
{
	std::vector < std::vector < bool > > connection_matrix = this->ConnectionMatrix();
	_out << connection_matrix.size() << std::endl;
	for (unsigned int i = 0; i < connection_matrix.size(); i++)
	{
		for (unsigned int j = 0; j < connection_matrix[i].size(); j++)
		{
			_out << connection_matrix[i][j] << ' ';
		}
		_out << std::endl;
	}
}
std::vector<std::set<int> > Graph::ConnectionList()
{
	return graph_;
}
void Graph::PrintConnectionList(std::ostream& _out)
{
	std::vector<std::set<int> > connection_list = ConnectionList();
	_out << connection_list.size() << std::endl;
	for (unsigned int i = 0; i < connection_list.size(); i++)
	{
		_out << connection_list[i].size() << ' ';
		std::set<int>::iterator it = graph_[i].begin();
		std::set<int>::iterator eit = graph_[i].end();
		for (; it != eit; it++)
		{
			_out << *it + 1 << ' ';
		}
		_out << std::endl;
	}
}
std::vector<std::pair<int, int> > Graph::ListOfEdges()
{
	std::vector < std::pair < int, int > > edges;
	for (unsigned int i = 0; i < graph_.size(); i++)
	{
		std::set<int>::iterator it = graph_[i].begin();
		std::set<int>::iterator eit = graph_[i].end();
		for (; it != eit; it++)
		{
			edges.push_back(std::make_pair(i, *it));
		}
	}
	return edges;
}
void Graph::PrintListOfEdges(std::ostream& _out)
{
	std::vector<std::pair<int, int> > edges = ListOfEdges();
	_out << current_number_of_vertices_ << ' ' << edges.size() << std::endl;
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		_out << edges[i].first + 1 << ' ' << edges[i].second + 1 << std::endl;
	}
}
int Graph::AddVertex()
{
	graph_.push_back(std::set<int>());
	return graph_.size();
}
bool Graph::AddEdge()
{
	std::shared_ptr<PrimitiveTest<int>> first_vertex_num(new ConstPrimitiveTest<int>(0));
	std::shared_ptr<PrimitiveTest<int>> last_vertex_num(new ConstPrimitiveTest<int>(graph_.size() - 1));
	std::shared_ptr<Range<int>> rng(new Range<int>(first_vertex_num.get(), last_vertex_num.get()));
	std::shared_ptr<PrimitiveTest<int>> random_number(new RangePrimitiveTest<int>(rng.get()));
	int first_vertex, second_vertex;
	random_number->Generate();
	first_vertex = random_number->Get();
	random_number->Generate();
	second_vertex = random_number->Get();
	if (!EdgeValidation(first_vertex, second_vertex))
		return false;
	this->AddEdge(first_vertex, second_vertex);
	return true;
}
void Graph::GenerateGraph()
{
	number_of_vertices_->Generate();
	number_of_edges_->Generate();
	current_number_of_vertices_ = number_of_vertices_->Get();
	current_number_of_edges_ = number_of_edges_->Get();
	graph_.clear();
	for (int i = 0; i < current_number_of_vertices_; i++)
	{
		this->AddVertex();
	}
	for (int i = 0; i < current_number_of_edges_; i++)
	{
		this->AddEdge();
	}


}
void Graph::Generate()
{
	GenerateGraph();
}
void Graph::Print(std::ostream& _out) const
{
	print_function_(_out);
}
Graph * Graph::Acyclic(bool _acyclic)
{
	if (buckle_)
	{
		throw "Buckle and Acyclic cannot be specified together";
	}
	acyclic_ = _acyclic;
	return this;
}
Graph * Graph::Buckle(bool _buckle)
{
	if (acyclic_)
	{
		throw "Buckle and Acyclic cannot be specified together";
	}
	buckle_ = _buckle;
	return this;
}
Graph * Graph::PrintType(PRINT_TYPE _print_type)
{
	print_type_ = _print_type;
	switch (print_type_)
	{
	case PRINT_TYPE::CONNECTION_MATRIX:
		print_function_ = std::bind(&Graph::PrintConnectionMatrix, this, std::placeholders::_1);
		break;
	case PRINT_TYPE::CONNECTION_LIST:
		print_function_ = std::bind(&Graph::PrintConnectionList, this, std::placeholders::_1);
		break;
	case PRINT_TYPE::LIST_OF_EDGES:
		print_function_ = std::bind(&Graph::PrintListOfEdges, this, std::placeholders::_1);
		break;
	default:
		break;
	}
	return this;
}
Graph::~Graph()
{
}
