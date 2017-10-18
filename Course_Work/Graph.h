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
	/// Enum to pass to PrintType function
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
	/// \cond
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
	/// \endcond
public:
	/// Graph
	/// \param _number_of_vertices - number of vertices in Graph
	/// \param _number_of_edges - number of edges in Graph
	/// \param _weights - weights if needed. Default: nullptr
	/// \param _directed - specified is Graph directed or not. Default: false
	/// \param _buckle - specified is Graph contains self-loops or not. Default: false
	/// \exception Does not raise any exceptions
	///
	/// Here is an example for Graph. You can try it by taking it from Graph.h
	/*!
	\code
	int main()
	{
		PrimitiveTest<int>* vertices_count = CreateNumber(3, 5);
		PrimitiveTest<int>* edges_count = CreateNumber(5, 10);
		Graph* graph = new Graph(vertices_count, edges_count);
		graph->Buckle()->Directed();
		graph->PrintType(Graph::LIST_OF_EDGES);
		graph->Generate();
		graph->Print();
		delete graph;
		delete edges_count;
		delete vertices_count;
	}
	\endcode
	*/
	///
	/// The shorter version
	///
	/*!
	\code
	int main()
	{
		Graph* graph = new Graph(CreateNumber(3, 5), CreateNumber(5, 10));
		graph->Buckle()->Directed()->PrintType(Graph::LIST_OF_EDGES)->Generate()->Print();
		delete graph;
	}
	\endcode
	*/

	Graph(PrimitiveTest<int>* _number_of_vertices, PrimitiveTest<int>* _number_of_edges, Test* _weights = nullptr, bool _directed = false, bool _buckle = false);
	virtual Graph* Generate();
	virtual void Print(std::ostream& = std::cout) const;
	virtual Graph* Clone() const;
	/// Specifies whether there should be self-loops in the graph
	/// \param _buckle - bool to specifying self-looping
	/// \returns this
	virtual Graph* Buckle(bool _buckle = true);
	/// Specifies whether the graph should be directed
	/// \param _buckle - bool to specifying are graph directed or not
	/// \returns this
	virtual Graph* Directed(bool _directed = true);
	/// Specifies the way to output tha graph. For now available only 3 way to output:
	/// 1. CONNECTION_MATRIX - count of vertices, if there is an edge (v, u), then matrix[v][u]=1:\n
	/// <table style="text-align:center;width:15%;border-collapse: collapse;border: 1px solid black;" border="1">
	///   <tr> <td>n</td> </tr>
	///   <tr> <td>0</td> <td>1</td> <td>...</td> <td>1</td> </tr>
	///   <tr> <td>0</td> <td>1</td> <td>...</td> <td>0</td> </tr>
	///   <tr> <td>...</td> <td>...</td> <td>...</td> <td>...</td> </tr>
	///   <tr> <td>1</td> <td>0</td> <td>...</td> <td>1</td> </tr>
	/// </table>
	/// <br>
	/// 2. CONNECTION_LIST - count of vertices, list of neighbors for each of vertex:\n
	/// <br>
	/// <table style="text-align:center;width:15%;border-collapse: collapse;border: 1px solid black;" border="1">
	///   <tr> <td>n</td> </tr>
	///   <tr> <td>m<sub>1</sub></td> <td>v<sub>11</sub></td> <td>...</td> <td>...</td> <td>...</td> <td>v<sub>1m<sub>1</sub></sub></td> </tr>
	///   <tr> <td>m<sub>2</sub></td> <td>v<sub>21</sub></td> <td>...</td> <td>v<sub>2m<sub>2</sub></sub></td> </tr>
	///   <tr> <td>...</td> <td>...</td> <td>...</td> <td>...</td> </tr>
	///   <tr> <td>m<sub>n</sub></td> <td>v<sub>n1</sub></td> <td>...</td> <td>...</td> <td>v<sub>nm<sub>n</sub></sub></td> </tr>
	/// </table>
	/// <br>
	/// 3. LIST_OF_EDGES - count of vertices, if there is an edge (v, u), then must be presented v u line: \n
	/// <br>
	/// <table style="text-align:center;width:15%;border-collapse: collapse;border: 1px solid black;" border="1">
	///   <tr> <td>n</td> </tr>
	///   <tr> <td>v<sub>1</sub></td> <td>u<sub>1</sub></td> </tr>
	///   <tr> <td>v<sub>2</sub></td> <td>u<sub>2</sub></td> </tr>
	///   <tr> <td>...</td> <td>...</td> </tr>
	///   <tr> <td>v<sub>n</sub></td> <td>u<sub>n</sub></td> </tr>
	/// </table>
	/// \param PRINT_TYPE enum
	virtual Graph* PrintType(PRINT_TYPE _print_type);
	/// \returns count of vertices
	virtual long long VerticesCount();
	/// \returns count of edges
	virtual long long EdgesCount();
	virtual ~Graph();
};

#endif
