//SingleLinkedListH.cpp : Program of single linked list with header node.

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

class SingleLinkedListH
{
	private:
		Node *head;
		
	public:
		SingleLinkedListH();
		SingleLinkedListH(const SingleLinkedListH& list);
		SingleLinkedListH& operator=(const SingleLinkedListH& list);
		~SingleLinkedListH();

		bool isEmpty();
		void display();
		void insertAtBeginning(int data);
		void insertAtEnd(int data);
		void insertBefore(int data, int nodeData);
		void insertAfter(int data, int nodeData);
		void insertAtPosition(int data, int position);
		void deleteAtBeginning();
		void deleteAtEnd();
		void deleteNode(int nodeData);
		void deleteAtPosition(int position);
		void reverse();

};//End of class SingleLinkedListH

SingleLinkedListH::SingleLinkedListH()
{
	head = new Node(0);
}//End of SingleLinkedListH()

SingleLinkedListH::~SingleLinkedListH()
{
	Node *ptr;
	while(head != NULL)
	{
		ptr = head->link;
		delete head;
		head = ptr;
	}
}//End of ~SingleLinkedListH()

SingleLinkedListH::SingleLinkedListH(const SingleLinkedListH& list)
{
	Node *ptr1, *ptr2;
	ptr1 = list.head;
	ptr2 = head = new Node(ptr1->info);
	ptr1 = ptr1->link;

	while(ptr1 != NULL)
	{		
		ptr2->link = new Node(ptr1->info);
		ptr2 = ptr2->link;
		ptr1 = ptr1->link;
	}
}//End of copy constructor

SingleLinkedListH& SingleLinkedListH::operator=(const SingleLinkedListH& list)
{
	if (this == &list)
		return *this;

	Node *ptr;
	while(head != NULL)
	{
		ptr = head->link;
		delete head;
		head = ptr;
	}
	
	if(list.head == NULL)
	{
		head = NULL;
		return *this;
	}	

	Node *ptr1, *ptr2;
		
	ptr1 = list.head;
	ptr2 = head = new Node(ptr1->info);
	ptr1 = ptr1->link;

	while(ptr1 != NULL)
	{		
		ptr2->link = new Node(ptr1->info);
		ptr2 = ptr2->link;
		ptr1 = ptr1->link;
	}

	return *this;
}//End of operator=

bool SingleLinkedListH::isEmpty()
{
	return (head->link == NULL);
}//End of isEmpty()

void SingleLinkedListH::display()
{
	Node *ptr;

	if(!isEmpty())
	{
		ptr = head->link;
		while(ptr != NULL)
		{
			cout << ptr->info << "\n";
			ptr = ptr->link;
		}
	}
	else
		cout << "List is empty\n";
}//End of display()

void SingleLinkedListH::insertAtBeginning(int data)
{
	Node *temp;

	temp = new Node(data);
	temp->link = head->link;
	head->link = temp;
}//End of insertAtBeginning()

void SingleLinkedListH::insertAtEnd(int data)
{
	Node *ptr, *temp;

	temp = new Node(data);

	ptr = head;
	while(ptr->link != NULL)
		ptr = ptr->link;
	ptr->link = temp;

}//End of insertAtEnd()

void SingleLinkedListH::insertBefore(int data, int nodeData)
{
	Node *ptr, *temp;

	ptr = head;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		//Find pointer to predecessor of node containing nodeData
		while(ptr->link != NULL)
		{
			if(ptr->link->info == nodeData)
			{
				temp = new Node(data);
				temp->link = ptr->link;
				ptr->link = temp;

				break;
			}
			ptr = ptr->link;
		}

		if(ptr->link == NULL)
			cout << "Item " << nodeData << " is not in the List\n";

	}//End of else

}//End of insertBefore()

