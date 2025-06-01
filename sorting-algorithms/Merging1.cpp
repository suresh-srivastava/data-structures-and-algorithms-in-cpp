//Merging1.cpp : Program of merging two sorted lists of an array into another array.

#include<iostream>
using namespace std;

static const int maxSize = 30;

//a[low1]...a[up1] and a[low2]...a[up2] merged to temp[low1]..temp[up2]
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

	while(i<=up1)
		temp[k++] = arr[i++];
	
	while(j<=up2)
		temp[k++] = arr[j++];
}//End of merge()

int main()
{
	int arr[maxSize] = {5,8,9,28,34, 4,22,25,30,33,40,42};
	int n = 12;

	int temp[maxSize];

	cout << "Array is :\n";
	for(int i=0; i<n; i++)
		cout << arr[i] << "  ";
	cout << "\n";

	merge(arr,temp,0,4, 5,11);
	
	cout << "Merged list :\n";
	for( int i=0; i<n; i++)
		cout << temp[i] << "  ";
	cout << "\n";
}//End of main()
