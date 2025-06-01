//DoublyLinkedList.cpp : Program of Doubly linked list.

#include<iostream>
using namespace std;

class Node
{
    public:
        int info;
        Node* prev;
        Node* next;

        Node(int data)
        {
            info = data;
            prev = NULL;
            next = NULL;
        }
};//End of class Node

class DoublyLinkedList
{
    private:
        Node* start;

    public:
		DoublyLinkedList();
		DoublyLinkedList(DoublyLinkedList& list);
		DoublyLinkedList& operator=(DoublyLinkedList& list);
		~DoublyLinkedList();

		bool isEmpty();
		void display();
		int size();
		int find(int data);
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
        
};//End of class DoublyLinkedList

DoublyLinkedList::DoublyLinkedList()
{
    start = NULL;
}//End of DoublyLinkedList()

DoublyLinkedList::~DoublyLinkedList()
{
	Node *ptr;

	while(start != NULL)
	{
		ptr = start->next;
		delete start;
		start = ptr;
	}
}//End of ~DoublyLinkedList()

DoublyLinkedList::DoublyLinkedList(DoublyLinkedList& list)
{
	if(list.start == NULL)
		start = NULL;
	else
	{
		Node *ptr1, *ptr2, *previous;
		
		ptr1 = list.start;
		ptr2 = start = new Node(ptr1->info);
		previous = NULL;
	
		ptr1 = ptr1->next;

		while(ptr1 != NULL)
		{		
			ptr2->next = new Node(ptr1->info);
			ptr2->prev = previous;
			previous = ptr2;
			ptr2 = ptr2->next;
			ptr1 = ptr1->next;
		}
		ptr2->prev = previous;
	}
}//End of copy constructor

DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList& list)
{
	if(this == &list)
		return *this;

	Node *ptr;
	while(start != NULL)
	{
		ptr = start->next;
		delete start;
		start = ptr;
	}
	
	if(list.start == NULL)
	{
		start = NULL;
		return *this;
	}	

	Node *ptr1, *ptr2, *previous;

	ptr1 = list.start;
	ptr2 = start = new Node(ptr1->info);
	previous = NULL;
	
	ptr1 = ptr1->next;

	while(ptr1 != NULL)
	{		
		ptr2->next = new Node(ptr1->info);
		ptr2->prev = previous;
		previous = ptr2;
		ptr2 = ptr2->next;
		ptr1 = ptr1->next;
	}
	ptr2->prev = previous;

	return *this;
}//End of operator=

bool DoublyLinkedList::isEmpty()
{
	return (start == NULL);
}//End of isEmpty()

void DoublyLinkedList::display()
{
	Node *ptr;

	if(!isEmpty())
	{
		ptr = start;
		while(ptr != NULL)
		{
			cout << ptr->info << "\n";
			ptr = ptr->next;
		}
	}
	else
		cout << "List is empty\n";
}//End of display()

int DoublyLinkedList::size()
{
	Node* ptr;
	int count = 0;

	ptr = start;
	while(ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}

	return count;
}//End of size()

int DoublyLinkedList::find(int nodeData)
{
	Node *ptr = start;
	int position = 0;

	while(ptr != NULL)
	{
		position++;
		if(ptr->info == nodeData)
			return position;
		ptr = ptr->next;
	}

	return 0;
}//End of find()

void DoublyLinkedList::insertAtBeginning(int data)
{
	Node *temp;

	temp = new Node(data);
	if(!isEmpty())
	{
		temp->next = start;
		start->prev = temp;
	}

	start = temp;
}//End of insertAtBeginning()

void DoublyLinkedList::insertAtEnd(int data)
{
	Node *ptr, *temp;

	temp = new Node(data);

	if(isEmpty())
		start = temp;
	else
	{
		ptr = start;
		while (ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = temp;
		temp->prev = ptr;
	}
}//End of insertAtEnd()

void DoublyLinkedList::insertBefore(int data, int nodeData)
{
	Node *ptr, *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else if(start->info == nodeData) //nodeData is in first node
	{
        temp = new Node(data);
        temp->next = start;
        start->prev = temp;
        start = temp;
	}
	else
	{
		ptr = start->next;
		while(ptr != NULL)
		{
			if(ptr->info == nodeData)
			{
				temp = new Node(data);
				temp->prev = ptr->prev;
				temp->next = ptr;
				ptr->prev->next = temp;
				ptr->prev = temp;
				break;
			}

			ptr = ptr->next;
		}

		if(ptr == NULL)
			cout << "Item " << nodeData << " is not in the List\n";

	}//End of else
}//End of insertBefore()

void DoublyLinkedList::insertAfter(int data, int nodeData)
{
	Node *ptr, *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		ptr = start;
		while(ptr != NULL)
		{
			if(ptr->info == nodeData)
			{
				temp = new Node(data);
				temp->prev = ptr;
				temp->next = ptr->next;
				if(ptr->next != NULL)
					ptr->next->prev = temp; //should not be done when ptr points to last node
				ptr->next = temp;

				break;
			}
			ptr = ptr->next;
		}

		if(ptr == NULL)
			cout << "Item " << nodeData << " is not in the list\n";

	}//End of else
}//End of insertAfter()

