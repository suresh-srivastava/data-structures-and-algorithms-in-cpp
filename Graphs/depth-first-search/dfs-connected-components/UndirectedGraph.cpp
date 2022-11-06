//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//UndirectedGraph.cpp : Program to find connected components in an undirected graph.

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
		int componentNumber;

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

	private:
		int getIndex(string vertexName);
		bool isAdjacent(int u, int v);
		void dfs(int vertex, int cn);

	public:
		UndirectedGraph();
		~UndirectedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void display();
		void connectedComponent();

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

void UndirectedGraph::dfs(int vertex, int cn)
{
	stack<int> dfsStack;

	//Push the start vertex into stack
	dfsStack.push(vertex);

	while(!dfsStack.empty())
	{
		vertex = dfsStack.top();
		dfsStack.pop();

		if(vertexList[vertex]->state == INITIAL)
		{
			vertexList[vertex]->state = VISITED;
			vertexList[vertex]->componentNumber = cn;
		}

		//Looking for the adjacent vertices of the popped element, and from these push only those vertices into the stack
		//which are in the INITIAL state.
		for(int i=nVertices-1; i>=0; i--)
		{
			//Checking for adjacent vertices with INITIAL state
			if(isAdjacent(vertex,i) && vertexList[i]->state==INITIAL)
			{
				dfsStack.push(i);
			}
		}
	}//End of while

}//End of dfs()

void UndirectedGraph::connectedComponent()
{
	int componentNumber = 0;

	//Initially all the vertices will have INITIAL state
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->state = INITIAL;
	}

	componentNumber++;
	dfs(0,componentNumber);		//Start DFS from vertex 0

	for(int v=0; v<nVertices; v++)
	{
		if(vertexList[v]->state == INITIAL)
		{
			componentNumber++;
			dfs(v, componentNumber);
		}
	}

	cout << "Number of connected components = " << componentNumber << "\n";

	if(componentNumber == 1)
	{
		cout << "Graph is connected\n";
	}
	else
	{
		cout << "Graph is not connected\n";
		for(int v=0; v<nVertices; v++)
		{
			cout << vertexList[v]->name << " -> Component Number : " << vertexList[v]->componentNumber << "\n";
		}
	}

}//End of connectedComponent()

int main()
{
	UndirectedGraph uGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		//Connected Graph
		//uGraph.insertVertex("0");
		//uGraph.insertVertex("1");
		//uGraph.insertVertex("2");
		//uGraph.insertVertex("3");
		//uGraph.insertVertex("4");
		//uGraph.insertVertex("5");
		//uGraph.insertVertex("6");
		//uGraph.insertVertex("7");
		//uGraph.insertVertex("8");
		//uGraph.insertVertex("9");

		//uGraph.insertEdge("0","1");
		//uGraph.insertEdge("0","3");
		//uGraph.insertEdge("1","2");
		//uGraph.insertEdge("1","4");
		//uGraph.insertEdge("1","5");
		//uGraph.insertEdge("2","3");
		//uGraph.insertEdge("2","5");
		//uGraph.insertEdge("3","6");
		//uGraph.insertEdge("4","7");
		//uGraph.insertEdge("5","6");
		//uGraph.insertEdge("5","7");
		//uGraph.insertEdge("5","8");
		//uGraph.insertEdge("6","9");
		//uGraph.insertEdge("7","8");
		//uGraph.insertEdge("8","9");

		//Not Connected Graph
		uGraph.insertVertex("0");
		uGraph.insertVertex("1");
		uGraph.insertVertex("2");
		uGraph.insertVertex("3");
		uGraph.insertVertex("4");
		uGraph.insertVertex("5");
		uGraph.insertVertex("6");
		uGraph.insertVertex("7");
		uGraph.insertVertex("8");
		uGraph.insertVertex("9");
		uGraph.insertVertex("10");
		uGraph.insertVertex("11");
		uGraph.insertVertex("12");
		uGraph.insertVertex("13");
		uGraph.insertVertex("14");

		uGraph.insertEdge("0","1");
		uGraph.insertEdge("0","2");
		uGraph.insertEdge("0","3");
		uGraph.insertEdge("2","3");

		uGraph.insertEdge("4","5");
		uGraph.insertEdge("4","6");
		uGraph.insertEdge("4","7");
		uGraph.insertEdge("4","8");
		uGraph.insertEdge("5","7");
		uGraph.insertEdge("6","8");
		uGraph.insertEdge("6","9");

		uGraph.insertEdge("10","11");
		uGraph.insertEdge("10","12");
		uGraph.insertEdge("10","13");
		uGraph.insertEdge("11","12");
		uGraph.insertEdge("11","13");
		uGraph.insertEdge("11","14");
		uGraph.insertEdge("13","14");

		//Display the graph
		uGraph.display();
		cout << "\n";

		//Find the connected components of graph
		uGraph.connectedComponent();

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()
