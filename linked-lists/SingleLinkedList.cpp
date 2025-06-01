//SingleLinkedList.cpp : Program of Single linked list.

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

class SingleLinkedList
{
	private:
		Node *start;
		
		Node* merge1(Node *p1, Node *p2);
		Node* merge2(Node *p1, Node *p2);
		Node* divideList(Node *p);
		Node* mergeSortRec(Node *listStart);
		Node* findCycle();

	public:
		SingleLinkedList();
		SingleLinkedList(const SingleLinkedList& list);
		SingleLinkedList& operator=(const SingleLinkedList& list);
		~SingleLinkedList();

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

		void bubbleSortExchangeData();
		void bubbleSortExchangeLinks();

		void selectionSortExchangeData();
		void selectionSortExchangeLinks();

		void mergeLists1(const SingleLinkedList& list, SingleLinkedList& mergedList);
		void mergeList2(SingleLinkedList& list, SingleLinkedList& mergedList);

		void mergeSort();

		void concatenate(SingleLinkedList& list);

		void insertCycle(int nodeData);
		bool hasCycle();
		void removeCycle();
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

SingleLinkedList::SingleLinkedList(const SingleLinkedList& list)
{
	if(list.start == NULL)
		start = NULL;
	else
	{
		Node *ptr1, *ptr2;
		ptr1 = list.start;
		ptr2 = start = new Node(ptr1->info);
		ptr1 = ptr1->link;

		while(ptr1 != NULL)
		{		
			ptr2->link = new Node(ptr1->info);
			ptr2 = ptr2->link;
			ptr1 = ptr1->link;
		}
	}
}//End of copy constructor

SingleLinkedList& SingleLinkedList::operator=(const SingleLinkedList& list)
{
	if (this == &list)
		return *this;

	Node *ptr;
	while(start != NULL)
	{
		ptr = start->link;
		delete start;
		start = ptr;
	}
	
	if(list.start == NULL)
	{
		start = NULL;
		return *this;
	}	

	Node *ptr1, *ptr2;
		
	ptr1 = list.start;
	ptr2 = start = new Node(ptr1->info);
	ptr1 = ptr1->link;

	while(ptr1 != NULL)
	{		
		ptr2->link = new Node(ptr1->info);
		ptr2 = ptr2->link;
		ptr1 = ptr1->link;
	}

	return *this;
}//End of operator=

bool SingleLinkedList::isEmpty()
{
	return (start == NULL);
}//End of isEmpty()

void SingleLinkedList::display()
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

int SingleLinkedList::size()
{
	Node* ptr;
	int count = 0;

	ptr = start;
	while(ptr != NULL)
	{
		count++;
		ptr = ptr->link;
	}

	return count;
}//End of size()

int SingleLinkedList::find(int nodeData)
{
	Node *ptr = start;
	int position = 0;

	while(ptr != NULL)
	{
		position++;
		if(ptr->info == nodeData)
			return position;
		ptr = ptr->link;
	}

	return 0;
}//End of find()

void SingleLinkedList::insertAtBeginning(int data)
{
	Node *temp;

	temp = new Node(data);
	if(!isEmpty())
		temp->link = start;

	start = temp;
}//End of insertAtBeginning()

void SingleLinkedList::insertAtEnd(int data)
{
	Node *ptr, *temp;

	temp = new Node(data);

	if(isEmpty())
		start = temp;
	else
	{
		ptr = start;
		while(ptr->link != NULL)
			ptr = ptr->link;

		ptr->link = temp;
	}
}//End of insertAtEnd()

void SingleLinkedList::insertBefore(int data, int nodeData)
{
	Node *ptr, *temp;

	ptr = start;

	if(isEmpty())
		cout << "List is empty\n";
	else if(ptr->info == nodeData) //nodeData is in first node
	{
		temp = new Node(data);
		temp->link = ptr;
		start = temp;
	}
	else
	{
		//Get the pointer to predecessor of node containing nodeData
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

void SingleLinkedList::insertAfter(int data, int nodeData)
{
	Node *ptr, *temp;

	ptr = start;
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

void SingleLinkedList::insertAtPosition(int data, int position)
{
	Node *ptr, *temp;

	if(position == 1)
	{
		temp = new Node(data);
		temp->link = start;
		start = temp;
	}
	else
	{
		ptr = start;
		int index = 1;
		while(ptr!=NULL && index < position-1) //Get the pointer to (position-1)th node
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

void SingleLinkedList::deleteAtBeginning()
{
	Node *temp;

	if(isEmpty())
		cout << "List is empty\n";
	else 
	{
		temp = start;
		start = start->link;

		delete temp;
	}
}//End of deleteAtBeginning()

void SingleLinkedList::deleteAtEnd()
{
	Node *ptr, *temp;

	ptr = start;

	if(isEmpty())
		cout << "List is empty\n";
	else if(ptr->link == NULL)
	{
		temp = ptr;
		start = ptr->link;
		delete temp;
	}
	else
	{
		while(ptr->link->link != NULL)
			ptr = ptr->link;

		temp = ptr->link;
		ptr->link = NULL;
		delete temp;
	}
}//End of deleteAtEnd()

void SingleLinkedList::deleteNode(int nodeData)
{
	Node *ptr, *temp;

	ptr = start;
	if(isEmpty())
		cout << "List is empty\n";
	else if(ptr->info == nodeData) //Deletion of first node
	{
		temp = ptr;
		start = ptr->link;
		delete temp;
	}
	else //Deletion in between or at the end
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

void SingleLinkedList::deleteAtPosition(int position)
{
	Node *ptr, *temp;

	ptr = start;

	if(isEmpty())
		cout << "List is empty\n";
	else if(position == 1)
	{
		temp = start;
		start = start->link;
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

void SingleLinkedList::reverse()
{
	Node *prev, *ptr, *next;

	if(isEmpty())
		cout << "List is empty\n";
	else
	{
		ptr = start;
		prev = NULL;

		while(ptr != NULL)
		{
			next = ptr->link;
			ptr->link = prev;
			prev = ptr;
			ptr = next;
		}
		start = prev;
	}
}//End of reverse()

void SingleLinkedList::selectionSortExchangeData()
{
	Node *p, *q;
	int temp;

	p = start;

	for(p=start; p->link!=NULL; p=p->link)
	{
		for(q=p->link; q!=NULL; q=q->link)
		{
			if(p->info > q->info)
			{
				temp = p->info;
				p->info = q->info;
				q->info = temp;
			}
		}
	}
}//End of selectionSortExchangeData()

void SingleLinkedList::selectionSortExchangeLinks()
{
	Node *p, *q, *r, *s, *temp;

	for(r=p=start; p->link!=NULL; r=p,p=p->link)
	{
		for(s=q=p->link; q!=NULL; s=q,q=q->link)
		{
			if(p->info > q->info)
			{
				temp = p->link;
				p->link = q->link;
				q->link = temp;
				if(p != start)
					r->link = q;
				s->link = p;
				if(p == start)
					start = q;
				temp = p;
				p = q;
				q = temp;
			}//End of if
		}//End of for
	}//End of for
}//End of selectionSortExchangeLinks()

void SingleLinkedList::bubbleSortExchangeData()
{
	Node *p, *q, *end;
	int temp;

	for(end=NULL; end!=start->link; end=q)
	{
		for(p=start; p->link!=end; p=p->link)
		{
			q = p->link;
			if(p->info > q->info)
			{
				temp = p->info;
				p->info = q->info;
				q->info = temp;
			}
		}
	}
}//End of bubbleSortExchangeData()

void SingleLinkedList::bubbleSortExchangeLinks()
{
	Node *p, *q, *r, *end, *temp;

	for(end=NULL; end!=start->link; end=q)
	{
		for(r=p=start; p->link!=end; r=p,p=p->link)
		{
			q = p->link;
			if(p->info > q->info)
			{
				p->link = q->link;
				q->link = p;
				if(p != start)
					r->link = q;
				else
					start = q;

				//Rearranging the position of p and q for next pass
				temp = p;
				p = q;
				q = temp;
			}//End of if
		}//End of for
	}//End of for
}//End of bubbleSortExchangeLinks()

void SingleLinkedList::mergeLists1(const SingleLinkedList& list, SingleLinkedList& mergedList)
{
	mergedList.start = merge1(start, list.start);
}//End of mergeLists1()

//Merging 2 lists to another new list
Node* SingleLinkedList::merge1(Node* p1, Node* p2)
{
	Node* startM;

	if(p1->info <= p2->info)
	{
		startM = new Node(p1->info);
		p1 = p1->link;
	}
	else
	{
		startM = new Node(p2->info);
		p2 = p2->link;
	}

	Node *pM = startM;

	while(p1!=NULL && p2!=NULL)
	{
		if(p1->info <= p2->info)
		{
			pM->link = new Node(p1->info);
			p1 = p1->link;
		}
		else
		{
			pM->link = new Node(p2->info);
			p2 = p2->link;
		}
		pM = pM->link;
	}

	//Second list is finished. Add the elements of first list.
	while(p1 != NULL)
	{
		pM->link = new Node(p1->info);
		p1 = p1->link;
		pM = pM->link;
	}

	//First list is finished. Add the elements of second list.
	while(p2 != NULL)
	{
		pM->link = new Node(p2->info);
		p2 = p2->link;
		pM = pM->link;
	}

	return startM;
}//End of merge1()

void SingleLinkedList::mergeList2(SingleLinkedList& list, SingleLinkedList& mergedList)
{
	mergedList.start = merge2(start, list.start);
	start = NULL;
	list.start = NULL;
}//End of mergeList2()

//Merging lists by exchanging links
Node* SingleLinkedList::merge2(Node* p1, Node* p2)
{
	Node* startM;

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

	Node* pM = startM;

	while(p1!=NULL && p2!=NULL)
	{
		if(p1->info <= p2->info)
		{
			pM->link = p1;
			p1 = p1->link;
			pM = pM->link;
		}
		else
		{
			pM->link = p2;
			p2 = p2->link;
			pM = pM->link;
		}
	}

	//Second list is finished. Add the remaining elements of first list
	if(p1 != NULL)
		pM->link = p1;

	//First list is finished. Add the remaining elements of second list
	if(p2 != NULL)
		pM->link = p2;

	return startM;
}//End of merge2()

void SingleLinkedList::mergeSort()
{
	start = mergeSortRec(start);
}//End of mergeSort()

Node* SingleLinkedList::mergeSortRec(Node* listStart)
{
	//If the list is empty or has only one node
	if(listStart==NULL || listStart->link==NULL)
		return listStart;

	//If more than one element
	Node *start1 = listStart;
	Node *start2 = divideList(listStart);
	start1 = mergeSortRec(start1);
	start2 = mergeSortRec(start2);
	Node* startM = merge2(start1, start2);

	return startM;
}//End of mergeSortRec()

Node* SingleLinkedList::divideList(Node *p)
{
	Node *q = p->link->link;

	while(q!=NULL && q->link!=NULL)
	{
		p = p->link;
		q = q->link->link;
	}

	Node *start2 = p->link;
	p->link = NULL;

	return start2;
}//End of divideList()

void SingleLinkedList::concatenate(SingleLinkedList& list)
{
	if(start == NULL)
	{
		start = list.start;
		return;
	}

	if(list.start == NULL)   
		return;

	Node *ptr = start;
	while(ptr->link != NULL)
		ptr = ptr->link;

	ptr->link = list.start;
	list.start = NULL;
}//End of concatenate()

void SingleLinkedList::insertCycle(int nodeData)
{
	Node *ptr, *prev, *cyclePtr;

	cyclePtr = NULL;

	if(start==NULL || start->link==NULL)
		cout << "Cycle cannot be inserted\n";
	else
	{
		ptr = start;
		prev = start;
		while(ptr != NULL)
		{
			if(ptr->info == nodeData)
			{
				cyclePtr = ptr;
			}
			prev = ptr;
			ptr = ptr->link;
		}

		if(cyclePtr != NULL)
		{
			cout << "cyclePtr : " << cyclePtr << "\n";
			cout << "cyclePtr->info : " << cyclePtr->info << "\n";
			prev->link = cyclePtr;

			//Display the list (info and link)
			ptr = start;
			while(ptr != cyclePtr)
			{
				cout << "ptr->info = " << ptr->info << "\n";
				cout << "ptr->link = " << ptr->link << "\n";
				ptr = ptr->link;
			}

			ptr = cyclePtr;
			do
			{
				cout << "ptr->info = " << ptr->info << "\n";
				cout << "ptr->link = " << ptr->link << "\n";
				ptr = ptr->link;
			}while(ptr != cyclePtr);
		}//End of if
		else
			cout << nodeData << " is not found in the list\n";
	}//End of else
}//End of insertCycle()

Node* SingleLinkedList::findCycle()
{
	Node *slowPtr, *fastPtr;

	if(start==NULL || start->link==NULL)
		return NULL;
	else
	{
		slowPtr = start;
		fastPtr = start;

		while(fastPtr!=NULL && fastPtr->link!=NULL)
		{
			slowPtr = slowPtr->link;
			fastPtr = fastPtr->link->link;

			if(slowPtr == fastPtr)
			{
				cout << "slowPtr and fastPtr meets here\n";
				cout << "slowPtr->info = " << slowPtr->info << "\n";
				cout << "slowPtr->link = " << slowPtr->link << "\n";
				cout << "fastPtr->info = " << fastPtr->info << "\n";
				cout << "fastPtr->link = " << slowPtr->link << "\n";

				return slowPtr;
			}
		}//End of while

		return NULL;
	}//End of else

}//End of findCycle()

bool SingleLinkedList::hasCycle()
{
	if(findCycle() != NULL)
		return true;
	else
		return false;
}//End of hasCycle()

void SingleLinkedList::removeCycle()
{
	Node *ptr, *ptr1, *ptr2;

	ptr = findCycle();

	if(ptr == NULL)
		cout << "There is no cycle in list\n";
	else
	{
		cout << "Node where cycle was detected : " << ptr->info << "\n";
		ptr1 = ptr;
		ptr2 = ptr;

		//Find the length of cycle
		int cycleLength = 0;
		do
		{
			cycleLength++;
			ptr1 = ptr1->link;
		}while(ptr1 != ptr2);

		cout << "Cycle Length : " << cycleLength << "\n";

		//Find the remaining length
		int remLength = 0;
		ptr1 = start;
		while(ptr1 != ptr2)
		{
			remLength++;
			ptr1 = ptr1->link;
			ptr2 = ptr2->link;
		}

		cout << "Remaining Length : " << remLength << "\n";

		int listLength = cycleLength + remLength;

		cout << "The List is : \n";
		ptr1 = start;
		for(int i=1; i<=listLength-1; i++)
		{
			cout << ptr1->info << "\n";
			ptr1 = ptr1->link;
		}
		cout << ptr1->info << "\n";
		ptr1->link = NULL;
	}
}//End of removeCycle()

int main()
{
	SingleLinkedList list1;

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

	SingleLinkedList list2(list1);
	cout << "List2 Items after using copy constructor :\n";
	list2.display();

	SingleLinkedList list3;
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

	SingleLinkedList list4;
	list4.insertAtEnd(20);
	list4.insertAtEnd(10);
	list4.insertAtEnd(50);
	list4.insertAtEnd(30);
	list4.insertAtEnd(40);

	cout << "List4 Items :\n";
	list4.display();

	SingleLinkedList list5(list4), list6(list4), list7(list4);

	list4.selectionSortExchangeData();
	cout << "List4 Items after selection sort (exchange data) :\n";
	list4.display();

	list5.selectionSortExchangeLinks();
	cout << "List5 Items after selection sort (exchange links) :\n";
	list5.display();

	list6.bubbleSortExchangeData();
	cout << "List6 Items after bubble sort (exchange data) :\n";
	list6.display();

	list7.bubbleSortExchangeLinks();
	cout << "List7 Items after bubble sort (exchange links) :\n";
	list7.display();

	SingleLinkedList list8, list9, list10, list11;

	list8.insertAtEnd(10);
	list8.insertAtEnd(20);
	list8.insertAtEnd(30);
	list8.insertAtEnd(40);
	list8.insertAtEnd(50);

	cout << "List8 Items :\n";
	list8.display();

	list9.insertAtEnd(15);
	list9.insertAtEnd(25);
	list9.insertAtEnd(30);
	list9.insertAtEnd(45);
	list9.insertAtEnd(55);

	cout << "List9 Items :\n";
	list9.display();

	list8.mergeLists1(list9, list10);
	cout << "List10 Items - Mergeing 2 Lists to another new list :\n";
	list10.display();

	list8.mergeList2(list9, list11);
	cout << "List11 Items - Merged List (exchange links) :\n";
	list11.display();

	SingleLinkedList list12;

	list12.insertAtEnd(10);
	list12.insertAtEnd(5);
	list12.insertAtEnd(20);
	list12.insertAtEnd(15);
	list12.insertAtEnd(30);
	list12.insertAtEnd(25);
	list12.insertAtEnd(40);
	list12.insertAtEnd(35);

	cout << "List12 Items :\n";
	list12.display();

	list12.mergeSort();

	cout << "List12 Items after merge sort :\n";
	list12.display();

	SingleLinkedList list13, list14;

	list13.insertAtEnd(10);
	list13.insertAtEnd(20);
	list13.insertAtEnd(30);
	list13.insertAtEnd(40);
	list13.insertAtEnd(50);

	cout << "List13 Items :\n";
	list13.display();

	list14.insertAtEnd(5);
	list14.insertAtEnd(15);
	list14.insertAtEnd(25);
	list14.insertAtEnd(35);
	list14.insertAtEnd(45);

	cout << "List14 Items :\n";
	list14.display();

	list13.concatenate(list14);

	cout << "List13 Items after concatenation :\n";
	list13.display();

	SingleLinkedList list15;

	list15.insertAtEnd(10);
	list15.insertAtEnd(20);
	list15.insertAtEnd(30);
	list15.insertAtEnd(40);
	list15.insertAtEnd(50);
	list15.insertAtEnd(60);
	list15.insertAtEnd(70);
	list15.insertAtEnd(80);

	cout << "Finding a cycle and its removal in list :\n";
	cout << "find(40) = " << list15.find(40) << "\n";
	list15.insertCycle(40);
	cout << "Has cycle : " << (list15.hasCycle() ? "True" : "False") << "\n";
	list15.removeCycle();
	cout << "Has cycle : " << (list15.hasCycle() ? "True" : "False") << "\n";

	return 0;

}//End of main()
