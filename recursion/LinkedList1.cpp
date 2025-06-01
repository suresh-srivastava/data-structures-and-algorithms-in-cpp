//LinkedList1.cpp :	Program to get the length of a single linked list.

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

		int length(Node *ptr);

	public:
		SingleLinkedList()
		{
			start = NULL;
		}
		bool isEmpty();
		void insertAtBeginning(int data);
		void display();
		int length();
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

int SingleLinkedList::length(Node *ptr)
{
	if(ptr == NULL)
		return 0;

	return (1 + length(ptr->link));
}//End of length()

int SingleLinkedList::length()
{
	return length(start);
}//End of length()

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

	cout << "Length of list is : " << singleLinkedList.length() << "\n";
	
	return 0;
}//End of main()
