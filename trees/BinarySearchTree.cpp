//BinarySearchTree.cpp : Program for Binary Search Tree.

#include<iostream>

using namespace std;

class Node
{
	public:
		int info;
		Node *lchild;
		Node *rchild;

		Node(int key)
		{
			info = key;
			lchild = NULL;
			rchild = NULL;
		}
};//End of class Node

class BinarySearchTree
{
	private:
		Node *root;

		void display(Node *ptr, int level);
		Node* insert(Node *ptr, int key);
		Node* del(Node *ptr, int key);
		Node* copy(Node *ptr);
		void destroy(Node *ptr);
		Node* search(Node *ptr, int key);
		Node* min(Node *ptr);
		Node* max(Node *ptr);
		void caseA(Node *parent, Node *ptr);
		void caseB(Node *parent, Node *ptr);
		void caseC(Node *parent, Node *ptr);

	public:
		BinarySearchTree();
		~BinarySearchTree();
		BinarySearchTree(const BinarySearchTree &T);
		BinarySearchTree& operator=(const BinarySearchTree &T);

		bool isEmpty();
		void insert(int key);
		void insert1(int key);
		void display();
		void del(int key);
		void del1(int key);
		void del2(int key);
		bool search1(int key);
		bool search(int key);
		int min1();
		int max1();
		int min();
		int max();
};//End of class BinarySearchTree

BinarySearchTree::BinarySearchTree()
{
	root = NULL;
}//End of BinarySearchTree()

BinarySearchTree::~BinarySearchTree()
{
	destroy(root);
	root = NULL;
}//End of ~BinarySearchTree()

void BinarySearchTree::destroy(Node *ptr)
{
	if(ptr == NULL)
		return;
	destroy(ptr->lchild);
	destroy(ptr->rchild);

	delete ptr;
}//End of destroy()

BinarySearchTree::BinarySearchTree(const BinarySearchTree &T)
{
	root = copy(T.root);
}//End of BinarySearchTree()

Node* BinarySearchTree::copy(Node *ptr)
{
	if(ptr == NULL)
		return NULL;

	Node *cp = new Node(ptr->info);
	cp->lchild = copy(ptr->lchild);
	cp->rchild = copy(ptr->rchild);
	return cp;
}//End of copy()

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree &T)
{
	if(this == &T)
		return *this;

	destroy(root);
	root = copy(T.root);

	return *this;
}//End of operator=()

bool BinarySearchTree::isEmpty()
{
	return root==NULL;
}//End of isEmpty()

//Non Recursive insertion
void BinarySearchTree::insert1(int key)
{
	Node *parent = NULL;
	Node *ptr = root;

	while(ptr != NULL)
	{
		parent = ptr;

		if(key < ptr->info)
			ptr = ptr->lchild;
		else if(key > ptr->info)
			ptr = ptr->rchild;
		else
		{
			cout << key << " is already there\n";
			return;
		}
	}

	Node *temp = new Node(key);

	if(parent == NULL)
		root = temp;
	else if(key < parent->info)
		parent->lchild = temp;
	else
		parent->rchild = temp;
}//End of insert1()

//Recursive insertion
Node* BinarySearchTree::insert(Node *ptr, int key)
{
	if(ptr == NULL) //Base Case
		ptr = new Node(key);
	else if(key < ptr->info) //Insertion in left subtree
		ptr->lchild = insert(ptr->lchild, key);
	else if(key > ptr->info) //Insertion in right subtree
		ptr->rchild = insert(ptr->rchild, key);
	else	//Base Case
		cout << key << " is already there\n";

	return ptr;
}//End of insert()

void BinarySearchTree::insert(int key)
{
	root = insert(root, key);
}//End of insert()

void BinarySearchTree::caseA(Node *parent, Node *ptr)
{
	if(parent == NULL)	//root node to be deleted
		root = NULL;
	else if(ptr == parent->lchild)
		parent->lchild = NULL;
	else
		parent->rchild = NULL;

	delete ptr;
}//End of caseA()

