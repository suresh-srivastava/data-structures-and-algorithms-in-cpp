//SortedLinkedList.cpp : Program of sorted linked list.

#include<iostream>
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

class SortedLinkedList
{
	private:
		Node *start;
		
	public:
		SortedLinkedList();
		~SortedLinkedList();

		bool isEmpty();
		void display();
		int find(int data);
		void insert(int data);

};//End of class SortedLinkedList

SortedLinkedList::SortedLinkedList()
{
	start = NULL;
}//End of SortedLinkedList()

SortedLinkedList::~SortedLinkedList()
{
	Node *ptr;
	while(start != NULL)
	{
		ptr = start->link;
		delete start;
		start = ptr;
	}
}//End of ~SortedLinkedList()

bool SortedLinkedList::isEmpty()
{
	return (start == NULL);
}//End of isEmpty()

void SortedLinkedList::display()
{
	Node *ptr;

	if(!isEmpty())
	{
		ptr = start;
		while(ptr != NULL)
		{
			cout << ptr->info << "\n";
			ptr = ptr->link;
		}
	}
	else
		cout << "List is empty\n";
}//End of display()

int SortedLinkedList::find(int nodeData)
{
	Node *ptr = start;
	int position = 0;

	while(ptr!=NULL && ptr->info<=nodeData)
	{
		position++;
		if(ptr->info == nodeData)
			return position;
		ptr = ptr->link;
	}

	return 0;
}//End of find()

void SortedLinkedList::insert(int data)
{
	Node *ptr, *temp;

	temp = new Node(data);
	
	//List empty or new node to be inserted before first node
	if(isEmpty() || data < start->info)
	{
		temp->link = start;
		start = temp;	
	}
	else
	{
		ptr = start;
		while(ptr->link!=NULL && ptr->link->info < data)
			ptr = ptr->link;
		temp->link = ptr->link;
		ptr->link = temp;
	}
}//End of insert()

int main()
{
	SortedLinkedList list;

	list.insert(10);
	list.insert(20);
	list.insert(15);
	list.insert(40);
	list.insert(50);

	cout << "List Items :\n";
	list.display();

	cout << "find(40) = " << list.find(40) << "\n";

	return 0;
}//End of main()

