//InsertionSort.cpp : Program of sorting using insertion sort.

#include<iostream>
using namespace std;

static const int maxSize = 30;

void insertionSort(int arr[], int n)
{
	int i,j,k;

	for(i=1; i<n; i++)
	{
		k = arr[i]; 
		for(j=i-1; j>=0 && arr[j]>k; j--)
			arr[j+1] = arr[j];
		arr[j+1] = k;
	}//End of for
}//End of insertionSort()

int main()
{
	int arr[maxSize] = {82, 42, 49, 8, 25, 52, 36, 93, 59, 15};
	int n = 10;

	cout << "Unsorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

	insertionSort(arr,n);
	
	cout << "Sorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

}//End of main()

