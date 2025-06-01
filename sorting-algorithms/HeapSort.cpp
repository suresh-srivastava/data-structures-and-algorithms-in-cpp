//HeapSort.cpp : Program of sorting using heap sort.

#include<iostream>
using namespace std;

static const int maxSize = 30;

void restoreDown(int i, int arr[], int n)
{
	int k = arr[i];
	int lchild = 2*i;
	int rchild = lchild+1;

	while(rchild <= n)
	{
		if(k>=arr[lchild] && k>=arr[rchild])
		{
			arr[i] = k;
			return;
		}
		else if(arr[lchild] > arr[rchild])
		{
			arr[i] = arr[lchild];
			i = lchild;
		}
		else
		{
			arr[i] = arr[rchild];
			i = rchild;
		}
		lchild = i*2;
		rchild = lchild+1;
	}//End of while

	//If number of nodes is even
	if(lchild==n && k<arr[lchild])
	{
		arr[i] = arr[lchild];
		i = lchild;
	}

	arr[i] = k;
}//End of restoreDown()

void buildHeapBottomUp(int arr[], int n)
{
	for( int i=n/2; i>=1; i-- )
		restoreDown(i,arr,n);
}//End of buildHeapBottomUp()

void heapSort(int arr[], int n)
{
	buildHeapBottomUp(arr,n);

	cout << "Heap is :\n";
	for(int i=1; i<=n; i++)
		cout << arr[i] << " ";
	cout << "\n";

	//deleting the root and moving it(maxValue) to arr[n]
	int maxValue;
	while(n > 1)
	{
		maxValue = arr[1];
		arr[1] = arr[n];
		arr[n] = maxValue;
		n--;
		restoreDown(1,arr,n);

		cout << "Heap is :\n";
		for(int i=1; i<=n; i++)
			cout << arr[i] << " ";
		cout << "\n";
	}
}//End of heapSort()

int main()
{
	int arr[maxSize] = {9999, 25, 35, 18, 9, 46, 70, 48, 23, 78, 12, 95}; //data is from arr[1]
	int n = 11; //data is from arr[1]...arr[11]

	cout << "Unsorted list is :\n";
	for(int i=1; i<=n; i++)
		cout << arr[i] << " ";
	cout << "\n";

	heapSort(arr,n);
	
	cout << "Sorted list is :\n"; 
	for(int i=1; i<=n; i++ )
		cout << arr[i] << " ";
	cout << "\n";
}//End of main()