void BinarySearchTree::caseB(Node *parent, Node *ptr)
{
	Node *child;

	//Initialize child
	if(ptr->lchild != NULL)	//node to be deleted has left child
		child = ptr->lchild;
	else					//node to be deleted has right child
		child = ptr->rchild;

	if(parent == NULL)		//node to be deleted is root node
		root = child;
	else if(ptr == parent->lchild)	//node is left child of its parent
		parent->lchild = child;
	else					//node is right child of its parent
		parent->rchild = child;

	delete ptr;
}//End of caseB()

void BinarySearchTree::caseC(Node *parent, Node *ptr)
{
	Node *s, *ps;

	//Find inorder successor and its parent
	ps = ptr;
	s = ptr->rchild;
	while(s->lchild != NULL)
	{
		ps = s;
		s = s->lchild;
	}
	ptr->info = s->info;
	if(s->lchild==NULL && s->rchild==NULL)
		caseA(ps, s);
	else
		caseB(ps, s);
}//End of caseC()

//Non Recursive deletion
void BinarySearchTree::del2(int key)
{
	Node *parent = NULL;
	Node *ptr = root;

	while(ptr != NULL)
	{
		if(ptr->info == key)
			break;

		parent = ptr;
		if(key < ptr->info)
			ptr = ptr->lchild;
		else
			ptr = ptr->rchild;
	}

	if(ptr == NULL)
		cout << key << " is not in the tree\n";
	else if(ptr->lchild != NULL && ptr->rchild != NULL)	//2 children
		caseC(parent, ptr);
	else if(ptr->lchild != NULL)	//only left child
		caseB(parent, ptr);
	else if(ptr->rchild != NULL)	//only right child
		caseB(parent, ptr);
	else	//no child
		caseA(parent, ptr);

}//End of del2()

//Non Recursive deletion
void BinarySearchTree::del1(int key)
{
	Node *parent = NULL;
	Node *ptr = root;

	while(ptr != NULL)
	{
		if(ptr->info == key)
			break;

		parent = ptr;
		if(key < ptr->info)
			ptr = ptr->lchild;
		else
			ptr = ptr->rchild;
	}

	if(ptr == NULL)
	{
		cout << key << " is not in the tree\n";
		return;
	}

	//Case C : 2 children
	//Find inorder successor and parent
	Node *s, *ps;
	if(ptr->lchild!=NULL && ptr->rchild!=NULL)
	{
		ps = ptr;
		s = ptr->rchild;

		while(s->lchild != NULL)
		{
			ps = s;
			s = s->lchild;
		}
		ptr->info = s->info;
		ptr = s;
		parent = ps;
	}

	//Case B and Case A : 1 or no child
	Node *child;
	if(ptr->lchild != NULL)	//Node to be deleted has left child
		child = ptr->lchild;
	else	//Node to be deleted has right child or no child
		child = ptr->rchild;

	if(parent == NULL)	//Node to be deleted is root node
		root = child;
	else if(ptr == parent->lchild)	//Node is left child of its parent
		parent->lchild = child;
	else	//Node is right child of its parent
		parent->rchild = child;

	delete ptr;
}//End of del1()

//Recursive deletion
Node* BinarySearchTree::del(Node *ptr, int key)
{
	Node *child, *s, *temp;

	if(ptr == NULL)
	{
		cout << key << " not found\n";
		return ptr;
	}

	if(key < ptr->info)	//Delete from left subtree
		ptr->lchild = del(ptr->lchild, key);
	else if(key > ptr->info)	//Delete from right subtree
		ptr->rchild = del(ptr->rchild, key);
	else
	{
		//Key to be deleted is found
		if(ptr->lchild!=NULL && ptr->rchild!=NULL)	//2 children
		{
			s = ptr->rchild;
			while(s->lchild != NULL)
				s = s->lchild;
			ptr->info = s->info;
			ptr->rchild = del(ptr->rchild, s->info);
		}
		else	//1 child or no child
		{
			if(ptr->lchild != NULL)	//Only left child
				child = ptr->lchild;
			else	//Only right child or no child
				child = ptr->rchild;
			temp = ptr;
			ptr = child;
			delete temp;
		}
	}//End of else

	return ptr;
}//End of del()

