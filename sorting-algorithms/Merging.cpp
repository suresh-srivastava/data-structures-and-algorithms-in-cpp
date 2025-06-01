//Merging.cpp : Program of merging two sorted arrays into a third sorted array.

#include<iostream>
using namespace std;

static const int maxSize = 30;

void merge(int arr1[], int arr2[], int temp[], int n1, int n2)
{
	int i = 0;	//Index for first array
	int j = 0;	//Index for second array
	int k = 0;	//Index for merged array

	while(i<=n1-1  && j<=n2-1)
	{
		if(arr1[i] < arr2[j])
			temp[k++] = arr1[i++];
		else
			temp[k++] = arr2[j++];
	}

	//Put remaining elements of arr1 into temp
	while(i <= n1-1)
		temp[k++] = arr1[i++];
	
	//Put remaining elements of arr2 into temp
	while(j <= n2-1)
		temp[k++] = arr2[j++];
}//End of merge()

int main()
{
	int arr1[maxSize] = {5, 8, 9, 28, 34};
	int n1 = 5;

	int arr2[maxSize] = {4, 22, 25, 30, 33, 40, 42};
	int n2 = 7;

	int temp[2*maxSize];

	cout << "Array 1 in sorted order :\n";
	for(int i=0; i<n1; i++)
		cout << arr1[i] << "  ";
	
	cout << "\nArray 2 in sorted order :\n";
	for(int i=0; i<n2; i++)
		cout << arr2[i] << "  ";
	
	merge(arr1,arr2,temp,n1,n2);
	
	cout << "\nMerged list :\n";
	for(int i=0; i<n1+n2; i++)
		cout << temp[i] << "  ";
	cout << "\n";
}//End of main()
