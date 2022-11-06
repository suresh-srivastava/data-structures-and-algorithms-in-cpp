//Copyright (C) Suresh Kumar Srivastava - All Rights Reserved
//DSA Masterclass courses are available on CourseGalaxy.com

//DirectedGraphList.cpp : Program for directed graph using adjacency list.

#include<iostream>
#include<string>
using namespace std;

class VertexNode;
class EdgeNode;

class VertexNode
{
	public:
		string name;
		VertexNode *nextVertex;
		EdgeNode *firstEdge;

	public:
		VertexNode(string name)
		{
			this->name = name;
			nextVertex = NULL;
			firstEdge = NULL;
		}
};//End of class Vertex

class EdgeNode
{
	public:
		VertexNode *endVertex;
		EdgeNode *nextEdge;

	public:
		EdgeNode(VertexNode *v)
		{
			this->endVertex = v;
			nextEdge = NULL;
		}
};//End of class Edge

class DirectedGraphList
{
	private:
		int nVertices;
		int nEdges;

	public:
		VertexNode *start;

	private:
		VertexNode* findVertex(string vertexName);
		void deleteFromEdgeLists(string vertexName);
		void deleteFromVertexList(string vertexName);

	public:
		DirectedGraphList();
		~DirectedGraphList();
		void insertVertex(string vertexName);
		void insertEdge(string source, string destination);
		void deleteVertex(string vertexName);
		void deleteEdge(string source, string destination);
		void display();
		bool edgeExists(string source, string destination);
		int getOutdegree(string vertex);
		int getIndegree(string vertex);

};//End of class DirectedGraphList

DirectedGraphList::DirectedGraphList()
{
	nVertices = 0;
	nEdges = 0;
	start = NULL;
}//End of DirectedGraphList()

DirectedGraphList::~DirectedGraphList()
{
	VertexNode *vertexPtr, *tempVertex;
	EdgeNode *edgePtr, *tempEdge;

	vertexPtr = start;
	while(vertexPtr != NULL)
	{
		edgePtr = vertexPtr->firstEdge;
		while(edgePtr != NULL)
		{
			tempEdge = edgePtr;
			edgePtr = edgePtr->nextEdge;
			delete tempEdge;
		}

		tempVertex = vertexPtr;
		vertexPtr = vertexPtr->nextVertex;
		delete tempVertex;
	}
}//End of ~DirectedGraphList()

void DirectedGraphList::insertVertex(string vertexName)
{
	VertexNode *ptr, *temp;
	bool vertexFound = false;

	ptr = start;

	if(ptr == NULL)
	{
		temp = new VertexNode(vertexName);
		start = temp;
		nVertices++;
	}
	else
	{
		while(ptr->nextVertex != NULL)
		{
			if(ptr->name == vertexName)
			{
				vertexFound = true;
				break;
			}
			ptr = ptr->nextVertex;
		}//End of while

		if(vertexFound || ptr->name == vertexName)
		{
			cout << "Vertex already present\n";
		}
		else
		{
			temp = new VertexNode(vertexName);
			ptr->nextVertex = temp;
			nVertices++;
		}
	}//End of else

}//End of insertVertex()

VertexNode* DirectedGraphList::findVertex(string vertexName)
{
    VertexNode *ptr = start;

    while(ptr != NULL)
    {
		if(ptr->name == vertexName)
            break;

		ptr = ptr->nextVertex;
    }

    return ptr;
}//End of findVertex()

