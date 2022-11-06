//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedWeightedGraph.cpp : Program for directed graph with weight on edge using adjacency matrix.

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

class DirectedWeightedGraph
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
		DirectedWeightedGraph();
		~DirectedWeightedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination, int weight);
		void deleteEdge(string source, string destination);
		void display();
		bool edgeExists(string source, string destination);
		int getOutdegree(string vertex);
		int getIndegree(string vertex);

};//End of class DirectedWeightedGraph

DirectedWeightedGraph::DirectedWeightedGraph()
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
}//End of DirectedWeightedGraph()

DirectedWeightedGraph::~DirectedWeightedGraph()
{
	for(int i=0; i<nVertices; i++)
	{
		delete vertexList[i];
	}
}//End of ~DirectedWeightedGraph()

void DirectedWeightedGraph::insertVertex(string vertexName)
{
	vertexList[nVertices++] = new Vertex(vertexName);
}//End of insertVertex()

int DirectedWeightedGraph::getIndex(string vertexName)
{
	for(int i=0; i<nVertices; i++ )
	{
        if(vertexName == vertexList[i]->name)
            return i;
	}

	throw exception("Invalid Vertex");

}//End of getIndex()

void DirectedWeightedGraph::insertEdge(string source, string destination, int weight)
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
		nEdges++;
	}
}//End of insertEdge()

void DirectedWeightedGraph::deleteEdge(string source, string destination)
{
	int u = getIndex(source);
	int v = getIndex(destination);

	if(adj[u][v] != 0)
	{
		adj[u][v] = 0;
		nEdges--;
	}
	else
	{
		cout << "Edge doesn't exist\n";
	}
}//End of deleteEdge()

void DirectedWeightedGraph::display()
{
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
			cout << adj[i][j] << " ";
        cout <<"\n";
    }
}//End of display()

bool DirectedWeightedGraph::isAdjacent(int u, int v)
{
	return (adj[u][v] != 0);
}//End of isAdjacent()

//Returns true if edge exists
bool DirectedWeightedGraph::edgeExists(string source, string destination)
{
	return isAdjacent(getIndex(source), getIndex(destination));
}//End of edgeExists()

//Returns number of edges going out from a vertex
int DirectedWeightedGraph::getOutdegree(string vertex)
{
	int u = getIndex(vertex); 
   
	int outdegree = 0;
    for(int v = 0; v<nVertices; v++)
	{
        if(adj[u][v] != 0)
			outdegree++;
	}

    return outdegree;
}//End of getOutdegree()
   
//Returns number of edges coming to a vertex
int DirectedWeightedGraph::getIndegree(string vertex)
{
    int u = getIndex(vertex);
   
    int indegree = 0;
    for(int v=0; v<nVertices; v++)
	{
        if(adj[v][u] != 0)
            indegree++;
	}

    return indegree;
}//End of getIndegree()

int main()
{
	DirectedWeightedGraph dwGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		dwGraph.insertVertex("0");
		dwGraph.insertVertex("1");
		dwGraph.insertVertex("2");
		dwGraph.insertVertex("3");

		dwGraph.insertEdge("0","3",1);
		dwGraph.insertEdge("1","2",2);
		dwGraph.insertEdge("2","3",3);
		dwGraph.insertEdge("3","1",4);
		dwGraph.insertEdge("0","2",5);

		//Display the graph
		dwGraph.display();
		cout << "\n";

		//Deleting an edge
		dwGraph.deleteEdge("0","2");

		//Display the graph
		dwGraph.display();

		//Check if there is an edge between two vertices
		cout << "Edge exist : " << (dwGraph.edgeExists("2","3") ? "True" : "False") << "\n";

		//Display Indegree and outdegree of a vertex\n";
		cout << "Outdegree : " << dwGraph.getOutdegree("3") << "\n";
		cout << "Indegree : " << dwGraph.getIndegree("3") << "\n";

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()

