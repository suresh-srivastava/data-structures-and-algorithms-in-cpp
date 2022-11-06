//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//UndirectedGraph.cpp : Program for traversing an undirected graph through DFS using recursion and finding out that graph is 
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
		int predecessor;

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
		int INITIAL;
		int VISITED;
		int FINISHED;
		bool hasCycle;

	private:
		int getIndex(string vertexName);
		bool isAdjacent(int u, int v);
		void dfs(int vertex);

	public:
		UndirectedGraph();
		~UndirectedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void display();
		bool isCyclic();

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

	INITIAL = 0;
	VISITED = 1;
	FINISHED = 2;

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
	for(int i=0; i<nVertices; i++)
	{
        if(vertexName == vertexList[i]->name)
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

void UndirectedGraph::dfs(int vertex)
{
	vertexList[vertex]->state = VISITED;

	for(int i=0; i<nVertices; i++)
	{
		if(isAdjacent(vertex,i) && vertexList[vertex]->predecessor!=i)
		{
			if(vertexList[i]->state == INITIAL)
			{
				//Its Tree Edge
				vertexList[i]->predecessor = vertex;
				dfs(i);
			}
			else if(vertexList[i]->state == VISITED)
			{
				//Its Back Edge
				hasCycle = true;
			}

		}//End of if
	}//End of for

	vertexList[vertex]->state = FINISHED;

}//End of dfs()

bool UndirectedGraph::isCyclic()
{
	//Initially all the vertices will have INITIAL state
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->state = INITIAL;
	}

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
	UndirectedGraph uGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		//Graph is acyclic
		//uGraph.insertVertex("0");
		//uGraph.insertVertex("1");
		//uGraph.insertVertex("2");
		//uGraph.insertVertex("3");
		//uGraph.insertVertex("4");
		//uGraph.insertVertex("5");

		//uGraph.insertEdge("0","1");
		//uGraph.insertEdge("1","3");
		//uGraph.insertEdge("2","3");
		//uGraph.insertEdge("3","4");
		//uGraph.insertEdge("4","5");

		//Graph is cyclic
		uGraph.insertVertex("0");
		uGraph.insertVertex("1");
		uGraph.insertVertex("2");
		uGraph.insertVertex("3");
		uGraph.insertVertex("4");
		uGraph.insertVertex("5");

		uGraph.insertEdge("0","1");
		uGraph.insertEdge("0","2");
		uGraph.insertEdge("1","3");
		uGraph.insertEdge("2","3");
		uGraph.insertEdge("3","4");
		uGraph.insertEdge("4","5");

		//Display the graph
		uGraph.display();
		cout << "\n";

		if(uGraph.isCyclic())
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
