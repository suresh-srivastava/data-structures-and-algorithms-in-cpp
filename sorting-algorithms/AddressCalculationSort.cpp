//AddressCalculationSort.cpp : Program of sorting using address calculation sort.

#include<iostream>
using namespace std;

static const int maxSize = 30;

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
		bool isEmpty() const;
	public:
		SortedLinkedList();
		~SortedLinkedList();
		void insert(int data);
		Node* getStart();
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

Node* SortedLinkedList::getStart()
{ 
	return start;
}//End of getStart()

inline bool SortedLinkedList::isEmpty() const
{
	return start == NULL;
}//End of isEmpty()

void SortedLinkedList::insert(int data)
{
	Node *temp = new Node(data);
	
	//List empty or new node to be inserted before first node
	if(isEmpty() || data < start->info)
	{
		temp->link = start;
		start = temp;	
	}
	else
	{
		Node *ptr = start;
		while(ptr->link != NULL && ptr->link->info < data)
			ptr = ptr->link;
		temp->link = ptr->link;
		ptr->link = temp;
	}
}//End of insert()

int hashFn(int x, int large)
{
	float temp;
    temp = (float)x / large;
    return (int)(temp * 5);
}//End of hashFn()

void addressCalculationSort(int arr[], int n)
{
	SortedLinkedList list[6];
	int i;

	int large = 0;
    for(i=0; i<n; i++)
    {
		if(arr[i] > large)
			large = arr[i];
    }

	int x;
	for(i=0; i<n; i++)
	{
		x = hashFn(arr[i],large);
		list[x].insert(arr[i]);
	}

   //Elements of linked lists are copied to array
   Node *ptr;
   i = 0;
   for(int j=0; j<=5; j++)
   {
		ptr = list[j].getStart();
        while(ptr != NULL)
        {
			arr[i++] = ptr->info;
            ptr = ptr->link;
		}
    }//End of for
}//End of addressCalculationSort()

int main()
{
	int arr[maxSize] = {194, 289, 566, 432, 654, 98, 232, 415, 345, 276, 532, 254, 165, 965, 476};
	int n = 15;

	cout << "Unsorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

	addressCalculationSort(arr,n);
	
	cout << "Sorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

}//End of main()
