//CircularLinkedList.cpp : Program of Circular linked list.

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

class CircularLinkedList
{
	private:
		Node *last;

	public:
		CircularLinkedList();
		CircularLinkedList(const CircularLinkedList& list);
		CircularLinkedList& operator=(const CircularLinkedList& list);
		~CircularLinkedList();
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
		void concatenate(CircularLinkedList& list);
};//End of class CircularLinkedList

CircularLinkedList::CircularLinkedList()
{
	last = NULL;
}//End of CircularLinkedList()

CircularLinkedList::~CircularLinkedList()
{
	if(!isEmpty())
	{
		if(last->link == last)
		{
			delete last;
			last = NULL;
		}
		else
		{
			Node *ptr;
			do
			{
				ptr = last->link->link;
				delete last->link;
				last->link = ptr;
			}while(ptr != last);

			delete last;
			last = NULL;
		}
	}//End of if
}//End of ~CircularLinkedList()

CircularLinkedList::CircularLinkedList(const CircularLinkedList& list)
{
	if(list.last == NULL)
		last = NULL;
	else
	{
		Node *ptr1, *ptr2;

		ptr1 = list.last->link;
		ptr2 = last = new Node(ptr1->info);
		last->link = last;
		ptr1 = ptr1->link;

		while(ptr1 != list.last->link)
		{
			Node *temp = new Node(ptr1->info);
			temp->link = ptr2->link;
			ptr2->link = temp;
			ptr2 = ptr2->link;
			last = ptr2;
			ptr1 = ptr1->link;
		}
	}//End of else
}//End of copy constructor

CircularLinkedList& CircularLinkedList::operator=(const CircularLinkedList& list)
{
	if (last == list.last)
		return *this;

	if(!isEmpty())
	{
		if(last->link == last)
		{
			delete last;
			last = NULL;
		}
		else
		{
			Node *ptr;
			do
			{
				ptr = last->link->link;
				delete last->link;
				last->link = ptr;
			}while(ptr != last);

			delete last;
			last = NULL;
		}
	}//End of if
	
	if(list.last == NULL)
		last = NULL;
	else
	{
		Node *ptr1, *ptr2;

		ptr1 = list.last->link;
		ptr2 = last = new Node(ptr1->info);
		last->link = last;
		ptr1 = ptr1->link;

		while(ptr1 != list.last->link)
		{
			Node *temp = new Node(ptr1->info);
			temp->link = ptr2->link;
			ptr2->link = temp;
			ptr2 = ptr2->link;
			last = ptr2;
			ptr1 = ptr1->link;
		}
	}//End of else

	return *this;
}//End of operator=

bool CircularLinkedList::isEmpty()
{
	return (last == NULL);
}//End of isEmpty()

void CircularLinkedList::display()
{
	Node *ptr;

	if(!isEmpty())
	{
		ptr = last->link;
		do
		{
			cout << ptr->info << "\n";
			ptr = ptr->link;
		}while(ptr != last->link);
	}
	else
		cout << "List is empty\n";
}//End of display()

void CircularLinkedList::insertAtBeginning(int data)
{
	Node *temp;

	temp = new Node(data);
	if(isEmpty())
	{
		last = temp;
		last->link = temp;
	}
	else
	{
		temp->link = last->link;
		last->link = temp;
	}
	
}//End of insertAtBeginning()

void CircularLinkedList::insertAtEnd(int data)
{
	Node *temp;

	temp = new Node(data);

	if(isEmpty())
	{
		last = temp;
		last->link = temp;
	}
	else
	{
		temp->link = last->link;
		last->link = temp;
		last = temp;
	}
}//End of insertAtEnd()

void CircularLinkedList::insertBefore(int data, int nodeData)
{
	Node *ptr, *temp;

	ptr = last;

	if(isEmpty())
		cout << "List is empty\n";
	else if(ptr->link->info == nodeData) //nodeData is in first node
	{
		temp = new Node(data);
		temp->link = ptr->link;
		ptr->link = temp;
	}
	else
	{
		ptr = last->link;
		do
		{
			if(ptr->link->info == nodeData)
			{
				temp = new Node(data);
				temp->link = ptr->link;
				ptr->link = temp;
				break;
			}
			ptr = ptr->link;
		}while(ptr != last->link);

		if(ptr == last->link)
			cout << "Item " << nodeData << " is not in the list\n";

	}//End of else
}//End of insertBefore()

void CircularLinkedList::insertAfter(int data, int nodeData)
{
	Node *ptr, *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		ptr = last->link;
		do
		{
			if(ptr->info == nodeData)
			{
				temp = new Node(data);
				temp->link = ptr->link;
				ptr->link = temp;
				if(ptr == last)
					last = temp;
				break;
			}
			ptr = ptr->link;
		}while(ptr != last->link);

		if(ptr == last->link)
			cout << "Item " << nodeData << " is not in the list\n";

	}//End of else
}//End of insertAfter()

