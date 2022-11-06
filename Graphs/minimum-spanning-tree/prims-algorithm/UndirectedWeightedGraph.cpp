//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//UndirectedWeightedGraph.cpp : Program to create minimum spanning tree using prim's algorithm.

#include<iostream>
#include<string>
using namespace std;

static const int maxSize = 30;

class Vertex
{
	public:
		string name;
		int status;
		int predecessor;
		int length;

	public:
		Vertex(string name)
		{
			this->name = name;
		}
};//End of class Vertex

class Edge
{
	public:
		int u;
		int v;
};//End of class Edge

class UndirectedWeightedGraph
{
	private:
		int nVertices;
		int nEdges;
		int adj[maxSize][maxSize];
		Vertex *vertexList[maxSize];
		Edge treeEdges[maxSize];
		int TEMPORARY;
		int PERMANENT;
		int INFINITY;
		int NIL;

	private:
		int getIndex(string vertexName);
		bool isAdjacent(int u, int v);
		void primsAlgorithm(int s);
		int getMinimumTemporary();

	public:
		UndirectedWeightedGraph();
		~UndirectedWeightedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination, int weight);
		void display();
		void minimumSpanningTree(string source);

};//End of class UndirectedWeightedGraph

UndirectedWeightedGraph::UndirectedWeightedGraph()
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

}//End of UndirectedWeightedGraph()

UndirectedWeightedGraph::~UndirectedWeightedGraph()
{
	for(int i=0; i<nVertices; i++)
	{
		delete vertexList[i];
	}
}//End of ~UndirectedWeightedGraph()

void UndirectedWeightedGraph::insertVertex(string vertexName)
{
	vertexList[nVertices++] = new Vertex(vertexName);
}//End of insertVertex()

int UndirectedWeightedGraph::getIndex(string vertexName)
{
	for(int i=0; i<nVertices; i++)
	{
        if(vertexName == vertexList[i]->name)
            return i;
	}

	throw exception("Invalid Vertex");

}//End of getIndex()

void UndirectedWeightedGraph::insertEdge(string source, string destination, int weight)
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
		adj[v][u] = weight;
		nEdges++;
	}
}//End of insertEdge()

void UndirectedWeightedGraph::display()
{
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
			cout << adj[i][j] << " ";
        cout <<"\n";
    }
}//End of display()

bool UndirectedWeightedGraph::isAdjacent(int u, int v)
{
	return (adj[u][v] != 0);
}//End of isAdjacent()

//Returns the temporary vertex with minimum value of length,
//Returns NIL if no temporary vertex left or all temporary vertices left have length INFINITY
int UndirectedWeightedGraph::getMinimumTemporary()
{
	int min = INFINITY;
	int k = NIL;

	for(int i=0; i<nVertices; i++)
	{
		if(vertexList[i]->status==TEMPORARY && vertexList[i]->length<min)
		{
			min = vertexList[i]->length;
			k=i;
		}
	}

	return k;

}//End of getMinimumTemporary()

void UndirectedWeightedGraph::primsAlgorithm(int r)
{
	int count = 0;	//Number of edges in the tree

	//Make all vertices temporary
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->status = TEMPORARY;
		vertexList[i]->predecessor = NIL;
		vertexList[i]->length = INFINITY;
	}

	//Make pathLength of source vertex equal to 0
	vertexList[r]->length = 0;

	while(true)
	{
		//Search for temporary vertex with minimum pathLength and make it current vertex
		int current = getMinimumTemporary();

		if(current == NIL)
		{
			if(count == nVertices-1)
			{
				break;	//No temporary vertex left
			}
			else		//Temporary vertices left with length INFINITY
			{
				throw exception("Graph is not connected, spanning tree is not possible.");
			}
		}

		//Make current vertex PERMANENT
		vertexList[current]->status = PERMANENT;

		//Insert the edge (vertexList[current]->predecessor,current) into the tree,
		//except when the current vertex is root
		if(current != r)
		{
			count++;
			treeEdges[count].u = vertexList[current]->predecessor;
			treeEdges[count].v = current;
		}

		for(int v=0; v<nVertices; v++)
		{
			//Checks for adjacent temporary vertices
			if(isAdjacent(current,v) && vertexList[v]->status==TEMPORARY)
			{
				if((adj[current][v]) < vertexList[v]->length)
				{
					vertexList[v]->predecessor = current;	//Relabel
					vertexList[v]->length = adj[current][v];
				}
			}
		}//End of for
	}//End of while

}//End of primsAlgorithm()

void UndirectedWeightedGraph::minimumSpanningTree(string root)
{
	int r = getIndex(root);
	int treeWeight=0;

	primsAlgorithm(r);

	cout << "Root vertex : " << root << "\n";

	cout << "Minimum Spanning Tree Edges :\n";
	for(int i=1; i<=nVertices-1; i++)
	{
		cout << "Edge - (" << treeEdges[i].u << "-" << treeEdges[i].v << ")\n";
		treeWeight += adj[treeEdges[i].u][treeEdges[i].v];
	}

	cout << "Minimum Spanning Tree Weight : " << treeWeight << "\n";

}//End of minimumSpanningTree()

int main()
{
	UndirectedWeightedGraph uwGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		//Connected graph
		uwGraph.insertVertex("0");
		uwGraph.insertVertex("1");
		uwGraph.insertVertex("2");
		uwGraph.insertVertex("3");
		uwGraph.insertVertex("4");
		uwGraph.insertVertex("5");

		uwGraph.insertEdge("0","1",6);
		uwGraph.insertEdge("0","2",2);
		uwGraph.insertEdge("0","3",3);
		uwGraph.insertEdge("0","4",10);
		uwGraph.insertEdge("1","3",11);
		uwGraph.insertEdge("1","5",9);
		uwGraph.insertEdge("2","3",14);
		uwGraph.insertEdge("2","4",8);
		uwGraph.insertEdge("3","4",7);
		uwGraph.insertEdge("3","5",5);
		uwGraph.insertEdge("4","5",4);

		//Not connected graph
		//uwGraph.insertVertex("0");
		//uwGraph.insertVertex("1");
		//uwGraph.insertVertex("2");
		//uwGraph.insertVertex("3");
		//uwGraph.insertVertex("4");
		//uwGraph.insertVertex("5");
		//uwGraph.insertVertex("6");
		//uwGraph.insertVertex("7");

		//uwGraph.insertEdge("0","1",6);
		//uwGraph.insertEdge("0","2",3);
		//uwGraph.insertEdge("0","3",8);
		//uwGraph.insertEdge("1","4",9);
		//uwGraph.insertEdge("2","3",7);
		//uwGraph.insertEdge("2","4",5);
		//uwGraph.insertEdge("3","4",4);

		//uwGraph.insertEdge("5","6",2);
		//uwGraph.insertEdge("5","7",8);
		//uwGraph.insertEdge("6","7",5);

		//Display the graph
		uwGraph.display();
		cout << "\n";

		uwGraph.minimumSpanningTree("0");

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()
