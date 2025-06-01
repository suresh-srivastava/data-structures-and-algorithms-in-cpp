//LinearSearchSortedArray.cpp : Program of sequential search (linear search) in sorted array

#include<iostream>
using namespace std;

static const int maxSize = 30;

int linearSearch(int arr[], int n, int item)
{
	int i=0;

	while(i<n && arr[i]<item)
		i++;

	if(arr[i] == item)
		return i;
	else
		return -1;
}//End of linearSearch()

int main()
{
	int arr[maxSize] = {2, 9, 16, 19, 29, 36, 41, 67, 85, 96};
	int n = 10;
	int item = 29;
	
	int index = linearSearch(arr, n, item);

	if(index==-1)
		cout << item << " not found in array\n";
	else
		cout << item << " found at position " << index << "\n";

	return 0;
}//End of main()
