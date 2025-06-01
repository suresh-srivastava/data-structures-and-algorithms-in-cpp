//BubbleSort.cpp : Program of sorting using bubble sort.

#include<iostream>
using namespace std;

static const int maxSize = 30;

void bubbleSort(int arr[], int n)
{
	int temp, xchanges;

	for(int i=0; i<n-1 ;i++)
	{
		xchanges = 0;
		for(int j=0; j<n-1-i; j++)
		{
			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				xchanges++;
			}
		}
		if(xchanges == 0) //If list is sorted
			break;
	}//End of for
}//End of bubbleSort()

int main()
{
	int arr[maxSize] = {40, 20, 50, 60, 30, 10, 90, 97, 70, 80};
	int n = 10;

	cout << "Unsorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

	bubbleSort(arr,n);
	
	cout << "Sorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

}//End of main()

