
#include"Graph.h"
#include"ConstPrimitiveTest.h"
#include"RangePrimitiveTest.h"
#include<memory>

Graph::Graph(PrimitiveTest<int>* _number_of_vertices, PrimitiveTest<int>* _number_of_edges, Test* _weights, bool _directed, bool _buckle)
	: number_of_vertices_(_number_of_vertices)
	, number_of_edges_(_number_of_edges)
	, current_number_of_vertices_(0)
	, current_number_of_edges_(0)
	, number_of_already_added_edges_(0)
	, weight_(_weights)
	, directed_(_directed)
	, buckle_(_buckle)
	, print_type_(PRINT_TYPE::CONNECTION_MATRIX)
	, print_function_(std::bind(&Graph::PrintConnectionMatrix, this, std::placeholders::_1))
{
}
std::vector<std::vector<bool> > Graph::ConnectionMatrix()
{
	THROW(current_number_of_vertices_ > 10000, "Number of vertices must be less or equal 10000");
	std::vector < std::vector < bool > > connection_matrix(current_number_of_vertices_, std::vector< bool >(current_number_of_vertices_));
	for (int i = 0; i < current_number_of_vertices_; i++)
	{
		std::set<long long>::iterator it = graph_[i].begin();
		std::set<long long>::iterator eit = graph_[i].end();
		for (; it != eit; it++)
		{
			connection_matrix[i][*it] = true;
			if (!directed_)
			{
				connection_matrix[*it][i] = true;
			}
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
std::vector<std::set<long long> > Graph::ConnectionList()
{
	std::vector < std::set < long long > > graph;
	if (directed_)
	{
		graph = graph_;
	}
	else
	{
		graph.resize(current_number_of_vertices_);
		for (int i = 0; i < current_number_of_vertices_; i++)
		{
			std::set<long long>::iterator it = graph_[i].begin();
			std::set<long long>::iterator eit = graph_[i].end();
			for (; it != eit; it++)
			{
				graph[i].insert(*it);
				graph[*it].insert(i);
			}
		}
	}
	return graph;
}
void Graph::PrintConnectionList(std::ostream& _out)
{
	std::vector<std::set<long long> > connection_list = ConnectionList();
	_out << connection_list.size() << std::endl;
	for (unsigned int i = 0; i < connection_list.size(); i++)
	{
		_out << connection_list[i].size() << ' ';
		std::set<long long>::iterator it = connection_list[i].begin();
		std::set<long long>::iterator eit = connection_list[i].end();
		for (; it != eit; it++)
		{
			_out << *it + 1 << ' ';
		}
		_out << std::endl;
	}
}
std::vector<std::pair<long long, long long> > Graph::ListOfEdges()
{
	std::vector < std::pair < long long, long long > > edges;
	for (unsigned int i = 0; i < graph_.size(); i++)
	{
		std::set<long long>::iterator it = graph_[i].begin();
		std::set<long long>::iterator eit = graph_[i].end();
		for (; it != eit; it++)
		{
			edges.push_back(std::make_pair(i, *it));
		}
	}
	return edges;
}
void Graph::PrintListOfEdges(std::ostream& _out)
{
	std::vector<std::pair<long long, long long> > edges = ListOfEdges();
	_out << current_number_of_vertices_ << ' ' << edges.size() << std::endl;
	for (unsigned int i = 0; i < edges.size(); i++)
	{
		_out << edges[i].first + 1 << ' ' << edges[i].second + 1 << ' ';
		if (weight_ != nullptr)
		{
			weight_->Generate();
			weight_->Print(_out);
		}
		_out << std::endl;
	}
}
int Graph::AddVertex()
{
	graph_.push_back(std::set<long long>());
	return (int)graph_.size();
}
void Graph::AddEdge(long long _start, long long _end)
{
	if (!directed_)
	{
		if (_start > _end)
		{
			_start ^= _end ^= _start ^= _end;
		}
	}
	graph_[_start].insert(_end);
}
bool Graph::AddEdge()
{
	std::shared_ptr<PrimitiveTest<int>> first_vertex_num(new ConstPrimitiveTest<int>(0));
	std::shared_ptr<PrimitiveTest<int>> last_vertex_num(new ConstPrimitiveTest<int>((int)graph_.size() - 1));
	std::shared_ptr<Range<int>> rng(new Range<int>(first_vertex_num.get(), last_vertex_num.get()));
	std::shared_ptr<PrimitiveTest<int>> random_number(new RangePrimitiveTest<int>(rng.get()));
	int first_vertex, second_vertex;
	random_number->Generate();
	first_vertex = random_number->Get();
	random_number->Generate();
	second_vertex = random_number->Get();
	if (!directed_ && first_vertex > second_vertex)
	{
		first_vertex ^= second_vertex ^= first_vertex ^= second_vertex;
	}
	if (!buckle_ && first_vertex == second_vertex)
	{
		return false;
	}
	if (graph_[first_vertex].find(second_vertex) != graph_[first_vertex].end())
	{
		return false;
	}
	this->AddEdge(first_vertex, second_vertex);
	return true;
}
void Graph::RemoveEdge(long long _start, long long _end)
{
	if (!directed_)
	{
		if (_start > _end)
		{
			_start ^= _end ^= _start ^= _end;
		}
	}
	graph_[_start].erase(_end);
}
bool Graph::RemoveEdge()
{
	std::shared_ptr<PrimitiveTest<int>> first_vertex_num(new ConstPrimitiveTest<int>(0));
	std::shared_ptr<PrimitiveTest<int>> last_vertex_num(new ConstPrimitiveTest<int>((int)graph_.size() - 1));
	std::shared_ptr<Range<int>> rng(new Range<int>(first_vertex_num.get(), last_vertex_num.get()));
	std::shared_ptr<PrimitiveTest<int>> random_number(new RangePrimitiveTest<int>(rng.get()));
	int first_vertex, second_vertex;
	random_number->Generate();
	first_vertex = random_number->Get();
	random_number->Generate();
	second_vertex = random_number->Get();
	if (!directed_ && first_vertex > second_vertex)
	{
		first_vertex ^= second_vertex ^= first_vertex ^= second_vertex;
	}
	if (graph_[first_vertex].find(second_vertex) == graph_[first_vertex].end())
	{
		return false;
	}
	if (fixed_tree_.find(std::make_pair(first_vertex, second_vertex)) != fixed_tree_.end())
	{
		return false;
	}
	this->RemoveEdge(first_vertex, second_vertex);
	return true;
}
void Graph::FixingTree()
{
	std::vector<int> available_vertices(current_number_of_vertices_);
	for (int i = 0; i < current_number_of_vertices_; i++)
	{
		available_vertices[i] = i;
	}
	std::random_shuffle(available_vertices.begin(), available_vertices.end(), Rand_with_mod);
	for (; number_of_already_added_edges_ < current_number_of_edges_ && number_of_already_added_edges_ < current_number_of_vertices_ - 1; number_of_already_added_edges_++)
	{
		long long to = Rand() % (number_of_already_added_edges_ + 1);
		fixed_tree_.insert(std::make_pair(available_vertices[number_of_already_added_edges_ + 1], available_vertices[to]));
		//fixed_tree_.insert(std::make_pair(to, available_vertices[number_of_already_added_edges_]));
	}
}
void Graph::CreateTree()
{
	for (auto it = fixed_tree_.begin(); it != fixed_tree_.end(); it++)
	{
		AddEdge(it->first, it->second);
	}
}
void Graph::GenerateGraph()
{
	number_of_vertices_->Generate();
	number_of_edges_->Generate();
	current_number_of_vertices_ = number_of_vertices_->Get();
	current_number_of_edges_ = number_of_edges_->Get();
	THROW(current_number_of_vertices_ > 100'000'000, "Number of Graph vertices must be less than 1e8");
	THROW(current_number_of_edges_ > 1'000'000'000, "Number of Graph edges must be less than 1e9");
	graph_.clear();
	for (int i = 0; i < current_number_of_vertices_; i++)
	{
		this->AddVertex();
	}
	THROW(graph_.size() == 0, "Graph size is equals to 0");
	FixingTree();
	if (current_number_of_edges_ * 2 < current_number_of_vertices_ * current_number_of_vertices_)
	{
		CreateTree();
		GenerateSmallGraph();
	}
	else
	{
		GenerateLargeGraph();
	}
}
void Graph::GenerateSmallGraph()
{
	for (; number_of_already_added_edges_ < current_number_of_edges_; number_of_already_added_edges_++)
	{
		bool edge_added = AddEdge();
		while (!edge_added)
		{
			edge_added = AddEdge();
		}
	}
}
void Graph::GenerateLargeGraph()
{
	THROW(current_number_of_vertices_ * current_number_of_vertices_ >= 1'000'000'000 * 2, "Number of Graph edges must be less than 1e9");
	long long count_of_all_edges = 0;
	for (int i = 0; i < current_number_of_vertices_; i++)
	{
		for (int j = i * !directed_; j < current_number_of_vertices_; j++)
		{
			if (i == j && !buckle_)
			{
				continue;
			}
			graph_[i].insert(j);
			count_of_all_edges++;
		}
	}
	if (count_of_all_edges <= current_number_of_edges_)
	{
		return;
	}
	for (; count_of_all_edges > current_number_of_edges_; count_of_all_edges--)
	{
		bool edge_removed = RemoveEdge();
		while (!edge_removed)
		{
			edge_removed = RemoveEdge();
		}
	}
}
Graph* Graph::Generate()
{
	GenerateGraph();

	std::ostringstream out;
	print_function_(out);
	result_ = out.str();
	Test::Generate();
	return this;
}
void Graph::Print(std::ostream& _out) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	THROW(print_type_ != LIST_OF_EDGES && weight_ != nullptr, "Weights cannot be specified with not LIST_OF_EDGES printing modificator");
	_out << result_;
}
Graph * Graph::Buckle(bool _buckle)
{
	buckle_ = _buckle;
	return this;
}
Graph * Graph::Directed(bool _directed)
{
	directed_ = _directed;
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
long long Graph::VerticesCount()
{
	return current_number_of_vertices_;
}
long long Graph::EdgesCount()
{
	return current_number_of_edges_;
}
Graph::~Graph()
{
}

Graph* Graph::Clone() const
{
	Graph* graph_to_return = new Graph(number_of_vertices_, number_of_edges_, weight_, directed_, buckle_);
	graph_to_return->print_type_ = print_type_;
	graph_to_return->print_function_ = print_function_;
	graph_to_return->postprocess_function_ = postprocess_function_;
	return graph_to_return;
}

// GraphMerger

void GraphMerger::RearrangeConnectionMatrix(const std::vector<std::map<int, int>>& _rearrangment_maps, int _size ) // number_of_vertices
{
	THROW(_size > 10000, "Number of vertices must be less or equal 10000");
	std::vector<std::vector<bool> > all_graphs_connection_matrix(_size, std::vector<bool>(_size));	
	for (size_t i = 0; i < graphs_.size(); i++)
	{
		std::vector<std::vector<bool> > connection_matrix = graphs_[i]->ConnectionMatrix();
		for (size_t j = 0; j < connection_matrix.size(); j++)
		{
			for (size_t k = 0; k < connection_matrix[j].size(); k++)
			{
				all_graphs_connection_matrix[_rearrangment_maps[i].at(j)][_rearrangment_maps[i].at(k)] = connection_matrix[j][k];
			}
		}
	}
	std::ostringstream os;
	os << all_graphs_connection_matrix.size() << std::endl;
	for (size_t i = 0; i < all_graphs_connection_matrix.size(); i++)
	{
		for (size_t j = 0; j < all_graphs_connection_matrix[i].size(); j++)
		{
			os << all_graphs_connection_matrix[i][j] << " ";
		}
		os << std::endl;
	}
	result_ = os.str();
}

void GraphMerger::RearrangeConnectionList(const std::vector<std::map<int, int>>& _rearrangment_maps, int _size)
{
	std::vector<std::set<long long> > all_graphs_connection_list(_size);
	for (size_t i = 0; i < graphs_.size(); i++)
	{
		std::vector<std::set<long long> > connection_list = graphs_[i]->ConnectionList();
		for (size_t j = 0; j < connection_list.size(); j++)
		{
			for (auto neighbor : connection_list[j])
			{
				all_graphs_connection_list[_rearrangment_maps[i].at(j)].insert(_rearrangment_maps[i].at(neighbor));
			}
		}
	}
	std::ostringstream os;
	os << all_graphs_connection_list.size() << std::endl;
	for (size_t i = 0; i < all_graphs_connection_list.size(); i++)
	{
		os << all_graphs_connection_list[i].size() << " ";
		for (auto neighbor : all_graphs_connection_list[i])
		{
			os << neighbor + 1 << " ";
		}
		os << std::endl;
	}
	result_ = os.str();
}

void GraphMerger::RearrangeListOfEdges(const std::vector<std::map<int, int>>& _rearrangment_maps, int _size)
{
	std::vector<std::pair<long long, long long> > all_graphs_list_of_edges;
	for (size_t i = 0; i < graphs_.size(); i++)
	{
		std::vector<std::pair<long long, long long> > list_of_edges = graphs_[i]->ListOfEdges();
		for (size_t j = 0; j < list_of_edges.size(); j++)
		{
			// all_graphs_list_of_edges[_rearrangment_maps[i].at(j)].insert(_rearrangment_maps[i].at(neighbor));
			all_graphs_list_of_edges.push_back({ _rearrangment_maps[i].at(list_of_edges[j].first), _rearrangment_maps[i].at(list_of_edges[j].second) });
		}
	}
	std::random_shuffle(all_graphs_list_of_edges.begin(), all_graphs_list_of_edges.end(), Rand_with_mod);
	std::ostringstream os;
	os << all_graphs_list_of_edges.size() << std::endl;
	for (size_t i = 0; i < all_graphs_list_of_edges.size(); i++)
	{
		os << all_graphs_list_of_edges[i].first + 1 << " " << all_graphs_list_of_edges[i].second + 1 << std::endl;
	}
	result_ = os.str();
}

GraphMerger::GraphMerger()
{
	rearrange_function_ = std::bind(&GraphMerger::RearrangeConnectionList, this, std::placeholders::_1, std::placeholders::_2);
}

GraphMerger * GraphMerger::Add(Graph * _graph)
{
	graphs_.push_back(_graph->Clone());
	return this;
}

GraphMerger * GraphMerger::Generate()
{
	int number_of_vertices = 0;
	for (size_t i = 0; i < graphs_.size(); i++)
	{
		graphs_[i]->Generate();
		number_of_vertices += graphs_[i]->VerticesCount();
	}
	std::vector<int> rearrange_array( number_of_vertices );
	for (size_t i = 0; i < rearrange_array.size(); i++)
	{
		rearrange_array[i] = i;
	}
	std::random_shuffle(rearrange_array.begin(), rearrange_array.end(), Rand_with_mod);
	std::vector<std::map<int, int>> rearragment_maps(graphs_.size());
	for (size_t i = 0, index = 0; i < graphs_.size(); i++)
	{
		for (size_t j = 0; j < graphs_[i]->VerticesCount(); j++)
		{
			rearragment_maps[i][j] = rearrange_array[index++];
		}
	}
	rearrange_function_(rearragment_maps, number_of_vertices);
	Test::Generate();
	return this;
}

GraphMerger * GraphMerger::PrintType(Graph::PRINT_TYPE _print_type)
{
	print_type_ = _print_type;
	switch (print_type_)
	{
	case Graph::PRINT_TYPE::CONNECTION_MATRIX:
		rearrange_function_ = std::bind(&GraphMerger::RearrangeConnectionMatrix, this, std::placeholders::_1, std::placeholders::_2);
		break;
	case Graph::PRINT_TYPE::CONNECTION_LIST:
		rearrange_function_ = std::bind(&GraphMerger::RearrangeConnectionList, this, std::placeholders::_1, std::placeholders::_2);
		break;
	case Graph::PRINT_TYPE::LIST_OF_EDGES:
		rearrange_function_ = std::bind(&GraphMerger::RearrangeListOfEdges, this, std::placeholders::_1, std::placeholders::_2);
		break;
	default:
		break;
	}
	return this;
}

void GraphMerger::Print(std::ostream& _out) const
{
	THROW(!test_generated_, "Print() must be called after Generate()");
	_out << result_;
}

GraphMerger * GraphMerger::Clone() const
{
	GraphMerger* graph_merger_to_return = new GraphMerger();
	for (size_t i = 0; i < graphs_.size(); i++)
	{
		graph_merger_to_return->Add(graphs_[i]);
	}
	graph_merger_to_return->postprocess_function_ = postprocess_function_;
	return graph_merger_to_return;
}



