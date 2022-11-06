//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedWeightedGraph.cpp : Program to find shortest path matrix by Modified Warshall's (Floyd) algorithm.

#include<iostream>
#include<string>
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

class DirectedWeightedGraph
{
	private:
		int nVertices;
		int nEdges;
		int adj[maxSize][maxSize];
		Vertex *vertexList[maxSize];
		int D[maxSize][maxSize]; //Shortest Path Matrix
		int Pred[maxSize][maxSize]; //Predecessor Matrix
		int INFINITY;

	private:
		int getIndex(string vertexName);
		bool isAdjacent(int u, int v);
		void display(int mat[maxSize][maxSize]);
		void floydWarshallsAlgorithm(int s);
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

	INFINITY = 9999;

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

void DirectedWeightedGraph::display(int mat[maxSize][maxSize])
{
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
			cout << mat[i][j] << " ";
        cout <<"\n";
    }
}//End of display()

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
 
void DirectedWeightedGraph::floydWarshallsAlgorithm(int s)
{
	//Getting D(-1), Pred(-1)
	for(int i=0; i<nVertices; i++)
	{
		for(int j=0; j<nVertices; j++)
		{
			if(adj[i][j] == 0)
			{
				D[i][j] = INFINITY;
				Pred[i][j] = -1;
			}
			else
			{
				D[i][j] = adj[i][j];
				Pred[i][j] = i;
			}
		}
	}//End of for

	//Getting D(k), Pred(k)
	for(int k=0; k<nVertices; k++)
	{
		for(int i=0; i<nVertices; i++)
		{
			for(int j=0; j<nVertices; j++)
			{
				if(D[i][k]+D[k][j] < D[i][j])
				{
					D[i][j] = D[i][k]+D[k][j];
					Pred[i][j] = Pred[k][j];
				}
			}
		}
	}//End of for

	//Finding negative cycle
	for(int i=0; i<nVertices; i++)
	{
		if(D[i][i] < 0)
		{
			throw exception("There is negative cycle in graph.");
		}
	}

	cout << "Shortest Path Matrix :\n";
	display(D);
	cout << "\nPredecessor Matrix :\n";
	display(Pred);

}//End of floydWarshallsAlgorithm()

void DirectedWeightedGraph::findPath(int s, int v)
{
	int path[maxSize];		//stores the shortest path
	int count=-1;			//number of vertices in the shortest path			

	if(D[s][v] == INFINITY)
	{
		cout << "No path\n";
	}
	else
	{
		do
		{
			path[++count] = v;
			v = Pred[s][v];
		}while(v!=s);

		path[++count] = s;
		cout << "Shortest Path : ";
		for(int i=count; i>=0; i--)
			cout << path[i] << " ";
		cout << "\n";
	}

}//End of findPath()

void DirectedWeightedGraph::findPaths(string source)
{
	int s = getIndex(source);

	floydWarshallsAlgorithm(s);

	cout << "Source : " << source << "\n";

	for(int v=0; v<nVertices; v++)
	{
		cout << "Destination : " << vertexList[v]->name << "\n";
		findPath(s, v);
		cout << "Shortest Distance : " << D[s][v] << "\n";
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

		dwGraph.insertEdge("0","1",2);
		dwGraph.insertEdge("0","3",9);
		dwGraph.insertEdge("1","0",3);
		dwGraph.insertEdge("1","2",4);
		dwGraph.insertEdge("1","3",7);
		dwGraph.insertEdge("2","1",6);
		dwGraph.insertEdge("2","3",2);
		dwGraph.insertEdge("3","0",14);
		dwGraph.insertEdge("3","2",4);

		//Graph with negative cycle
		//dwGraph.insertVertex("0");
		//dwGraph.insertVertex("1");
		//dwGraph.insertVertex("2");
		//dwGraph.insertVertex("3");
		//dwGraph.insertVertex("4");

		//dwGraph.insertEdge("0","1",2);
		//dwGraph.insertEdge("0","2",7);
		//dwGraph.insertEdge("1","3",-9);
		//dwGraph.insertEdge("2","4",6);
		//dwGraph.insertEdge("3","0",4);
		//dwGraph.insertEdge("3","4",5);

		//Display the graph
		dwGraph.display();
		cout << "\n";

		dwGraph.findPaths("0");

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()
