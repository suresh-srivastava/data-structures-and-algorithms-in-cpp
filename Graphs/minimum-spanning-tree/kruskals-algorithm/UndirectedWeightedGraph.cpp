//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//UndirectedWeightedGraph.cpp : Program to create minimum spanning tree using Kruskal's algorithm.

#include<iostream>
#include<string>
#include<queue>
using namespace std;

static const int maxSize = 30;

class Vertex
{
	public:
		string name;
		int father;

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
		int wt;

	public:
		Edge(int u, int v, int wt);
};//End of class Edge

Edge::Edge(int u, int v, int wt)
{
	this->u = u;
	this->v = v;
	this->wt = wt;
};//End of Edge()

class UndirectedWeightedGraph
{
	private:
		int nVertices;
		int nEdges;
		int adj[maxSize][maxSize];
		Vertex *vertexList[maxSize];
		Edge *treeEdges[maxSize];
		int NIL;

	private:
		int getIndex(string vertexName);
		bool isAdjacent(int u, int v);
		void kruskalsAlgorithm();

	public:
		UndirectedWeightedGraph();
		~UndirectedWeightedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination, int weight);
		void display();
		void minimumSpanningTree();

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

	NIL = -1;

}//End of UndirectedWeightedGraph()

UndirectedWeightedGraph::~UndirectedWeightedGraph()
{
	for(int i=0; i<nVertices; i++)
	{
		delete vertexList[i];
	}

	for(int i=1; treeEdges[i]!=NULL; i++)
	{
		delete treeEdges[i];
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

class ComparaeWeight
{
	public:
		bool operator()(Edge *a, Edge *b)
		{
			return a->wt > b->wt;
		}
};

void UndirectedWeightedGraph::kruskalsAlgorithm()
{
	int count = 0;	//Number of edges in the tree

	priority_queue<Edge*, vector<Edge*>, ComparaeWeight> edgeQueue;

	//Inserting all the edges in priority queue
	for(int u=0; u<nVertices; u++)
	{
		for(int v=u; v<nVertices; v++)
		{
			if(isAdjacent(u,v))
			{
				edgeQueue.push(new Edge(u,v,adj[u][v]));
			}
		}
	}

	//Initialize the father of vertices to NIL
	for(int i=0; i<nVertices; i++)
	{
		vertexList[i]->father = NIL;
	}

	int v1, v2, v1Root=NIL, v2Root=NIL;
	Edge *edge;

	while(!edgeQueue.empty() && count < nVertices-1)
	{
		edge = edgeQueue.top();
		edgeQueue.pop();

		v1 = edge->u;
		v2 = edge->v;

		while(v1!=NIL)
		{
			v1Root = v1;
			v1 = vertexList[v1]->father;
		}

		while(v2!=NIL)
		{
			v2Root = v2;
			v2 = vertexList[v2]->father;
		}

		if(v1Root != v2Root)	//Include the edge in tree
		{
			count++;
			treeEdges[count] = new Edge(edge->u, edge->v, edge->wt);
			vertexList[v2Root]->father = v1Root;
		}

	}//End of while

	treeEdges[count+1]=NULL;

	if(count < nVertices-1)
	{
		throw exception("Graph is not connected, spanning tree is not possible.");
	}

}//End of kruskalsAlgorithm()

void UndirectedWeightedGraph::minimumSpanningTree()
{
	int treeWeight=0;

	kruskalsAlgorithm();

	cout << "Minimum Spanning Tree Edges :\n";
	for(int i=1; i<=nVertices-1; i++)
	{
		cout << "Edge - (" << treeEdges[i]->u << "-" << treeEdges[i]->v << ")\n";
		treeWeight += adj[treeEdges[i]->u][treeEdges[i]->v];
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
		uwGraph.insertVertex("6");
		uwGraph.insertVertex("7");
		uwGraph.insertVertex("8");

		uwGraph.insertEdge("0","1",9);
		uwGraph.insertEdge("0","3",4);
		uwGraph.insertEdge("0","4",2);
		uwGraph.insertEdge("1","2",10);
		uwGraph.insertEdge("1","4",8);
		uwGraph.insertEdge("2","4",7);
		uwGraph.insertEdge("2","5",5);
		uwGraph.insertEdge("3","4",3);
		uwGraph.insertEdge("3","6",18);
		uwGraph.insertEdge("4","5",6);
		uwGraph.insertEdge("4","6",11);
		uwGraph.insertEdge("4","7",12);
		uwGraph.insertEdge("4","8",15);
		uwGraph.insertEdge("5","8",16);
		uwGraph.insertEdge("6","7",14);
		uwGraph.insertEdge("7","8",20);

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

		uwGraph.minimumSpanningTree();

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()
