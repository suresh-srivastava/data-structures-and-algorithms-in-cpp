//BuildHeap.cpp : Program to build the heap.

#include<iostream>
using namespace std;

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
	for(int i=n/2; i>=1; i--)
		restoreDown(i, arr, n);
}//End of buildHeapBottomUp()

void restoreUp(int i, int arr[])
{
	int k = arr[i];
	int iParent = i/2;

	while(arr[iParent] < k)
	{
		arr[i] = arr[iParent];
		i = iParent;
		iParent = i/2;
	}
	arr[i] = k;
}//End of restoreUp()

void buildHeapTopDown(int arr[], int n)
{
	for(int i=2; i<=n; i++)
		restoreUp(i, arr);
}//End of buildHeapTopDown()

int main()
{
	int arr1[] = {9999, 25, 35, 18, 9, 46, 70, 48, 23, 78, 12, 95};
	int n1 = 11;

	cout << "Building Heap Botton Up :\n";
	buildHeapBottomUp(arr1, n1);

	for(int i=1; i<=n1; i++)
		cout << arr1[i] << " ";
	cout << "\n";

	int arr2[] = {9999, 25, 35, 18, 9, 46, 70, 48, 23, 78, 12, 95};
	int n2 = 11;

	cout << "Building Heap Top Down :\n";
	buildHeapTopDown(arr2, n2);

	for(int i=1; i<=n2; i++)
		cout << arr2[i] << " ";
	cout << "\n";

	return 0;
}//End of main()

