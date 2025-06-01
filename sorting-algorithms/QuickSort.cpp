//QuickSort.cpp : Program of sorting using quick sort.

#include<iostream>
using namespace std;

static const int maxSize = 30;

int partition(int arr[], int low, int up)
{	
	int pivot = arr[low];

	int i = low+1;	//moves from left to right
	int j = up;		//moves from right to left

	int temp;
	
	while(i <= j)
	{
		while(arr[i]<pivot && i<up)
			i++;
		
		while(arr[j] > pivot)	
			j--;
		
		if(i < j)	//swap arr[i] and arr[j]
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
		else	//found proper place for pivot
			i++;
	}//End of while

	//Proper place for pivot is j
	arr[low] = arr[j];
	arr[j] = pivot;
	
	return j;
}//End of partition()

//Recursive quickSort()
void quickSort(int arr[], int low, int up )
{
	if(low >= up)
		return;

	int pivotloc = partition(arr,low,up);
	quickSort(arr,low,pivotloc-1); //process left sublist
	quickSort(arr,pivotloc+1,up);  //process right sublist
}//End of quickSort()

void quickSort(int arr[], int n)
{
	quickSort(arr, 0, n-1);
}//End of quickSort()

int main()
{
	int arr[maxSize] = {48, 44, 19, 59, 72, 80, 42, 65, 82, 8, 95, 68};
	int n = 11;

	cout << "Unsorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

	quickSort(arr,n);
	
	cout << "Sorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

}//End of main()
