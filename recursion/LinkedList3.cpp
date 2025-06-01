//LinkedList3.cpp : Program to display the elements of a single linked list.

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

		void display(Node *ptr);

	public:
		SingleLinkedList()
		{
			start = NULL;
		}
		bool isEmpty();
		void insertAtBeginning(int data);
		void display();
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

void SingleLinkedList::display(Node *ptr)
{
	if(ptr == NULL)
		return;

	cout << ptr->info << "\n";
	display(ptr->link);
}//End of display()

void SingleLinkedList::display()
{
	display(start);
}//End of display()

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
	
	return 0;
}//End of main()