void BinarySearchTree::del(int key)
{
	root = del(root, key);
}//End of del()

void BinarySearchTree::display(Node *ptr, int level)
{
	if(ptr == NULL)
		return;

	display(ptr->rchild, level+1);
	cout << "\n";

	for(int i=0; i<level; i++)
		cout << "    ";
	cout << ptr->info;

	display(ptr->lchild, level+1);
}//End of display()

void BinarySearchTree::display()
{
	display(root, 0);
}//End of display()

//Non Recursive search
bool BinarySearchTree::search1(int key)
{
	Node *ptr = root;

	while(ptr != NULL)
	{
		if(key < ptr->info)
			ptr = ptr->lchild;	//Move to left child
		else if(key > ptr->info)
			ptr = ptr->rchild;	//Move to right child
		else	//key found
			return true;
	}

	return false;
}//End of search1()

//Recursive search
Node* BinarySearchTree::search(Node *ptr, int key)
{
	if(ptr == NULL)
		return NULL;	//key not found
	if(key < ptr->info)
		return search(ptr->lchild, key);	//search in left subtree
	if(key > ptr->info)
		return search(ptr->rchild, key);	//search in right subtree
	return ptr;	//key found
}//End of search()

bool BinarySearchTree::search(int key)
{
	return search(root, key) != NULL;
}//End of search()

//Non Recursive to find minimum key
int BinarySearchTree::min1()
{
	if(isEmpty())
		throw exception("Tree is empty");

	Node *ptr = root;
	while(ptr->lchild != NULL)
		ptr = ptr->lchild;

	return ptr->info;
}//End of min1()

//Non Recursive to find maximum key
int BinarySearchTree::max1()
{
	if(isEmpty())
		throw exception("Tree is empty");

	Node *ptr = root;
	while(ptr->rchild != NULL)
		ptr = ptr->rchild;

	return ptr->info;
}//End of max1()

//Recursive to find minimum key
Node* BinarySearchTree::min(Node *ptr)
{
	if(ptr->lchild == NULL)
		return ptr;
	return min(ptr->lchild);
}//End of min()

int BinarySearchTree::min()
{
	if(isEmpty())
		throw exception("Tree is empty");

	return min(root)->info;
}//End of min()

//Recursive to find maximum key
Node* BinarySearchTree::max(Node *ptr)
{
	if(ptr->rchild == NULL)
		return ptr;
	return max(ptr->rchild);
}//End of max()

int BinarySearchTree::max()
{
	if(isEmpty())
		throw exception("Tree is empty");

	return max(root)->info;
}//End of max()

int main()
{
	BinarySearchTree bst;

	try
	{
		cout << "Insertion to create the BST :\n";
		bst.insert1(80);
		bst.insert1(70);
		bst.insert1(65);
		bst.insert1(75);
		bst.insert1(90);
		bst.insert1(85);
		bst.insert1(95);
		bst.display();
		cout << "\n";
		cout << "After deleting 95 :\n";
		bst.del(95);
		bst.display();
		cout << "\n";

		cout << "Copy constructor :\n";
		BinarySearchTree bst1(bst);
		bst1.display();
		cout << "\n";

		cout << "Overloading assignment operator :\n";
		BinarySearchTree bst2;
		bst2 = bst;
		bst2.display();
		cout << "\n";

		//Search (Iterative) in BST
		cout << "search1(75) : " << (bst.search1(75) ? "True" : "False");
		cout << "\n";

		//Search (Recursive) in BST
		cout << "search(75) : " << (bst.search(75) ? "True" : "False");
		cout << "\n";

		cout << "Min key (Iterative) = " << bst.min1() << "\n";
		cout << "Min key (Recursive) = " << bst.min() << "\n";

		cout << "Max key (Iterative) = " << bst.max1() << "\n";
		cout << "Max key (Recursive) = " << bst.max() << "\n";

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}//End of main()

