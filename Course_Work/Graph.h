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
	int current_number_of_vertices_, current_number_of_edges_;
	std::vector< std::set<int> > graph_;
	std::function<void(std::ostream&)> print_function_;
	bool acyclic_;
	bool buckle_;
	PRINT_TYPE print_type_;
	
	virtual void GenerateGraph();
	virtual int AddVertex();
	virtual bool AddEdge();
	virtual bool EdgeValidation(int, int) = 0;
	virtual void AddEdge(int, int) = 0;
	virtual std::vector<std::vector<bool> > ConnectionMatrix();
	virtual void PrintConnectionMatrix(std::ostream&);
	virtual std::vector<std::set<int> > ConnectionList();
	virtual void PrintConnectionList(std::ostream&);
	virtual std::vector<std::pair<int, int> > ListOfEdges();
	virtual void PrintListOfEdges(std::ostream&);
public:
	Graph(PrimitiveTest<int>*, PrimitiveTest<int>*, bool = false, bool = false);
	virtual void Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual Graph* Clone() const = 0;
	virtual Graph* Acyclic(bool = true);
	virtual Graph* Buckle(bool = true);
	virtual Graph* PrintType(PRINT_TYPE);
	virtual ~Graph();
};


#endif
