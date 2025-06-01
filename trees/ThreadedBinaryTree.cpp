//ThreadedBinaryTree.cpp : Program for Threaded Binary Tree.

#include<iostream>
using namespace std;

class Node
{
	public:
		int info;
		Node *lchild;
		Node *rchild;
		bool lthread;
		bool rthread;

		Node(int key)
		{
			info = key;
			lchild = NULL;
			rchild = NULL;
			lthread = true;
			rthread = true;
		}
};//End of class Node

class ThreadedBinaryTree
{
	private:
		Node *root;

		Node* inorderPredecessor(Node *ptr);
		Node* inorderSuccessor(Node *ptr);

	public:
		ThreadedBinaryTree();
		~ThreadedBinaryTree(){};
		bool isEmpty();
		void insert(int key);
		void del(int key);
		void inorder();
		void preorder();
};//End of class ThreadedBinaryTree

ThreadedBinaryTree::ThreadedBinaryTree()
{
	root = NULL;
}//End of ThreadedBinaryTree()

bool ThreadedBinaryTree::isEmpty()
{
	return root==NULL;
}//End of isEmpty()

void ThreadedBinaryTree::insert(int key)
{
	Node *parent = NULL;
	Node *ptr = root;

	while(ptr != NULL)
	{
		parent = ptr;

		if(key < ptr->info)
		{
			if(ptr->lthread == false)
				ptr = ptr->lchild;
			else
				break;
		}
		else if(key > ptr->info)
		{
			if(ptr->rthread == false)
				ptr = ptr->rchild;
			else
				break;
		}
		else
		{
			cout << key << " is already there\n";
			return;
		}
	}//End of while

	Node *temp = new Node(key);

	if(parent == NULL)
		root = temp;
	else if(key < parent->info)	//Inserted as left child
	{
		temp->lchild = parent->lchild;
		temp->rchild = parent;
		parent->lthread = false;
		parent->lchild = temp;
	}
	else	//Inserted as right child
	{
		temp->lchild = parent;
		temp->rchild = parent->rchild;
		parent->rthread = false;
		parent->rchild = temp;
	}

}//End of insert()

void ThreadedBinaryTree::inorder()
{
	if(root == NULL)
	{
		cout << "Tree is empty\n";
		return;
	}

	//Find the leftmost node of the tree
	Node *ptr = root;

	while(ptr->lthread == false)
		ptr = ptr->lchild;

	while(ptr != NULL)
	{
		cout << ptr->info << " ";
		
		if(ptr->rthread == true)
			ptr = ptr->rchild;
		else
		{
			ptr = ptr->rchild;
			while(ptr->lthread == false)
				ptr = ptr->lchild;
		}
	}
}//End of inorder()

void ThreadedBinaryTree::preorder()
{
	if(root == NULL)
	{
		cout << "Tree is empty\n";
		return;
	}

	Node *ptr = root;
	while(ptr != NULL)
	{
		cout << ptr->info << " ";
		if(ptr->lthread == false)
			ptr = ptr->lchild;
		else if(ptr->rthread == false)
			ptr = ptr->rchild;
		else
		{
			while(ptr!=NULL && ptr->rthread==true)
				ptr = ptr->rchild;

			if(ptr != NULL)
				ptr = ptr->rchild;
		}
	}
}//End of preorder()

Node* ThreadedBinaryTree::inorderPredecessor(Node *ptr)
{
	if(ptr->lthread == true)
	{
		return ptr->lchild;
	}
	else
	{
		ptr = ptr->lchild;
		while(ptr->rthread == false)
			ptr = ptr->rchild;
		return ptr;
	}
}//End of inorderPredecessor()

Node* ThreadedBinaryTree::inorderSuccessor(Node *ptr)
{
	if(ptr->rthread == true)
	{
		return ptr->rchild;
	}
	else
	{
		ptr = ptr->rchild;
		while(ptr->lthread == false)
			ptr = ptr->lchild;
		return ptr;
	}
}//End of inorderSuccessor()

void ThreadedBinaryTree::del(int key)
{
	Node *parent = NULL;
	Node *ptr = root;

	while(ptr != NULL)
	{
		if(ptr->info == key)
			break;

		parent = ptr;
		if(key < ptr->info)
		{
			if(ptr->lthread == false)
				ptr = ptr->lchild;
			else
				break;
		}
		else
		{
			if(ptr->rthread == false)
				ptr = ptr->rchild;
			else
				break;
		}

	}//End of while

	if(ptr!=NULL && ptr->info!=key)
	{
		cout << key << " not found\n";
		return;
	}

	//Case C : 2 children
	if(ptr->lthread==false && ptr->rthread==false)
	{
		//Find inorder successor and its parent
		Node *ps = ptr;
		Node *s = ptr->rchild;

		while(s->lthread == false)
		{
			ps = s;
			s = s->lchild;
		}
		ptr->info = s->info;
		ptr = s;
		parent = ps;
	}

	//Case A : no child
	if(ptr->lthread==true && ptr->rthread==true)
	{
		if(parent == NULL)	//key to be deleted is in root node
			root = NULL;
		else if(ptr == parent->lchild)
		{
			parent->lthread = true;
			parent->lchild = ptr->lchild;
		}
		else
		{
			parent->rthread = true;
			parent->rchild = ptr->rchild;
		}

		delete ptr;
		return;
	}

	//Case B : 1 child
	Node *child;
	//Initialize child
	if(ptr->lthread == false)	//Node to be deleted has left child
		child = ptr->lchild;
	else	//Node to be deleted has right child
		child = ptr->rchild;

	if(parent == NULL)	//Node to be deleted is root node
		root = child;
	else if(ptr == parent->lchild)	//Node is left child of its parent
		parent->lchild = child;
	else	//Node is right child of its parent
		parent->rchild = child;

	Node *pred = inorderPredecessor(ptr);
	Node *succ = inorderSuccessor(ptr);

	if(ptr->lthread == false)	//If ptr has left child, right is a thread
		pred->rchild = succ;
	else	//ptr has right child, left is a thread
		succ->lchild = pred;

	delete ptr;
}//End of del()

int main()
{
	ThreadedBinaryTree threadedTree;

	threadedTree.insert(67);
	threadedTree.insert(34);
	threadedTree.insert(81);
	threadedTree.insert(12);
	threadedTree.insert(45);
	threadedTree.insert(78);
	threadedTree.insert(95);
	threadedTree.insert(20);
	threadedTree.insert(40);
	threadedTree.insert(89);
	threadedTree.insert(98);

	cout << "Inorder traversal :\n";
	threadedTree.inorder();
	cout << "\n";
	cout << "Preorder traversal :\n";
	threadedTree.preorder();
	cout << "\n";

	threadedTree.del(81);		//Case C
	cout << "Inorder traversal after deleting 81 :\n";
	threadedTree.inorder();
	cout << "\n";

	threadedTree.del(45);		//Case B (left child)
	cout << "Inorder traversal after deleting 45 :\n";
	threadedTree.inorder();
	cout << "\n";

	threadedTree.del(20);		//Case B (right child)
	cout << "Inorder traversal after deleting 20 :\n";
	threadedTree.inorder();
	cout << "\n";

	threadedTree.del(40);		//Case A (leaf node)
	cout << "Inorder traversal after deleting 40 :\n";
	threadedTree.inorder();
	cout << "\n";

	threadedTree.del(67);		//Case C (root node)
	cout << "Inorder traversal after deleting 67 :\n";
	threadedTree.inorder();
	cout << "\n";

	return 0;
}//End of main()