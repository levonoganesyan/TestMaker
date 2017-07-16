
#include"NonDirectedGraph.h"
#include"ConstPrimitiveTest.h"
#include"RangePrimitiveTest.h"


NonDirectedGraph::DSU::DSU(int n)
{
	parent.resize(n);
	for (int i = 0; i < n; i++)
	{
		make_set(i);
	}
}
void NonDirectedGraph::DSU::make_set(int _v)
{
	parent[_v] = _v;
}
int NonDirectedGraph::DSU::find_set(int _v)
{
	return parent[_v] == _v ? _v : parent[_v] = find_set(parent[_v]);
}
bool NonDirectedGraph::DSU::union_sets(int _first, int _second)
{
	_first = find_set(_first);
	_second = find_set(_second);
	if (_second == _first)
	{
		return false;
	}
	else
	{
		parent[_second] = _first;
		return true;
	}
}




NonDirectedGraph::NonDirectedGraph(PrimitiveTest<int>* _number_of_vertices, PrimitiveTest<int>* _number_of_edges, bool _acyclic, bool _buckle)
	: Graph(_number_of_vertices, _number_of_edges, _acyclic, _buckle)
	, dsu_(NULL)
{
	this->Generate();
}

bool NonDirectedGraph::EdgeValidation(int _start, int _end)
{
	if (!buckle_ && _start == _end)
		return false;
	if (dsu_ == NULL)
		dsu_ = new DSU(graph_.size());
	if (acyclic_ && !(dsu_->union_sets(_start, _end)))
		return false;
	return true;
}
void NonDirectedGraph::AddEdge(int _start, int _end)
{
	graph_[_start].insert(_end);
	graph_[_end].insert(_start);
}
void NonDirectedGraph::Generate()
{
	delete dsu_;
	dsu_ = NULL;
	Graph::Generate();
}
NonDirectedGraph * NonDirectedGraph::Clone() const
{
	NonDirectedGraph* graph = new NonDirectedGraph(number_of_vertices_, number_of_edges_);
	graph->graph_ = graph_;
	graph->buckle_ = buckle_;
	graph->acyclic_ = acyclic_;
	graph->print_type_ = print_type_;
	graph->print_function_ = print_function_;
	return graph;
}
NonDirectedGraph::~NonDirectedGraph()
{
	delete dsu_;
}
