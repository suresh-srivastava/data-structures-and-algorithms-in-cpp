//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedGraph.cpp : Program for traversing a directed graph through BFS.
//Visiting only those vertices that are reachable from start vertex.
//Visiting all vertices

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

class DirectedGraph
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
		DirectedGraph();
		~DirectedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void display();
		void bfsTraversal(string vertexName);
		void bfsTraversalAll(string vertexName);

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

	INITIAL = 0;
	WAITING = 1;
	VISITED = 2;

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
 
void DirectedGraph::bfs(int vertex)
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

void DirectedGraph::bfsTraversal(string vertexName)
{
	//Initially all the vertices will have INITIAL state
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->state = INITIAL;
	}

	bfs(getIndex(vertexName));
}//End of bfsTraversal()

void DirectedGraph::bfsTraversalAll(string vertexName)
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

		dGraph.insertEdge("0","1");
		dGraph.insertEdge("0","3");
		dGraph.insertEdge("0","4");
		dGraph.insertEdge("1","2");
		dGraph.insertEdge("2","5");
		dGraph.insertEdge("3","4");
		dGraph.insertEdge("3","6");
		dGraph.insertEdge("4","5");
		dGraph.insertEdge("4","7");
		dGraph.insertEdge("6","4");
		dGraph.insertEdge("6","7");
		dGraph.insertEdge("7","5");
		dGraph.insertEdge("7","8");

		//Display the graph
		dGraph.display();
		cout << "\n";

		//BFS traversal visiting only those vertices that are reachable from start vertex
		dGraph.bfsTraversal("4");

		//BFS traversal visiting all the vertices
		dGraph.bfsTraversalAll("0");

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()

