#ifndef GRAPH___
#define GRAPH___

#include"Test.h"
#include"PrimitiveTest.h"
#include<vector>
#include<set>
#include<functional>


class Graph : public Test
{
public:
	enum PRINT_TYPE { CONNECTION_MATRIX, CONNECTION_LIST, LIST_OF_EDGES };
	/*
	CONNECTION_MATRIX(count of vertices, if there is an edge (v, u), then matrix[v][u]=1):
	n
	0 1 ... 1
	0 0 ... 0
	.   .
	.     .
	1 0 ... 1
	CONNECTION_LIST(count of vertices, list of neighbors for each of vertex):
	n
	m1 v1{1} ... v1{m1}
	m2 v2{1} ... v2{m2}
	.
	.
	mn vn{1} ... vn{mm}
	LIST_OF_EDGES(count of vertices, if there is an edge (v, u), then must be presented v u line):
	n
	v{1} u{1}
	.
	.
	v{n} u{n}
	*/
protected:
	PrimitiveTest<int> *number_of_vertices_, *number_of_edges_;
	Test* weight_;
	long long current_number_of_vertices_, current_number_of_edges_;
	std::vector< std::set<long long> > graph_;
	std::set<std::pair<long long, long long> >  fixed_tree_;
	std::function<void(std::ostream&)> print_function_;
	long long number_of_already_added_edges_;
	bool buckle_;
	bool directed_;
	PRINT_TYPE print_type_;
	
	virtual bool AddEdge();
	virtual void AddEdge(long long, long long);
	virtual bool RemoveEdge();
	virtual void RemoveEdge(long long, long long);
	virtual int  AddVertex();
	virtual void FixingTree();
	virtual void GenerateGraph();
	virtual void GenerateSmallGraph();
	virtual void GenerateLargeGraph();
	virtual void CreateTree();
	virtual std::vector<std::vector<bool> > ConnectionMatrix();
	virtual void PrintConnectionMatrix(std::ostream&);
	virtual std::vector<std::set<long long> > ConnectionList();
	virtual void PrintConnectionList(std::ostream&);
	virtual std::vector<std::pair<long long, long long> > ListOfEdges();
	virtual void PrintListOfEdges(std::ostream&);
public:
	Graph(PrimitiveTest<int>*, PrimitiveTest<int>*, Test* = NULL, bool = false, bool = false);
	virtual void Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual Graph* Clone() const;
	virtual Graph* Buckle(bool = true);
	virtual Graph* PrintType(PRINT_TYPE);
	virtual long long VerticesCount();
	virtual long long EdgesCount();
	virtual ~Graph();
};

#endif
