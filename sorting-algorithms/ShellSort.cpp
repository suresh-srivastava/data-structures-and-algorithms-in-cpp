//ShellSort.cpp : Program of sorting using shell sort.

#include<iostream>
using namespace std;

static const int maxSize = 30;

void shellSort(int arr[], int n)
{
	int i,j,k;
	int incr = 5; //maximum increment (odd value)
	
	while(incr >= 1)
	{
		for(i=incr; i<n; i++)
		{
			k=arr[i];
			for(j=i-incr; j>=0 && k<arr[j]; j=j-incr)
				arr[j+incr]=arr[j];
			arr[j+incr]=k;
		}//End of for
		incr=incr-2;	//Decrease the increment
	}//End of while

}//End of shellSort()

int main()
{
	int arr[maxSize] = {19, 63, 2, 6, 7, 10, 1, 18, 9, 4, 45, 3, 5, 17, 16, 12, 56};
	int n = 17;

	cout << "Unsorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

	shellSort(arr,n);
	
	cout << "Sorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

}//End of main()

