//HeapTree.cpp : Program for Heap Tree.

#include<iostream>
using namespace std;

static const int maxSize = 30;

class HeapTree
{
	private:
		int heapArr[maxSize];
		int n;	//Number of elements in heap
		void restoreUp(int i);
		void restoreDown(int i);

	public:
		HeapTree();
		~HeapTree(){}
		bool isEmpty();
		void insert(int key);
		int deleteHeap();
		void display();
};//End of class HeapTree

HeapTree::HeapTree()
{
	n = 0;
	heapArr[0] = 9999;
}//End of HeapTree()

bool HeapTree::isEmpty()
{
	return n==0;
}//End of isEmpty()

void HeapTree::insert(int key)
{
	n++;	//Increase the heap size by 1
	heapArr[n] = key;
	restoreUp(n);
}//End of insert()

void HeapTree::restoreUp(int i)
{
	int k = heapArr[i];
	int iParent = i/2;

	while(heapArr[iParent] < k)
	{
		heapArr[i] = heapArr[iParent];
		i = iParent;
		iParent = i/2;
	}
	heapArr[i] = k;
}//End of restoreUp()

int HeapTree::deleteHeap()
{
	if(isEmpty())
		throw exception("Tree is empty\n");

	int maxValue = heapArr[1];	//Save the element present at the root
	heapArr[1] = heapArr[n];	//Place the last element in the root
	n--;						//Decrease the heap size by 1
	restoreDown(1);

	return maxValue;
}//End of deleteHeap()

void HeapTree::restoreDown(int i)
{
	int k = heapArr[i];
	int lchild = 2*i;
	int rchild = lchild+1;

	while(rchild <= n)
	{
		if(heapArr[lchild]<=k && heapArr[rchild]<=k)
		{
			heapArr[i] = k;
			return;
		}
		else if(heapArr[lchild] > heapArr[rchild])
		{
			heapArr[i] = heapArr[lchild];
			i = lchild;
		}
		else
		{
			heapArr[i] = heapArr[rchild];
			i = rchild;
		}

		lchild = 2*i;
		rchild = lchild+1;

	}//End of while

	//If number of nodes is even
	if(lchild==n && k<heapArr[lchild])
	{
		heapArr[i] = heapArr[lchild];
		i = lchild;
	}

	heapArr[i] = k;
}//End of restoreDown()

void HeapTree::display()
{
	for(int i=1; i<=n; i++)
		cout << heapArr[i] << " ";
	cout << "\n";
	cout << "Number of elements = " << n << "\n";
}//End of display()

int main()
{
	HeapTree heapTree;

	try
	{
		heapTree.insert(25);
		heapTree.display();
		heapTree.insert(35);
		heapTree.display();
		heapTree.insert(18);
		heapTree.display();
		heapTree.insert(9);
		heapTree.display();
		heapTree.insert(46);
		heapTree.display();
		heapTree.insert(70);
		heapTree.display();
		heapTree.insert(48);
		heapTree.display();
		heapTree.insert(23);
		heapTree.display();
		heapTree.insert(78);
		heapTree.display();
		heapTree.insert(12);
		heapTree.display();
		heapTree.insert(95);

		cout << "After Insertion :\n";
		heapTree.display();

		cout << "After Deletion :\n";
		cout << "Maximum Element : " << heapTree.deleteHeap() << "\n";
		heapTree.display();
		cout << "Maximum Element : " << heapTree.deleteHeap() << "\n";
		heapTree.display();
	}
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}//End of main()

