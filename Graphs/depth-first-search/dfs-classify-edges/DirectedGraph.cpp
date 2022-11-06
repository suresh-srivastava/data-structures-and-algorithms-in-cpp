//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedGraph.cpp : Program for traversing a directed graph through DFS using recursion and classify all the edges in graph

#include<iostream>
#include<string>
#include<stack>
using namespace std;

static const int maxSize = 30;

class Vertex
{
	public:
		string name;
		int state;
		int discoveryTime;
		int finishingTime;

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
		int INITIAL;
		int VISITED;
		int FINISHED;
		static int time;

	private:
		int getIndex(string vertexName);
		bool isAdjacent(int u, int v);
		void dfs(int vertex);

	public:
		DirectedGraph();
		~DirectedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void display();
		void dfsClassifyEdges();

};//End of class DirectedGraph

int DirectedGraph::time;

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

	INITIAL = 0;
	VISITED = 1;
	FINISHED = 2;

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
	for( int i = 0; i < nVertices; i++ )
	{
        if (vertexName == vertexList[i]->name)
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
  
bool DirectedGraph::isAdjacent(int u, int v)
{
	return (adj[u][v] != 0);
}//End of isAdjacent()

void DirectedGraph::dfs(int vertex)
{
	vertexList[vertex]->state = VISITED;
	vertexList[vertex]->discoveryTime = ++time;

	for(int i=0; i<nVertices; i++)
	{
		//Checking for adjacent vertices with INITIAL state
		if(isAdjacent(vertex,i))
		{
			if(vertexList[i]->state==INITIAL)
			{
				cout << "Tree Edge - (" << vertexList[vertex]->name << "-" << vertexList[i]->name << ")\n";
				dfs(i);
			}
			else if(vertexList[i]->state==VISITED)
			{
				cout << "Back Edge - (" << vertexList[vertex]->name << "-" << vertexList[i]->name << ")\n";
			}
			else if(vertexList[vertex]->discoveryTime < vertexList[i]->discoveryTime)
			{
				cout << "Forward Edge - (" << vertexList[vertex]->name << "-" << vertexList[i]->name << ")\n";
			}
			else
			{
				cout << "Cross Edge - (" << vertexList[vertex]->name << "-" << vertexList[i]->name << ")\n";
			}
		}
	}//End of for

	vertexList[vertex]->state = FINISHED;
	vertexList[vertex]->finishingTime = ++time;

}//End of dfs()

void DirectedGraph::dfsClassifyEdges()
{
	//Initially all the vertices will have INITIAL state
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->state = INITIAL;
	}

	time = 0;

	for(int v=0; v<nVertices; v++)
	{
		if(vertexList[v]->state == INITIAL)
			dfs(v);
	}

	cout << "\n";
}//End of dfsClassifyEdges()

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
		dGraph.insertVertex("4");
		dGraph.insertVertex("5");
		dGraph.insertVertex("6");
		dGraph.insertVertex("7");
		dGraph.insertVertex("8");
		dGraph.insertVertex("9");
		dGraph.insertVertex("10");
		dGraph.insertVertex("11");
		dGraph.insertVertex("12");
		dGraph.insertVertex("13");
		dGraph.insertVertex("14");
		dGraph.insertVertex("15");

		dGraph.insertEdge("0","1");
		dGraph.insertEdge("0","2");
		dGraph.insertEdge("0","3");
		dGraph.insertEdge("1","2");
		dGraph.insertEdge("3","2");
		dGraph.insertEdge("4","1");
		dGraph.insertEdge("4","5");
		dGraph.insertEdge("4","6");
		dGraph.insertEdge("4","7");
		dGraph.insertEdge("5","6");
		dGraph.insertEdge("6","3");
		dGraph.insertEdge("6","9");
		dGraph.insertEdge("7","8");
		dGraph.insertEdge("8","4");
		dGraph.insertEdge("8","5");
		dGraph.insertEdge("8","9");
		dGraph.insertEdge("9","5");
		dGraph.insertEdge("10","11");
		dGraph.insertEdge("10","14");
		dGraph.insertEdge("11","8");
		dGraph.insertEdge("11","12");
		dGraph.insertEdge("11","14");
		dGraph.insertEdge("11","15");
		dGraph.insertEdge("12","15");
		dGraph.insertEdge("13","10");
		dGraph.insertEdge("14","13");
		dGraph.insertEdge("14","15");

		//Display the graph
		dGraph.display();
		cout << "\n";

		//classify all the edges in graph
		dGraph.dfsClassifyEdges();

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()
