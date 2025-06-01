//LinkedList5.cpp : Program to find an element in a single linked list.

#include <iostream>
using namespace std;

class Node
{
	public:
		int info;
		Node *link;

		Node(int data)
		{
			info = data;
			link = NULL;
		}
};//End of class Node

class SingleLinkedList
{
	private:
		Node *start;

		bool search(Node *ptr, int data);

	public:
		SingleLinkedList()
		{
			start = NULL;
		}
		bool isEmpty();
		void insertAtBeginning(int data);
		void display();
		bool search(int data);
};//End of class SingleLinkedList

bool SingleLinkedList::isEmpty()
{
	return start==NULL;
}//End of isEmpty()

void SingleLinkedList::insertAtBeginning(int data)
{
	Node *temp;

	temp = new Node(data);
	if(!isEmpty())
		temp->link = start;

	start = temp;
}//End of insertAtBeginning()

void SingleLinkedList::display()
{
	Node *ptr;

	if(isEmpty())
	{
		cout << "List is empty\n";
	}
	else
	{
		ptr = start;
		while(ptr != NULL)
		{
			cout << ptr->info << "\n";
			ptr = ptr->link;
		}
	}
}//End of display()

bool SingleLinkedList::search(Node *ptr, int data)
{
	if(ptr == NULL)
		return false;

	if(ptr->info == data)
		return true;

	search(ptr->link, data);
}//End of search()

bool SingleLinkedList::search(int data)
{
	return search(start, data);
}//End of search()

int main()
{
	SingleLinkedList singleLinkedList;

	singleLinkedList.insertAtBeginning(50);
	singleLinkedList.insertAtBeginning(40);
	singleLinkedList.insertAtBeginning(30);
	singleLinkedList.insertAtBeginning(20);
	singleLinkedList.insertAtBeginning(10);

	cout << "List Items :\n";
	singleLinkedList.display();

	int nodeData = 40;

	cout << "List node " << nodeData << " found : " << (singleLinkedList.search(nodeData) ? "True" : "False");
	cout << "\n";
	
	return 0;
}//End of main()
