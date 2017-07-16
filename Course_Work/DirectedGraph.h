#ifndef DIRECTED_GRAPH___
#define DIRECTED_GRAPH___

#include"Graph.h"
#include<map>

class DirectedGraph : public Graph
{
private:
	int current_vertex_map_index_;
	std::map<int, int> shuffled_vertices_;
protected:
	virtual bool EdgeValidation(int, int);
	virtual void AddEdge(int, int);
public:
	DirectedGraph(PrimitiveTest<int>*, PrimitiveTest<int>*, bool = false, bool = false);
	virtual void Generate();
	virtual DirectedGraph* Clone() const;
	virtual ~DirectedGraph();
};


#endif
