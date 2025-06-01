//MergeSortRecursive.cpp : Program of sorting using merge sort through recursion.

#include<iostream>
using namespace std;

static const int maxSize = 30;

//arr[low1]...arr[up1] and arr[low2]...arr[up2] merged to temp[low1]...temp[up2]
void merge(int arr[], int temp[], int low1, int up1, int low2, int up2)
{
	int i=low1, j=low2, k=low1;  	

	while(i<=up1 && j<=up2)
	{
		if(arr[i] < arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}

	while(i <= up1)
		temp[k++] = arr[i++];
	
	while(j <= up2)
		temp[k++] = arr[j++];
}//End of merge()

void copy(int arr[], int temp[], int low, int up)
{
	for(int i=low; i<=up; i++)
		arr[i] = temp[i];
}//End of copy()

void mergeSort(int arr[], int low, int up)
{
	int mid, temp[maxSize];

	if(low == up)	//if only one element
		return;
	
	mid = (low+up)/2;
	mergeSort(arr,low,mid);		//Sort arr[low]....arr[mid]
	mergeSort(arr,mid+1,up);	//Sort arr[mid+1]....arr[up]

	//Merge arr[low]...arr[mid] and arr[mid+1]....arr[up] to temp[low]...temp[up]
	merge(arr,temp,low,mid,mid+1,up); 

	//Copy temp[low]...temp[up] to arr[low]...arr[up]
	copy(arr,temp,low,up);
}//End of mergeSort()

void mergeSort(int arr[], int n)
{
	mergeSort(arr,0,n-1);
}//End of mergeSort()

int main()
{
	int arr[maxSize] = {8, 5, 89, 30, 42, 92, 64, 4, 21, 56, 3};
	int n = 11;

	cout << "Unsorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

	mergeSort(arr,n);
	
	cout << "Sorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

}//End of main()