void DirectedGraphList::insertEdge(string source, string destination)
{
	VertexNode *u, *v;
	EdgeNode *edgePtr, *temp;

	bool edgeFound = false;

	if(source == destination)
	{
		cout << "Inavlid Edge : source and destination vertices are same\n";
	}
	else
	{
		u = findVertex(source);
		v = findVertex(destination);

		if(u == NULL)
		{
			cout << "Source vertex not present, first insert vertex " << source << "\n";
		}
		else if(v == NULL)
		{
			cout << "Destination vertex not present, first insert vertex " << destination << "\n";
		}
		else
		{
			if(u->firstEdge == NULL)
			{
				temp = new EdgeNode(v);
				u->firstEdge = temp;
				nEdges++;
			}
			else
			{
				edgePtr = u->firstEdge;

				while(edgePtr->nextEdge != NULL)
				{
					if(edgePtr->endVertex->name == v->name)
					{
						edgeFound = true;
						break;
					}

					edgePtr = edgePtr->nextEdge;
				}//End of while

				if(edgeFound || edgePtr->endVertex->name == destination)
				{
					cout << "Edge already present\n";
				}
				else
				{
					temp = new EdgeNode(v);
					edgePtr->nextEdge = temp;
					nEdges++;
				}
			}//End of else
		}//End of else
	}//End of else

}//End of insertEdge()

void DirectedGraphList::deleteVertex(string vertexName)
{
	deleteFromEdgeLists(vertexName);
	deleteFromVertexList(vertexName);
}//End of deleteVertex()

//Delete incoming edges
void DirectedGraphList::deleteFromEdgeLists(string vertexName)
{
	VertexNode *vertexPtr;
	EdgeNode *edgePtr, *temp;

	vertexPtr = start;

	while(vertexPtr != NULL)
	{
		if(vertexPtr->firstEdge != NULL)
		{
			if(vertexPtr->firstEdge->endVertex->name == vertexName)
			{
				temp = vertexPtr->firstEdge;
				vertexPtr->firstEdge = vertexPtr->firstEdge->nextEdge;
				delete temp;
				nEdges--;
				continue;
			}

			edgePtr = vertexPtr->firstEdge;
			while(edgePtr->nextEdge != NULL)
			{
				if(edgePtr->nextEdge->endVertex->name == vertexName)
				{
					temp = edgePtr->nextEdge;
					edgePtr->nextEdge = edgePtr->nextEdge->nextEdge;
					delete temp;
					nEdges--;
					continue;
				}
				edgePtr = edgePtr->nextEdge;
			}
		}//End of if

		vertexPtr = vertexPtr->nextVertex;
	}//End of while
}//End of deleteFromEdgeLists()

//Delete outgoing edges and vertex
void DirectedGraphList::deleteFromVertexList(string vertexName)
{
	VertexNode *vertexPtr, *tempVertex=NULL;
	EdgeNode *edgePtr, *tempEdge;

	if(start == NULL)
	{
		cout << "No vertices to be deleted\n";
		return;
	}

	if(start->name == vertexName)
	{
		tempVertex = start;
		start = start->nextVertex;
	}
	else	//vertex to be deleted is in between or at last
	{
		vertexPtr = start;
		while(vertexPtr->nextVertex != NULL)
		{
			if(vertexPtr->nextVertex->name == vertexName)
				break;
			vertexPtr = vertexPtr->nextVertex;
		}

		if(vertexPtr->nextVertex != NULL)
		{
			tempVertex = vertexPtr->nextVertex;
			vertexPtr->nextVertex = vertexPtr->nextVertex->nextVertex;
		}
		else
		{
			cout << "Vertex not found\n";
		}
	}//End of else

	if(tempVertex)
	{
		//Before deleting the tempVertex, delete all the edges going from this vertex
		edgePtr = tempVertex->firstEdge;
		while(edgePtr != NULL)
		{
			tempEdge = edgePtr;
			edgePtr = edgePtr->nextEdge;
			delete tempEdge;
			nEdges--;
		}

		delete tempVertex;
		nVertices--;
	}

}//End of deleteFromVertexList()

void DirectedGraphList::deleteEdge(string source, string destination)
{
	VertexNode *vertexPtr;
	EdgeNode *edgePtr, *temp;

	vertexPtr = findVertex(source);

	if(vertexPtr==NULL)
	{
		cout << "Edge not found\n";
	}
	else
	{
		edgePtr = vertexPtr->firstEdge;

		if(edgePtr==NULL)
		{
			cout << "Edge not found\n";
		}
		else
		{
			if(edgePtr->endVertex->name == destination)
			{
				vertexPtr->firstEdge = edgePtr->nextEdge;
				delete edgePtr;
				nEdges--;
			}
			else
			{
				while(edgePtr->nextEdge != NULL)
				{
					if(edgePtr->nextEdge->endVertex->name == destination)
					{
						break;
					}
					edgePtr = edgePtr->nextEdge;
				}

				if(edgePtr->nextEdge==NULL)
				{
					cout << "Edge not found\n";
				}
				else
				{
					temp = edgePtr->nextEdge;
					edgePtr->nextEdge = edgePtr->nextEdge->nextEdge;
					delete temp;
					nEdges--;
				}
			}//End of else
		}//End of else
	}//End of else

}//End of deleteEdge()

