//BinarySearchRecursive.cpp : Program of recursive binary search in an array

#include<iostream>
using namespace std;

static const int maxSize = 30;

int rbinarySearch(int arr[], int low, int up, int item)
{
	int mid;

	if(low > up)
		return -1;

	mid = (low+up)/2;

	if(item > arr[mid]) //Search in right half
		rbinarySearch(arr, mid+1, up, item);
	else if (item < arr[mid]) //Search in left half
		rbinarySearch(arr, low, mid-1, item);
	else
		return mid;
}//End of rbinarySearch()

int rbinarySearch(int arr[], int n, int item)
{
	return rbinarySearch(arr, 0, n-1, item);

}//End of rbinarySearch()

int main()
{
	int arr[maxSize] = {2, 9, 16, 19, 29, 36, 41, 67, 85, 96};
	int n = 10;
	int item = 29;
	
	int index = rbinarySearch(arr, n, item);

	if(index==-1)
		cout << item << " not found in array\n";
	else
		cout << item << " found at position " << index << "\n";

	return 0;
}//End of main()


