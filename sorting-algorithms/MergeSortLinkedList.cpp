//MergeSortLinkedList.cpp : Program of sorting using merge sort on linked list.
#include <iostream>
using namespace std;

class Node
{
	public:
		int info;
		Node* link;

		Node(int data)
		{
			info = data;
			link = NULL;
		}
};//End of class Node

class SingleLinkedList
{
	private:
		Node* start;
		
		Node* merge(Node* p1, Node* p2);
		Node* divideList(Node* p);
		Node* mergeSortRec(Node* listStart);

	public:
		SingleLinkedList();
		~SingleLinkedList();
		bool isEmpty();
		void insertAtBeginning(int data);
		void display();
		void mergeSort();
};//End of class SingleLinkedList

SingleLinkedList::SingleLinkedList()
{
	start = NULL;
}//End of SingleLinkedList()

SingleLinkedList::~SingleLinkedList()
{
	Node *ptr;
	while(start != NULL)
	{
		ptr = start->link;
		delete start;
		start = ptr;
	}
}//End of ~SingleLinkedList()

bool SingleLinkedList::isEmpty()
{
	return (start == NULL);
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

	if(!isEmpty())
	{
		ptr = start;
		while(ptr != NULL)
		{
			cout << ptr->info << " ";
			ptr = ptr->link;
		}
		cout << "\n";
	}
	else
		cout << "List is empty\n";
}//End of display()

Node* SingleLinkedList::merge(Node *p1, Node *p2)
{
	Node *startM;

	if(p1->info <= p2->info)
	{
		startM = p1;
		p1 = p1->link;
	}
	else
	{
		startM = p2;
		p2 = p2->link;
	}

	Node *pM = startM;

	while(p1 != NULL && p2 != NULL)
	{
		if(p1->info <= p2->info)
		{
			pM->link = p1;
			pM = pM->link;
			p1 = p1->link;
		}
		else
		{
			pM->link = p2;
			pM = pM->link;
			p2 = p2->link;
		}
	}//End of while

	if(p1 == NULL)
		pM->link = p2;
	else
		pM->link = p1;
     
	return startM;
}//End of merge()

Node* SingleLinkedList::divideList(Node* p)
{
	Node* q = p->link->link;

	while(q != NULL && q->link != NULL)
	{
		p = p->link;
		q = q->link->link;
	}

	Node *start2 = p->link;
	p->link = NULL;

	return start2;
}//End of divideList()

Node* SingleLinkedList::mergeSortRec(Node* listStart)
{
	if(listStart == NULL || listStart->link == NULL) //if list empty or has one element
		return listStart;

	//if more than one element
	Node* start1 = listStart;
	Node* start2 =divideList(listStart);
	start1 = mergeSortRec(start1);
	start2 = mergeSortRec(start2);
	Node* startM = merge(start1, start2);
	return startM;
}//End of mergeSortRec()

void SingleLinkedList::mergeSort()
{
	start = mergeSortRec(start);
}//End of mergeSort()

int main()
{
	SingleLinkedList list;

	//Create the List
	list.insertAtBeginning(3);
	list.insertAtBeginning(56);
	list.insertAtBeginning(21);
	list.insertAtBeginning(4);
	list.insertAtBeginning(64);
	list.insertAtBeginning(92);
	list.insertAtBeginning(42);
	list.insertAtBeginning(30);
	list.insertAtBeginning(89);
	list.insertAtBeginning(5);
	list.insertAtBeginning(8);

	cout << "List items :\n";
	list.display();

	list.mergeSort();

	cout << "List items after merge sort on list : \n";
	list.display();

}//End of main()
