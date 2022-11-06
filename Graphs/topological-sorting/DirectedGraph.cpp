//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedGraph.cpp : Program for topological sorting of directed acyclic graph.

#include<iostream>
#include<string>
#include<queue>
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
		int getIndegree(int vertex);

	public:
		DirectedGraph();
		~DirectedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void display();
		void topologicalOrder();

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
  
//Returns number of edges coming to a vertex
int DirectedGraph::getIndegree(int vertex)
{
    int indegree = 0;
    for(int v=0; v<nVertices; v++)
        if (adj[v][vertex])
            indegree++;

    return indegree;
}//End of getIndegree()

void DirectedGraph::topologicalOrder()
{
	int topoOrder[maxSize], indegree[maxSize];
	queue<int> q;
	int v, count;

	//Get the indegree of each vertex
	for(v=0; v<nVertices; v++)
	{
		indegree[v] = getIndegree(v);
		if(indegree[v] == 0)
			q.push(v);
	}

	count=0;
	while(!q.empty() && count<nVertices)
	{
		v = q.front();
		q.pop();

		topoOrder[++count] = v;	//Add vertex v to topoOrder array

		//Delete all the edges going from vertex v
		for(int i=0; i<nVertices; i++)
		{
			if(adj[v][i] == true)
			{
				adj[v][i] = false;
				indegree[i] = indegree[i]-1;
				if(indegree[i] == 0)
					q.push(i);
			}
		}

	}//End of while

	if(count < nVertices)
	{
		throw exception("Graph contains cycle. Topological order is not possible.");
	}

	cout << "Vertices in topological order are :\n";
	for(int i=1; i<=count; i++)
		cout << topoOrder[i] << " ";
	cout << "\n";

}//End of topologicalOrder()

int main()
{
	DirectedGraph dGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		//Graph without cycle
		dGraph.insertVertex("0");
		dGraph.insertVertex("1");
		dGraph.insertVertex("2");
		dGraph.insertVertex("3");
		dGraph.insertVertex("4");
		dGraph.insertVertex("5");
		dGraph.insertVertex("6");

		dGraph.insertEdge("0","1");
		dGraph.insertEdge("0","5");
		dGraph.insertEdge("1","4");
		dGraph.insertEdge("1","5");
		dGraph.insertEdge("2","1");
		dGraph.insertEdge("2","3");
		dGraph.insertEdge("3","1");
		dGraph.insertEdge("3","4");
		dGraph.insertEdge("4","5");
		dGraph.insertEdge("6","4");
		dGraph.insertEdge("6","5");

		//Graph with cycle
		//dGraph.insertVertex("0");
		//dGraph.insertVertex("1");
		//dGraph.insertVertex("2");
		//dGraph.insertVertex("3");
		//dGraph.insertVertex("4");

		//dGraph.insertEdge("0","1");
		//dGraph.insertEdge("0","2");
		//dGraph.insertEdge("1","3");
		//dGraph.insertEdge("2","4");
		//dGraph.insertEdge("3","0");
		//dGraph.insertEdge("3","4");

		//Display the graph
		dGraph.display();

		dGraph.topologicalOrder();

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()

