//LinkedList6.cpp : Program to insert a node at the end of a single linked list.

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

		Node* insertAtEnd(Node *ptr, int data);

	public:
		SingleLinkedList()
		{
			start = NULL;
		}
		bool isEmpty();
		void insertAtBeginning(int data);
		void display();
		void insertAtEnd(int data);
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

Node* SingleLinkedList::insertAtEnd(Node *ptr, int data)
{
	Node *temp;

	if(ptr == NULL)
	{
		temp = new Node(data);
		return temp;
	}

	ptr->link = insertAtEnd(ptr->link, data);

	return ptr;
}//End of insertAtEnd()

void SingleLinkedList::insertAtEnd(int data)
{
	start = insertAtEnd(start, data);
}//End of insertAtEnd()

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

	int data = 75;
	
	singleLinkedList.insertAtEnd(data);

	cout << "After inserting " << data << " at the end, list items are : \n";
	singleLinkedList.display();

	return 0;
}//End of main()
