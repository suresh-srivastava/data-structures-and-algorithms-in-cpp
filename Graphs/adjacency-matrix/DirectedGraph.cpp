//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedGraph.cpp : Program for directed graph using adjacency matrix.

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

class DirectedGraph
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
		DirectedGraph();
		~DirectedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void deleteEdge(string source, string destination);
		void display();
		bool edgeExists(string source, string destination);
		int getOutdegree(string vertex);
		int getIndegree(string vertex);

};//End of class DirectedGraph

DirectedGraph::DirectedGraph()
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
}//End of DirectedGraph()

DirectedGraph::~DirectedGraph()
{
	for(int i=0; i<nVertices; i++)
	{
		delete vertexList[i];
	}
}//End of ~DirectedGraph()

void DirectedGraph::insertVertex(string vertexName)
{
	vertexList[nVertices++] = new Vertex(vertexName);
}//End of insertVertex()

int DirectedGraph::getIndex(string vertexName)
{
	for(int i=0; i<nVertices; i++ )
	{
        if(vertexName == vertexList[i]->name)
            return i;
	}

	throw exception("Invalid Vertex");

}//End of getIndex()

void DirectedGraph::insertEdge(string source, string destination)
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
		nEdges++;
	}
}//End of insertEdge()

void DirectedGraph::deleteEdge(string source, string destination)
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

void DirectedGraph::display()
{
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
			cout << adj[i][j] << " ";
        cout <<"\n";
    }
}//End of display()

bool DirectedGraph::isAdjacent(int u, int v)
{
	return (adj[u][v] != 0);
}//End of isAdjacent()

bool DirectedGraph::edgeExists(string source, string destination)
{
	return isAdjacent(getIndex(source), getIndex(destination));
}//End of edgeExists()

//Returns number of edges going out from a vertex
int DirectedGraph::getOutdegree(string vertex)
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
int DirectedGraph::getIndegree(string vertex)
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
	DirectedGraph dGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		dGraph.insertVertex("0");
		dGraph.insertVertex("1");
		dGraph.insertVertex("2");
		dGraph.insertVertex("3");

		dGraph.insertEdge("0","3");
		dGraph.insertEdge("1","2");
		dGraph.insertEdge("2","3");
		dGraph.insertEdge("3","1");
		dGraph.insertEdge("0","2");

		//Display the graph
		dGraph.display();
		cout << "\n";

		//Deleting an edge
		dGraph.deleteEdge("0","2");

		//Display the graph
		dGraph.display();

		//Check if there is an edge between two vertices
		cout << "Edge exist : " << (dGraph.edgeExists("2","3") ? "True" : "False") << "\n";

		//Display Indegree and Outdegree of a vertex
		cout << "Outdegree : " << dGraph.getOutdegree("3") << "\n";
		cout << "Indegree : " << dGraph.getIndegree("3") << "\n";

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()

