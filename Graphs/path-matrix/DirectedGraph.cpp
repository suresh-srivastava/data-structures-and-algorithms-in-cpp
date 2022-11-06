//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedGraph.cpp : Program to find out the path matrix by powers of adjacency matrix.

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

class DirectedGraph
{
	private:
		int nVertices;
		int nEdges;
		int adj[maxSize][maxSize];
		Vertex *vertexList[maxSize];

	private:
		int getIndex(string vertexName);

	public:
		DirectedGraph();
		~DirectedGraph();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void display();
		void pathMatrix();

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

void DirectedGraph::pathMatrix()
{
	int adjp[maxSize][maxSize], x[maxSize][maxSize], temp[maxSize][maxSize];
	int path[maxSize][maxSize];

	//Initialize x
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
		{
			x[i][j] = 0;
		}
    }

	//Initially adjp and x is equal to adj
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
		{
			x[i][j] = adjp[i][j] = adj[i][j];
		}
    }

	//Get the matrix x by adding all the adjp
	for(int p=2; p<=nVertices; p++)
	{
		//adjp(1...n) x adj
		for(int i=0; i<nVertices; i++)
		{
			for(int j=0; j<nVertices; j++)
			{
				temp[i][j]=0;
				for(int k=0; k<nVertices; k++)
				{
					temp[i][j] = temp[i][j] + adjp[i][k]*adj[k][j];
				}
			}
		}

		//Now adjp will be equal to temp
		for(int i=0; i<nVertices; i++)
		{
     		for(int j=0; j<nVertices; j++)
			{
				adjp[i][j] = temp[i][j];
			}
		}

		//x = adjp1 + adjp2 + ...... + adjpn
		for(int i=0; i<nVertices; i++)
		{
     		for(int j=0; j<nVertices; j++)
			{
				x[i][j] = x[i][j] + adjp[i][j];
			}
		}
	}//End of for

	//Display x
	cout << "x matrix is :\n";
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
		{
			cout << x[i][j] << " ";
		}
        cout <<"\n";
    }

	//Assign values to path matrix
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
		{
			if(x[i][j] == 0)
				path[i][j] = 0;
			else
				path[i][j] = 1;
		}
    }

	//Display path matrix
	cout << "Path matrix is :\n";
    for(int i=0; i<nVertices; i++)
    {
     	for(int j=0; j<nVertices; j++)
            cout << path[i][j] << " ";
        cout <<"\n";
    }

}//End of pathMatrix()

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

		dGraph.insertEdge("0","1");
		dGraph.insertEdge("0","3");
		dGraph.insertEdge("1","0");
		dGraph.insertEdge("1","2");
		dGraph.insertEdge("1","3");
		dGraph.insertEdge("2","3");
		dGraph.insertEdge("3","0");
		dGraph.insertEdge("3","2");

		//Display the graph
		dGraph.display();
		cout << "\n";

		cout << "Find the path matrix :\n";
		dGraph.pathMatrix();
	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()