void SingleLinkedListH::insertAfter(int data, int nodeData)
{
	Node *ptr, *temp;

	ptr = head->link;
	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		while(ptr != NULL)
		{
			if(ptr->info == nodeData)
			{
				temp = new Node(data);
				temp->link = ptr->link;
				ptr->link = temp;
				break;
			}
			ptr = ptr->link;
		}

		if(ptr == NULL)
			cout << "Item " << nodeData << " is not in the list\n";

	}//End of else
}//End of insertAfter()

void SingleLinkedListH::insertAtPosition(int data, int position)
{
	Node *ptr, *temp;

	if(position == 1)
	{
		temp = new Node(data);
		temp->link = head->link;
		head->link = temp;
	}
	else
	{
		ptr = head->link;
		int index = 1;
		while(ptr!=NULL && index < position-1) //Find a pointer to (position-1)th node
		{
			ptr = ptr->link;
			index++;
		}

		if(ptr!=NULL && position>0)
		{
			temp = new Node(data);
			temp->link = ptr->link;
			ptr->link = temp;
		}
		else
			cout << "Item cannot be inserted at position : " << position << "\n";

	}//End of else

}//End of insertAtPosition()

void SingleLinkedListH::deleteAtBeginning()
{
	Node *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else 
	{
		temp = head->link;
		head->link = temp->link;

		delete temp;
	}
}//End of deleteAtBeginning()

void SingleLinkedListH::deleteAtEnd()
{
	Node *ptr, *temp;

	ptr = head;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		while(ptr->link->link != NULL)
			ptr = ptr->link;

		temp = ptr->link;
		ptr->link = NULL;
		delete temp;
	}
}//End of deleteAtEnd()

void SingleLinkedListH::deleteNode(int nodeData)
{
	Node *ptr, *temp;

	ptr = head;
	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		while(ptr->link != NULL)
		{
			if(ptr->link->info == nodeData)
				break;
			ptr = ptr->link;
		}
		if(ptr->link == NULL)
			cout << nodeData << " not found in list\n";
		else
		{
			temp = ptr->link;
			ptr->link = ptr->link->link;
			delete temp;
		}
	}//End of else
}//End of deleteNode()

void SingleLinkedListH::deleteAtPosition(int position)
{
	Node *ptr, *temp;

	ptr = head->link;

	if(isEmpty())
		cout << "List is empty\n";
	else if(position == 1)
	{
		temp = head->link;
		head->link = ptr->link;
		delete temp;
	}
	else
	{
		int index = 1;

		while(ptr->link!=NULL && index < position-1)
		{
			ptr = ptr->link;
			index++;
		}

		if(ptr->link!=NULL && position>0)
		{
			temp = ptr->link;
			ptr->link = ptr->link->link;
			delete temp;
		}
		else
			cout << "Node cannot be deleted at position : " << position << "\n";
	}//End of else

}//End of deleteAtPosition()

void SingleLinkedListH::reverse()
{
	Node *prev, *ptr, *next;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		ptr = head->link;
		prev = NULL;

		while(ptr != NULL)
		{
			next = ptr->link;
			ptr->link = prev;
			prev = ptr;
			ptr = next;
		}
		head->link = prev;
	}
}//End of reverse()

int main()
{
	SingleLinkedListH list1;

	//Create the List
	list1.insertAtBeginning(10);
	list1.insertAtEnd(30);
	list1.insertAfter(50,30);
	list1.insertAtPosition(20,2);
	list1.insertBefore(40,50);

	cout << "List1 Items after insertion :\n";
	list1.display();

	SingleLinkedListH list2(list1);
	cout << "List2 Items after using copy constructor :\n";
	list2.display();

	SingleLinkedListH list3;
	list3 = list1;
	cout << "List3 Items after using = operator :\n";
	list3.display();

	list1.deleteAtBeginning();
	list1.deleteAtEnd();
	list1.deleteNode(30);
	list1.deleteAtPosition(2);

	cout << "List1 Items after deletion :\n";
	list1.display();

	list2.reverse();
	cout << "List2 Items after reverse :\n";
	list2.display();

	return 0;
}//End of main()

