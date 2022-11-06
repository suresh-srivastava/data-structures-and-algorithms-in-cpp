//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//UndirectedWeightedGraph.cpp : Program for undirected graph with weight on edge using adjacency matrix.

#include<iostream>
#include<string>
using namespace std;

static const int maxSize = 30;

class Vertex
{
	public:
		string name;

	public:
		Vertex(string name)
		{
			this->name = name;
		}
};//End of class Vertex

class UndirectedWeightedGraph
{
	private:
		int nVertices;
		int nEdges;
		int adj[maxSize][maxSize];
		Vertex *vertexList[maxSize];

	private:
		int getIndex(string vertexName);
		bool isAdjacent(int u, int v);

	public:
		UndirectedWeightedGraph();
		~UndirectedWeightedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination, int weight);
		void deleteEdge(string source, string destination);
		void display();
		bool edgeExists(string source, string destination);
		int getDegree(string vertex);

};//End of class UndirectedWeightedGraph

UndirectedWeightedGraph::UndirectedWeightedGraph()
{
	nVertices = 0;
	nEdges = 0;

	for(int i=0; i<maxSize; i++)
	{
		for(int j=0; j<maxSize; j++)
		{
			adj[i][j] = 0;
		}
	}
}//End of UndirectedWeightedGraph()

UndirectedWeightedGraph::~UndirectedWeightedGraph()
{
	for(int i=0; i<nVertices; i++)
	{
		delete vertexList[i];
	}
}//End of ~UndirectedWeightedGraph()

void UndirectedWeightedGraph::insertVertex(string vertexName)
{
	vertexList[nVertices++] = new Vertex(vertexName);
}//End of insertVertex()

int UndirectedWeightedGraph::getIndex(string vertexName)
{
	for(int i=0; i<nVertices; i++ )
	{
        if(vertexName == vertexList[i]->name)
            return i;
	}

	throw exception("Invalid Vertex");

}//End of getIndex()

void UndirectedWeightedGraph::insertEdge(string source, string destination, int weight)
{
	int u = getIndex(source);
	int v = getIndex(destination);
            
	if(u == v)
		cout << "Not a valid edge\n";
	else if(adj[u][v] != 0)
		cout << "Edge already present\n";
	else  
	{
		adj[u][v] = weight;
		adj[v][u] = weight;
		nEdges++;
	}
}//End of insertEdge()

void UndirectedWeightedGraph::deleteEdge(string source, string destination)
{
	int u = getIndex(source);
	int v = getIndex(destination);

	if(adj[u][v] != 0)
	{
		adj[u][v] = 0;
		adj[v][u] = 0;
		nEdges--;
	}
	else
		cout << "Edge does not exist\n";
}//End of deleteEdge()

void UndirectedWeightedGraph::display()
{
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
			cout << adj[i][j] << " ";
        cout <<"\n";
    }
}//End of display()

bool UndirectedWeightedGraph::isAdjacent(int u, int v)
{
	return (adj[u][v] != 0);
}//End of isAdjacent()

//Returns true if edge exists
bool UndirectedWeightedGraph::edgeExists(string source, string destination)
{
	return isAdjacent(getIndex(source), getIndex(destination));
}//End of edgeExists()

//Returns number of edges from a vertex
int UndirectedWeightedGraph::getDegree(string vertex)
{
	int u = getIndex(vertex); 
   
	int degree = 0;
    for(int v=0; v<nVertices; v++)
	{
        if(adj[u][v] != 0)
			degree++;
	}

    return degree;
}//End of getDegree()

int main()
{
	UndirectedWeightedGraph uwGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		uwGraph.insertVertex("0");
		uwGraph.insertVertex("1");
		uwGraph.insertVertex("2");
		uwGraph.insertVertex("3");

		uwGraph.insertEdge("0","3",1);
		uwGraph.insertEdge("1","2",2);
		uwGraph.insertEdge("2","3",3);
		uwGraph.insertEdge("3","1",4);
		uwGraph.insertEdge("0","2",5);

		//Display the graph
		uwGraph.display();
		cout << "\n";

		//Deleting an edge
		uwGraph.deleteEdge("0","2");

		//Display the graph
		uwGraph.display();

		//Check if there is an edge between two vertices
		cout << "Edge exist : " << (uwGraph.edgeExists("2","3") ? "True" : "False") << "\n";

		//Display Indegree and degree of a vertex\n";
		cout << "Degree : " << uwGraph.getDegree("3") << "\n";

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()