void DoublyLinkedList::insertAtPosition(int data, int position)
{
	Node *temp, *ptr;

	if(position == 1)
	{
		temp = new Node(data);
		if(!isEmpty())
		{
			temp->next = start;
			start->prev = temp;
		}
		start = temp;
	}
	else
	{
		ptr = start;
		int index = 1;
		while(ptr != NULL && index < position-1) //Find a pointer to (position-1)th node
		{
			ptr = ptr->next;
			index++;
		}

		if(ptr!=NULL && position>0)
		{
			temp = new Node(data);
			temp->prev = ptr;
			temp->next = ptr->next;
			if(ptr->next != NULL)
				ptr->next->prev = temp; //should not be done when ptr points to last node
			ptr->next = temp;
		}
		else
			cout << "Item cannot be inserted at position : " << position << "\n";

	}//End of else

}//End of insertAtPosition()

void DoublyLinkedList::deleteAtBeginning()
{
	Node *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else 
	{
		temp = start;
		if(start->next == NULL) //If list has only 1 node
			start = NULL;
		else
		{
			start = start->next;
			start->prev = NULL;
		}
		delete temp;
	}
}//End of deleteAtBeginning()

void DoublyLinkedList::deleteAtEnd()
{
	Node *ptr, *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		ptr = start;
		while(ptr->next != NULL)
			ptr = ptr->next;

		temp = ptr;
		if(temp->prev != NULL)
			temp->prev->next = NULL;
		else
			start = NULL;

		delete temp;
	}
}//End of deleteAtEnd()

void DoublyLinkedList::deleteNode(int nodeData)
{
	Node *ptr, *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		ptr = start;
		while(ptr->next != NULL)
		{
			if(ptr->info == nodeData)
				break;
        
			ptr = ptr->next;
		}

		if(ptr->info == nodeData)
		{
			temp = ptr;
			if(temp->next == NULL)
			{
				if(temp->prev == NULL) //First and only node
					start = NULL;
				else
					temp->prev->next = NULL; //Last node
			}
			else
			{
				if(temp->prev == NULL) //First node
				{
					temp->next->prev = NULL;
					start = temp->next;
				}
				else //Node in between
				{
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
				}
			}

			delete temp;
		}//End of if
		else
			cout << nodeData << " not found in list\n";

	}//End of else

}//End of deleteNode()

void DoublyLinkedList::deleteAtPosition(int position)
{
    Node *ptr, *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		ptr = start;
		int index = 1;
		while(ptr->next != NULL)
		{
			if(index == position)
				break;
        
			index++;
			ptr = ptr->next;
		}

		if(position == 1)
		{
			temp = ptr;
			if(temp->next == NULL) //First node of only node in list
				start = NULL;
			else //First node of more than one node in list
			{
				temp->next->prev = NULL;
				start = temp->next;
			}

			delete temp;
		}
		else if(index == position)
		{
			temp = ptr;
			if(temp->next == NULL)
				temp->prev->next = NULL;
			else
			{
				temp->next->prev = temp->prev;
				temp->prev->next = temp->next;
			}

			delete temp;
		}
		else
			cout << "Node cannot be deleted at position : " << position << "\n";

	}//End of else

}//End of deleteAtPosition()

void DoublyLinkedList::reverse()
{
    Node *ptr, *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		ptr = start;
		while(ptr->next != NULL)
		{
			temp = ptr->next;
			ptr->next = ptr->prev;
			ptr->prev = temp;
			ptr = temp;
		}

		ptr->next = ptr->prev;
		ptr->prev = NULL;
		start = ptr;
	}
}//End of reverse()

int main()
{
	DoublyLinkedList list1;

	//Create the List
	list1.insertAtBeginning(10);
	list1.insertAtEnd(30);
	list1.insertAfter(50,30);
	list1.insertAtPosition(20,2);
	list1.insertBefore(40,50);

	cout << "List1 Items after insertion :\n";
	list1.display();

	cout << "Total items : " << list1.size() << "\n";
	cout << "find(40) = " << list1.find(40) << "\n";

	DoublyLinkedList list2(list1);
	cout << "List2 Items after using copy constructor :\n";
	list2.display();

	DoublyLinkedList list3;
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
