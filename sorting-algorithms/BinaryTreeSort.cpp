//BinaryTreeSort.cpp : Program of sorting using binary tree sort.

#include<iostream>
using namespace std;

static const int maxSize = 30;

class Node
{
	public:
		int info;
		Node *lchild;
		Node *rchild;

		Node(int data) 
		{
			info = data;
			lchild = NULL;
			rchild = NULL;
		}
};//End of class Node

class BinarySearchTree
{ 
	private:
		Node *root;
		static int k;

	private:
		void destroy(Node *ptr);
		Node* insert(Node *ptr, int data);
		void inorder(Node *ptr, int arr[]);
	public:
		BinarySearchTree();
		~BinarySearchTree();
		bool isEmpty();
		void insert(int data);
		void inorder(int arr[]);
};//End of class BinarySearchTree

int BinarySearchTree::k;   

BinarySearchTree::BinarySearchTree()
{
	root = NULL;
}//End of constructor BinarySearchTree()

BinarySearchTree::~BinarySearchTree()
{
	destroy(root);
	root = NULL;
}//End of destructor ~BinarySearchTree()

void BinarySearchTree::destroy(Node *ptr)
{
	if(ptr == NULL)
		return;
	destroy(ptr->lchild);
	destroy(ptr->rchild);
	delete ptr;
}//End of destroy()

bool BinarySearchTree::isEmpty()
{
	return root == NULL;
}//End of isEmpty()

Node* BinarySearchTree::insert(Node *ptr, int data)
{
	if(ptr == NULL)	
		ptr = new Node(data);
	else if(data < ptr->info)	
		ptr->lchild = insert(ptr->lchild, data);
	else 
		ptr->rchild = insert(ptr->rchild, data);  
	return ptr;
}//End of insert()

void BinarySearchTree::insert(int data)
{
	root = insert(root, data);
}//End of insert()

//Recursive inorder traversal
void BinarySearchTree::inorder(Node *ptr, int arr[])
{
	if(ptr == NULL)	
		return;
	inorder(ptr->lchild,arr);
	arr[k++] = ptr->info;
	inorder(ptr->rchild,arr);
}//End of inorder()

void BinarySearchTree::inorder(int arr[])
{
	k = 0;
	inorder(root,arr);
}//End of inorder()

void binaryTreeSort(int arr[], int n)
{
	BinarySearchTree bst;

    for(int i = 0; i < n; i++)
		bst.insert(arr[i]);
    bst.inorder(arr);
}//End of binaryTreeSort()

int main()
{
	int arr[maxSize] = {19, 35, 10, 12, 46, 6, 40, 3, 90, 8};
	int n = 10;

	cout << "Unsorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

	binaryTreeSort(arr,n);
	
	cout << "Sorted list is :\n"; 
	for(int i=0; i<n; i++)
		cout << arr[i] << " ";
	cout << "\n";

}//End of main()



