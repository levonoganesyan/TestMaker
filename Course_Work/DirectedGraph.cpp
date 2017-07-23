
#include"DirectedGraph.h"
#include"ConstPrimitiveTest.h"
#include"RangePrimitiveTest.h"


DirectedGraph::DirectedGraph(PrimitiveTest<int>* _number_of_vertices, PrimitiveTest<int>* _number_of_edges, PrimitiveTest<int>* _weights, bool _acyclic, bool _buckle)
	: Graph(_number_of_vertices, _number_of_edges, _weights, _acyclic, _buckle)
	, current_vertex_map_index_(0)
{
	this->Generate();
}

bool DirectedGraph::EdgeValidation(int _start, int _end)
{	
	if (!buckle_ && _start == _end)
		return false;
	return true;
}
void DirectedGraph::AddEdge(int _start, int _end)
{
	if (acyclic_)
	{
		if (shuffled_vertices_.find(_start) == shuffled_vertices_.end())
		{
			shuffled_vertices_[_start] = current_vertex_map_index_++;
		}
		if (shuffled_vertices_.find(_end) == shuffled_vertices_.end())
		{
			shuffled_vertices_[_end] = current_vertex_map_index_++;
		}
		if (shuffled_vertices_[_start] > shuffled_vertices_[_end])
		{
			_start ^= _end ^= _start ^= _end;
		}
	}
	graph_[_start].insert(_end);
}
void DirectedGraph::Generate()
{
	current_vertex_map_index_ = 0;
	shuffled_vertices_.clear();
	Graph::Generate();
}
DirectedGraph * DirectedGraph::Clone() const
{
	DirectedGraph* graph = new DirectedGraph(number_of_vertices_, number_of_edges_);
	graph->graph_ = graph_;
	graph->buckle_ = buckle_;
	graph->acyclic_ = acyclic_;
	graph->print_type_ = print_type_;
	graph->print_function_ = print_function_;
	return graph;
}
DirectedGraph::~DirectedGraph()
{
}
