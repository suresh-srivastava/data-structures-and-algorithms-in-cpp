//LinkedList7.cpp : Program to delete the last node of a single linked list.

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

		Node* delAtEnd(Node *ptr);

	public:
		SingleLinkedList()
		{
			start = NULL;
		}
		bool isEmpty();
		void insertAtBeginning(int data);
		void display();
		void delAtEnd();
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

Node* SingleLinkedList::delAtEnd(Node *ptr)
{
	if(ptr->link == NULL)
	{
		delete ptr;
		return NULL;
	}

	ptr->link = delAtEnd(ptr->link);

	return ptr;
}//End of delAtEnd()

void SingleLinkedList::delAtEnd()
{
	start = delAtEnd(start);
}//End of delAtEnd()

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

	singleLinkedList.delAtEnd();

	cout << "After Deletion of last node, list items are :\n";
	singleLinkedList.display();

	return 0;
}//End of main()
