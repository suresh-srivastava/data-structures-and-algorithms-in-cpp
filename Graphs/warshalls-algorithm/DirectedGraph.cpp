//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedGraph.cpp : Program to find out the path matrix using warshall's algorithm.

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

	public:
		DirectedGraph();
		~DirectedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void display();
		void warshallsAlgorithm();

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

void DirectedGraph::display()
{
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
			cout << adj[i][j] << " ";
        cout <<"\n";
    }
}//End of display()

void DirectedGraph::warshallsAlgorithm()
{
	int P[maxSize][maxSize];

	//Initializing P(-1)
	for(int i=0; i<nVertices; i++)
	{
		for(int j=0; j<nVertices; j++)
		{
			P[i][j] = adj[i][j];
		}
	}

	//P0,P1......Pn-1
	for(int k=0; k<nVertices; k++)
	{
		for(int i=0; i<nVertices; i++)
		{
			for(int j=0; j<nVertices; j++)
			{
				P[i][j] = (P[i][j] || (P[i][k] && P[k][j]));
			}
		}

		//Display P
		cout << "P" << k << " :\n";
		for(int i=0; i<nVertices; i++)
		{
     		for(int j=0; j<nVertices; j++)
				cout << P[i][j] << " ";
			cout <<"\n";
		}

	}//End of for

}//End of warshallsAlgorithm()

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

		dGraph.insertEdge("0","1");
		dGraph.insertEdge("0","3");
		dGraph.insertEdge("1","0");
		dGraph.insertEdge("1","2");
		dGraph.insertEdge("1","3");
		dGraph.insertEdge("2","3");
		dGraph.insertEdge("3","0");
		dGraph.insertEdge("3","2");

		//Display the graph
		dGraph.display();
		cout << "\n";

		cout << "Find the path matrix :\n";
		dGraph.warshallsAlgorithm();
	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()

