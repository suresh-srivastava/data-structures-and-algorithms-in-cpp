//RadixSort.cpp : Program of sorting using radix sort.

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

//Returns kth digit from right in n
int getDigit(int n, int k)
{
	int digit=0;
	for(int i=1; i<=k; i++)
	{
		digit = n%10 ;
		n /= 10;
	}

	return digit;
}//End of digit()

//Returns number of digits in the largest element of the list
int digitsInLargest(Node *start)
{
	//Find largest element
	Node *ptr = start;
	int large = 0;

	while(ptr != NULL)
	{
		if(ptr->info > large)
			large = ptr->info;
		ptr = ptr->link;
	}
	
	//Find number of digits in largest element
	int ndigits = 0;
	while(large != 0)
	{
		ndigits++;
		large /= 10;
	}

	return ndigits;
}//End of digitsInLargest()

void radixSort(int arr[], int n)
{
	Node *temp;
	Node *start = NULL;

	//Creating linked list by insertion at beginning from arr[n-1]...arr[0]
	for(int i=n-1; i>=0; i--)
	{
		temp = new Node(arr[i]);
		temp->link = start;
		start = temp;
	}

	Node *rear[10], *front[10];

	int leastSigPos = 1;
    int mostSigPos = digitsInLargest(start);

    int i, digit;
    Node *ptr;

	for(int k=leastSigPos; k<=mostSigPos; k++) 
	{
		//Make all the queues empty at the beginning of each pass
		for(i=0; i<=9 ; i++)
		{
			rear[i] = NULL;
			front[i] = NULL;
		}
		
		for(ptr=start; ptr!=NULL; ptr=ptr->link)
		{
			//Find kth digit from right in the number
			digit = getDigit(ptr->info, k);
		
			//Insert the node in Queue(dig)
			if(front[digit] == NULL)
				front[digit] = ptr ;
			else
				rear[digit]->link = ptr;
			rear[digit] = ptr;
		}
		
		//Join all the queues to form the new linked list
		i=0;
		while(front[i] == NULL)	//Finding first non empty queue
			i++;

		start = front[i];	
		while(i<=8) 
		{
			if(rear[i+1] != NULL) //if (i+1)th  queue is not empty
				rear[i]->link = front[i+1];	//join end of ith queue to start of (i+1)th queue
			else
				rear[i+1] = rear[i];	//continue with rear[i]
			i++;
		}
		rear[9]->link = NULL;
	}//End of for

	//Copying linked list to arr and deleting the linked list
	i=0;
	ptr=start;
	while(ptr != NULL)
	{
		arr[i++] = ptr->info;
		ptr = ptr->link;
		delete start;
		start = ptr;
	}

}//End of radixSort()

int main()
{
	int arr[maxSize] = {62, 234, 456, 750, 789, 3, 21, 345, 983, 99, 153, 65, 23, 5, 98, 10, 6, 372};
	int n = 18;

	cout << "Unsorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

	radixSort(arr, n);

	cout << "Sorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

}//End of main()