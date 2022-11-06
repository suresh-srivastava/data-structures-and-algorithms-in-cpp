//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//UndirectedGraph.cpp : Program for undirected graph using adjacency matrix.

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

class UndirectedGraph
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
		UndirectedGraph();
		~UndirectedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void deleteEdge(string source, string destination);
		void display();
		bool edgeExists(string source, string destination);
		int getDegree(string vertex);

};//End of class UndirectedGraph

UndirectedGraph::UndirectedGraph()
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
}//End of UndirectedGraph()

UndirectedGraph::~UndirectedGraph()
{
	for(int i=0; i<nVertices; i++)
	{
		delete vertexList[i];
	}
}//End of ~UndirectedGraph()

void UndirectedGraph::insertVertex(string vertexName)
{
	vertexList[nVertices++] = new Vertex(vertexName);
}//End of insertVertex()

int UndirectedGraph::getIndex(string vertexName)
{
	for( int i = 0; i < nVertices; i++ )
	{
        if (vertexName == vertexList[i]->name)
            return i;
	}

	throw exception("Invalid Vertex");

}//End of getIndex()

void UndirectedGraph::insertEdge(string source, string destination)
{
	int u = getIndex(source);
	int v = getIndex(destination);
            
	if(u == v)
		cout << "Not a valid edge\n";
	else if(adj[u][v] != 0)
		cout << "Edge already present\n";
	else  
	{
		adj[u][v] = 1;
		adj[v][u] = 1;
		nEdges++;
	}
}//End of insertEdge()

void UndirectedGraph::deleteEdge(string source, string destination)
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

void UndirectedGraph::display()
{
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
			cout << adj[i][j] << " ";
        cout <<"\n";
    }
}//End of display()

bool UndirectedGraph::isAdjacent(int u, int v)
{
	return (adj[u][v] != 0);
}//End of isAdjacent()

//Returns true if edge exists
bool UndirectedGraph::edgeExists(string source, string destination)
{
	return isAdjacent(getIndex(source), getIndex(destination));
}//End of edgeExists()

//Returns number of edges from a vertex
int UndirectedGraph::getDegree(string vertex)
{
	int u = getIndex(vertex); 
   
	int degree = 0;
    for(int v = 0; v<nVertices; v++)
	{
        if(adj[u][v] != 0)
			degree++;
	}

    return degree;
}//End of getDegree()

int main()
{
	UndirectedGraph uGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		uGraph.insertVertex("0");
		uGraph.insertVertex("1");
		uGraph.insertVertex("2");
		uGraph.insertVertex("3");

		uGraph.insertEdge("0","3");
		uGraph.insertEdge("1","2");
		uGraph.insertEdge("2","3");
		uGraph.insertEdge("3","1");
		uGraph.insertEdge("0","2");

		//Display the graph
		uGraph.display();
		cout << "\n";

		//Deleting an edge
		uGraph.deleteEdge("0","2");

		//Display the graph
		uGraph.display();

		//Check if there is an edge between two vertices
		cout << "Edge exist : " << (uGraph.edgeExists("2","3") ? "True" : "False") << "\n";

		//Display Indegree and degree of a vertex\n";
		cout << "Degree : " << uGraph.getDegree("3") << "\n";

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()