void CircularLinkedList::insertAtPosition(int data, int position)
{
	Node *ptr, *temp;

	ptr = last;

	if(isEmpty())
	{
		if(position == 1)
		{
			temp = new Node(data);
			last = temp;
			last->link = temp;
		}
		else
			cout << "Item cannot be inserted at position : " << position << "\n";
	}
	else if(position == 1)
	{
		temp = new Node(data);
		temp->link = last->link;
		last->link = temp;
	}
	else
	{
		ptr = last->link;
		int index = 1;
		do
		{
			if(index == position-1)
			{
				temp = new Node(data);
				temp->link = ptr->link;
				ptr->link = temp;
				if(ptr == last)
					last = temp;
				ptr = ptr->link;
				break;
			}
			index++;
			ptr = ptr->link;
		}while(ptr != last->link);

		if(ptr == last->link)
			cout << "Item cannot be inserted at position : " << position << "\n";

	}//End of else

}//End of insertAtPosition()

void CircularLinkedList::deleteAtBeginning()
{
	Node *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else if(last->link == last) //List has only one node
	{
		delete last;
		last = NULL;
	}
	else 
	{
		temp = last->link;
		last->link = temp->link;
		delete temp;
	}
}//End of deleteAtBeginning()

void CircularLinkedList::deleteAtEnd()
{
	Node *ptr, *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else if(last->link == last) //List has only one node
	{
		delete last;
		last = NULL;
	}
	else
	{
		ptr = last->link;
		while(ptr->link != last)
			ptr = ptr->link;

		ptr->link = last->link;
		delete last;
		last = ptr;
	}
}//End of deleteAtEnd()

void CircularLinkedList::deleteNode(int nodeData)
{
	Node *ptr, *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else if(last->link->info == nodeData) //Deletion of first node
	{
		if(last->link == last) //List has only one node
		{
			delete last;
			last = NULL;
		}
		else 
		{
			temp = last->link;
			last->link = temp->link;
			delete temp;
		}
	}
	else //Deletion in between or at the end
	{
		ptr = last->link;

		while(ptr->link != last->link)
		{
			if(ptr->link->info == nodeData)
				break;
			ptr = ptr->link;
		}
		if(ptr->link == last->link)
			cout << nodeData << " not found in list\n";
		else
		{
			temp = ptr->link;
			if(ptr->link == last)
				last = ptr;
			ptr->link = ptr->link->link;
			delete temp;
		}
	}//End of else
}//End of deleteNode()

void CircularLinkedList::deleteAtPosition(int position)
{
	Node *ptr, *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else if(position == 1) //Deletion of first node
	{
		if(last->link == last) //List has only one node
		{
			delete last;
			last = NULL;
		}
		else 
		{
			temp = last->link;
			last->link = temp->link;
			delete temp;
		}
	}
	else //Deletion in between or at the end
	{
		ptr = last->link;
		int index = 1;

		while(ptr->link != last->link)
		{
			if(index == position-1)
				break;
			index++;
			ptr = ptr->link;
		}
		if(ptr->link == last->link)
			cout << "Node cannot be deleted at position : " << position << "\n";
		else
		{
			temp = ptr->link;
			if(ptr->link == last)
				last = ptr;
			ptr->link = ptr->link->link;
			delete temp;
		}
	}//End of else
}//End of deleteAtPosition()

void CircularLinkedList::reverse()
{
	Node *prev, *ptr, *next;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		ptr = last->link;
		prev = last;

		while(ptr->link != last->link)
		{
			next = ptr->link;
			ptr->link = prev;
			prev = ptr;
			ptr = next;
		}
		last = ptr->link;
		last->link = ptr;
		ptr->link = prev;

	}
}//End of reverse()

void CircularLinkedList::concatenate(CircularLinkedList& list)
{
	Node *ptr;

	if(last == NULL)
	{
		last = list.last;
		list.last = NULL;
	}
	else if(list.last != NULL)
	{
		ptr = last->link;
		last->link = list.last->link;
		list.last->link = ptr;
		last = list.last;
	 
		list.last = NULL;
	}
}//End of concatenate()

int main()
{
	CircularLinkedList list1;

	//Create the List
	list1.insertAtBeginning(10);
	list1.insertAtEnd(30);
	list1.insertAfter(50,30);
	list1.insertAtPosition(20,2);
	list1.insertBefore(40,50);

	cout << "List1 Items after insertion :\n";
	list1.display();

	CircularLinkedList list2(list1);
	cout << "List2 Items after using copy constructor :\n";
	list2.display();

	CircularLinkedList list3;
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

	CircularLinkedList list4, list5;

	list4.insertAtEnd(10);
	list4.insertAtEnd(20);
	list4.insertAtEnd(30);
	list4.insertAtEnd(40);
	list4.insertAtEnd(50);

	cout << "List4 Items :\n";
	list4.display();

	list5.insertAtEnd(5);
	list5.insertAtEnd(15);
	list5.insertAtEnd(25);
	list5.insertAtEnd(35);
	list5.insertAtEnd(45);

	cout << "List5 Items :\n";
	list5.display();

	list4.concatenate(list5);

	cout << "List4 Items after concatenation :\n";
	list4.display();

	return 0;
}//End of main()










