//BinarySearch.cpp : Program of binary search in an array

#include<iostream>
using namespace std;

static const int maxSize = 30;

int binarySearch(int arr[], int n, int item)
{
	int low=0, up=n-1, mid;

	while(low <= up)
	{
		mid = (low+up)/2;
		if(item > arr[mid])
			low = mid+1;	//Search in right half
		else if(item < arr[mid])
			up = mid-1;		//Search in left half
		else
			return mid;
	}

	return -1;
}//End of binarySearch()

int main()
{
	int arr[maxSize] = {2, 9, 16, 19, 29, 36, 41, 67, 85, 96};
	int n = 10;
	int item = 29;
	
	int index = binarySearch(arr, n, item);

	if(index==-1)
		cout << item << " not found in array\n";
	else
		cout << item << " found at position " << index << "\n";

	return 0;
}//End of main()