void DirectedGraphList::display()
{
	VertexNode *vertexPtr;
	EdgeNode *edgePtr;

	vertexPtr = start;

	while(vertexPtr != NULL)
	{
		cout << "Vertex : " << vertexPtr->name << "\n";

		edgePtr = vertexPtr->firstEdge;
		while(edgePtr != NULL)
		{
			cout << "Edge : " << vertexPtr->name << " -> " << edgePtr->endVertex->name << "\n";
			edgePtr = edgePtr->nextEdge;
		}

		vertexPtr = vertexPtr->nextVertex;
	}
}//End of display()

bool DirectedGraphList::edgeExists(string source, string destination)
{
	VertexNode *vertexPtr;
	EdgeNode *edgePtr;
	bool edgeFound = false;

	vertexPtr = findVertex(source);

	if(vertexPtr)
	{
		edgePtr = vertexPtr->firstEdge;
		while(edgePtr != NULL)
		{
			if(edgePtr->endVertex->name == destination)
			{
				edgeFound = true;
				break;
			}
			edgePtr = edgePtr->nextEdge;
		}
	}

	return edgeFound;
}//End of edgeExists()

int DirectedGraphList::getOutdegree(string vertex)
{
	VertexNode *vertexPtr;
	EdgeNode *edgePtr;
	int outdegree = 0;

	vertexPtr = findVertex(vertex);
	if(vertexPtr == NULL)
		throw exception("Invalid Vertex");

	edgePtr = vertexPtr->firstEdge;
	while(edgePtr != NULL)
	{
		outdegree++;
		edgePtr = edgePtr->nextEdge;
	}

	return outdegree;
}//End of getOutdegree()

int DirectedGraphList::getIndegree(string vertex)
{
	VertexNode *vertexPtr;
	EdgeNode *edgePtr;
	int indegree = 0;

	if(findVertex(vertex) == NULL)
		throw exception("Invalid Vertex");

	vertexPtr = start;
	while(vertexPtr != NULL)
	{
		edgePtr = vertexPtr->firstEdge;
		while(edgePtr != NULL)
		{
			if(edgePtr->endVertex->name == vertex)
			{
				indegree++;
			}
			edgePtr = edgePtr->nextEdge;
		}
		vertexPtr = vertexPtr->nextVertex;
	}

	return indegree;
}//End of getIndegree()

int main()
{
	DirectedGraphList dGraph;

	try
	{
		//Creating the graph, inserting the vertices and edges
		dGraph.insertVertex("0");
		dGraph.insertVertex("1");
		dGraph.insertVertex("2");
		dGraph.insertVertex("3");

		dGraph.insertEdge("0","3");
		dGraph.insertEdge("1","2");
		dGraph.insertEdge("2","3");
		dGraph.insertEdge("3","1");
		dGraph.insertEdge("0","2");

		//Display the graph
		dGraph.display();
		cout << "\n";

		//Deleting an edge
		dGraph.deleteEdge("0","2");

		//Display the graph
		dGraph.display();
		cout << "\n";

		//Deleting a vertex
		dGraph.deleteVertex("0");

		//Display the graph
		dGraph.display();

		//Check if there is an edge between two vertices
		cout << "Edge exist : " << (dGraph.edgeExists("2","3") ? "True" : "False") << "\n";

		//Display Indegree and Outdegree of a vertex
		cout << "Outdegree : " << dGraph.getOutdegree("3") << "\n";
		cout << "Indegree : " << dGraph.getIndegree("3") << "\n";

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;

}//End of main()

