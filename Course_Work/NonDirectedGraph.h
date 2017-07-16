#ifndef NON_DIRECTED_GRAPH___
#define NON_DIRECTED_GRAPH___

#include"Graph.h"


class NonDirectedGraph : public Graph
{
private:
	class DSU
	{
		std::vector<int> parent;
		void make_set(int);
		int find_set(int);
	public:
		DSU(int);
		bool union_sets(int, int);
	};
	DSU* dsu_;
protected:
	virtual bool EdgeValidation(int, int);
	virtual void AddEdge(int, int);
public:
	NonDirectedGraph(PrimitiveTest<int>*, PrimitiveTest<int>*, bool = false, bool = false);
	virtual void Generate();
	virtual NonDirectedGraph* Clone() const;
	virtual ~NonDirectedGraph();
};


#endif
