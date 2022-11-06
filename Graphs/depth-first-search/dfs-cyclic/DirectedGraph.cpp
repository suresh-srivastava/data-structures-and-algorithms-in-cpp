//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedGraph.cpp : Program for traversing a directed graph through DFS using recursion and finding out that graph is 
//cyclic or not

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
		bool hasCycle;

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
		bool isCyclic();

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
	for(int i=0; i<nVertices; i++)
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
				//Its Tree Edge
				dfs(i);
			}
			else if(vertexList[i]->state==VISITED)
			{
				//Its Back Edge
				hasCycle = true;
			}
		}
	}//End of for

	vertexList[vertex]->state = FINISHED;
	vertexList[vertex]->finishingTime = ++time;

}//End of dfs()

bool DirectedGraph::isCyclic()
{
	//Initially all the vertices will have INITIAL state
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->state = INITIAL;
	}

	time = 0;
	hasCycle = false;

	for(int v=0; v<nVertices; v++)
	{
		if(vertexList[v]->state == INITIAL)
			dfs(v);
	}

	return hasCycle;
}//End of isCyclic()

int main()
{
	DirectedGraph dGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		//Graph is acyclic
		//dGraph.insertVertex("0");
		//dGraph.insertVertex("1");
		//dGraph.insertVertex("2");
		//dGraph.insertVertex("3");

		//dGraph.insertEdge("0","1");
		//dGraph.insertEdge("0","2");
		//dGraph.insertEdge("0","3");
		//dGraph.insertEdge("1","2");
		//dGraph.insertEdge("3","2");

		//Graph is cyclic
		dGraph.insertVertex("0");
		dGraph.insertVertex("1");
		dGraph.insertVertex("2");
		dGraph.insertVertex("3");

		dGraph.insertEdge("0","1");
		dGraph.insertEdge("0","2");
		dGraph.insertEdge("1","2");
		dGraph.insertEdge("2","3");
		dGraph.insertEdge("3","0");

		//Display the graph
		dGraph.display();
		cout << "\n";

		if(dGraph.isCyclic())
			cout << "Graph is Cyclic\n";
		else
			cout << "Graph is Acyclic\n";

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()
