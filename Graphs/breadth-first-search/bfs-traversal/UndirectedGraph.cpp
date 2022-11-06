//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//UndirectedGraph.cpp : Program for traversing an undirected graph through BFS.
//Visiting only those vertices that are reachable from start vertex.
//Visiting all vertices.
//Finding graph is connected or not connected.

#include<iostream>
#include<string>
#include<queue>
using namespace std;

static const int maxSize = 30;

class Vertex
{
	public:
		string name;
		int state;

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
		int WAITING;
		int VISITED;

	private:
		int getIndex(string vertexName);
		bool isAdjacent(int u, int v);
		void bfs(int vertex);

	public:
		UndirectedGraph();
		~UndirectedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void display();
		void bfsTraversal(string vertexName);
		void bfsTraversalAll(string vertexName);
		bool isConnected();

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
	WAITING = 1;
	VISITED = 2;

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

void UndirectedGraph::bfs(int vertex)
{
	queue<int> bfsQueue;

	//Inserting the start vertex into queue and changing its state to WAITING
	bfsQueue.push(vertex);
	vertexList[vertex]->state = WAITING;

	while(!bfsQueue.empty())
	{
		//Deleting front element from the queue and changing its state to VISITED
		vertex = bfsQueue.front();
		bfsQueue.pop();
		vertexList[vertex]->state = VISITED;

		cout << vertex << " ";

		//Looking for the adjacent vertices of the deleted element, and from these insert only those vertices into the
		//queue which are in the INITIAL state. Change the state of all these inserted vertices from INITIAL to WAITING
		for(int i=0; i<nVertices; i++)
		{
			//Checking for adjacent vertices with INITIAL state
			if(isAdjacent(vertex,i) && vertexList[i]->state==INITIAL)
			{
				bfsQueue.push(i);
				vertexList[i]->state = WAITING;
			}
		}
	}//End of while

	cout << "\n";

}//End of bfs()

void UndirectedGraph::bfsTraversal(string vertexName)
{
	//Initially all the vertices will have INITIAL state
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->state = INITIAL;
	}

	bfs(getIndex(vertexName));
}//End of bfsTraversal()

void UndirectedGraph::bfsTraversalAll(string vertexName)
{
	//Initially all the vertices will have INITIAL state
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->state = INITIAL;
	}

	bfs(getIndex(vertexName));

	for(int v=0; v<nVertices; v++)
	{
		if(vertexList[v]->state == INITIAL)
			bfs(v);
	}

}//End of bfsTraversalAll()

bool UndirectedGraph::isConnected()
{
	bool connected = true;

	//Initially all the vertices will have INITIAL state
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->state = INITIAL;
	}

	bfs(0);	//Start traversal from vertex 0

	for(int v=0; v<nVertices; v++)
	{
		if(vertexList[v]->state == INITIAL)
		{
			connected = false;
			break;
		}
	}

	return connected;

}//End of isConnected()

int main()
{
	UndirectedGraph uGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		//Connected Graph
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

		uGraph.insertEdge("0","1");
		uGraph.insertEdge("0","3");
		uGraph.insertEdge("1","2");
		uGraph.insertEdge("1","4");
		uGraph.insertEdge("1","5");
		uGraph.insertEdge("2","3");
		uGraph.insertEdge("2","5");
		uGraph.insertEdge("3","6");
		uGraph.insertEdge("4","7");
		uGraph.insertEdge("5","6");
		uGraph.insertEdge("5","7");
		uGraph.insertEdge("5","8");
		uGraph.insertEdge("6","9");
		uGraph.insertEdge("7","8");
		uGraph.insertEdge("8","9");

		//Not Connected Graph
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
		//uGraph.insertVertex("10");
		//uGraph.insertVertex("11");
		//uGraph.insertVertex("12");
		//uGraph.insertVertex("13");
		//uGraph.insertVertex("14");

		//uGraph.insertEdge("0","1");
		//uGraph.insertEdge("0","3");
		//uGraph.insertEdge("1","2");

		//uGraph.insertEdge("4","5");
		//uGraph.insertEdge("4","7");
		//uGraph.insertEdge("4","8");
		//uGraph.insertEdge("5","6");
		//uGraph.insertEdge("5","8");
		//uGraph.insertEdge("6","9");
		//uGraph.insertEdge("7","8");
		//uGraph.insertEdge("8","9");

		//uGraph.insertEdge("10","11");
		//uGraph.insertEdge("10","13");
		//uGraph.insertEdge("10","14");
		//uGraph.insertEdge("11","12");
		//uGraph.insertEdge("12","13");
		//uGraph.insertEdge("13","14");

		//Display the graph
		uGraph.display();
		cout << "\n";

		//BFS traversal visiting only those vertices that are reachable from start vertex
		uGraph.bfsTraversal("4");

		//BFS traversal visiting all the vertices
		uGraph.bfsTraversalAll("0");

		//Find out that graph is conncted or not connected
		if(uGraph.isConnected())
			cout << "Graph is connected\n";
		else
			cout << "Graph is not connected\n";

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()

