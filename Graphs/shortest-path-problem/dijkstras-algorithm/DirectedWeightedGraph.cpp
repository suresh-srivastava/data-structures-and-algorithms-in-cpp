//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedWeightedGraph.cpp : Program to find shortest paths using Dijkstra's algorithm.

#include<iostream>
#include<string>
#include<stack>
using namespace std;

static const int maxSize = 30;

class Vertex
{
	public:
		string name;
		int status;
		int predecessor;
		int pathLength;

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
		int TEMPORARY;
		int PERMANENT;
		int INFINITY;
		int NIL;

	private:
		int getIndex(string vertexName);
		bool isAdjacent(int u, int v);
		void dijkstrasAlgorithm(int s);
		int getMinimumTemporary();
		void findPath(int s, int v);

	public:
		DirectedWeightedGraph();
		~DirectedWeightedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination, int weight);
		void display();
		void findPaths(string source);

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

	TEMPORARY = 0;
	PERMANENT = 1;
	INFINITY = 9999;
	NIL = -1;

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
	for(int i=0; i<nVertices; i++)
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
  
//Returns the temporary vertex with minimum value of pathLength,
//Returns NIL if no temporary vertex left or all temporary vertices left have pathLength INFINITY
int DirectedWeightedGraph::getMinimumTemporary()
{
	int min = INFINITY;
	int k = NIL;

	for(int i=0; i<nVertices; i++)
	{
		if(vertexList[i]->status==TEMPORARY && vertexList[i]->pathLength<min)
		{
			min = vertexList[i]->pathLength;
			k=i;
		}
	}

	return k;

}//End of getMinimumTemporary()

void DirectedWeightedGraph::dijkstrasAlgorithm(int s)
{
	//Make all vertices temporary
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->status = TEMPORARY;
		vertexList[i]->predecessor = NIL;
		vertexList[i]->pathLength = INFINITY;
	}

	//Make pathLength of source vertex equal to 0
	vertexList[s]->pathLength = 0;

	while(true)
	{
		//Search for temporary vertex with minimum pathLength and make it current vertex
		int current = getMinimumTemporary();

		if(current == NIL)
			break;

		//Make current vertex PERMANENT
		vertexList[current]->status = PERMANENT;

		for(int v=0; v<nVertices; v++)
		{
			//Checks for adjacent temporary vertices
			if(isAdjacent(current,v) && vertexList[v]->status==TEMPORARY)
			{
				if((vertexList[current]->pathLength + adj[current][v]) < vertexList[v]->pathLength)
				{
					vertexList[v]->predecessor = current;	//Relabel
					vertexList[v]->pathLength = vertexList[current]->pathLength + adj[current][v];
				}
			}
		}//End of for
	}//End of while

}//End of dijkstrasAlgorithm()

void DirectedWeightedGraph::findPath(int s, int v)
{
	int path[maxSize];		//stores the shortest path
	int shortestDistance=0;	//length of shortest path
	int count=0;			//number of vertices in the shortest path			
	int u;

	//Store the full path in the array path
	while(v!=s)
	{
		count++;
		path[count] = v;
		u = vertexList[v]->predecessor;
		shortestDistance += adj[u][v];
		v = u;
	}

	count++;
	path[count] = s;
	cout << "Shortest Path : ";
	for(int i=count; i>=1; i--)
		cout << path[i] << " ";
	cout << "\n";
	cout << "Shortest Distance : " << shortestDistance << "\n";

}//End of findPath()

void DirectedWeightedGraph::findPaths(string source)
{
	int s = getIndex(source);

	dijkstrasAlgorithm(s);

	cout << "Source : " << source << "\n";

	for(int v=0; v<nVertices; v++)
	{
		cout << "Destination : " << vertexList[v]->name << "\n";
		if(vertexList[v]->pathLength == INFINITY)
			cout << "There is no path from " << source << " to vertex " << vertexList[v]->name << "\n";
		else
			findPath(s, v);
	}

}//End of findPaths()

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
		dwGraph.insertVertex("4");
		dwGraph.insertVertex("5");
		dwGraph.insertVertex("6");
		dwGraph.insertVertex("7");

		dwGraph.insertEdge("0","1",8);
		dwGraph.insertEdge("0","2",2);
		dwGraph.insertEdge("0","3",7);
		dwGraph.insertEdge("1","5",16);
		dwGraph.insertEdge("2","0",5);
		dwGraph.insertEdge("2","3",4);
		dwGraph.insertEdge("2","6",3);
		dwGraph.insertEdge("3","4",9);
		dwGraph.insertEdge("4","0",4);
		dwGraph.insertEdge("4","5",5);
		dwGraph.insertEdge("4","7",8);
		dwGraph.insertEdge("6","2",6);
		dwGraph.insertEdge("6","3",3);
		dwGraph.insertEdge("6","4",4);
		dwGraph.insertEdge("7","5",2);
		dwGraph.insertEdge("7","6",5);

		//Display the graph
		dwGraph.display();
		cout << "\n";

		//Finding path from source vertex to other vertices
		dwGraph.findPaths("0");

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()
