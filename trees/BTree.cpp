//BTree.cpp : Program for B tree.

#include<iostream>

using namespace std;

static const int M = 5; //Order of B tree
static const int MAX = M-1; //Maximum number of permissible keys in a node
static const int MIN = (M%2==0)?((M/2)-1):(((M+1)/2)-1); //Minimum number of permissible keys in a node except root

class Node
{
	public:
		int key[MAX+1];
		Node *child[MAX+1];
		int numKeys;
	public:
		Node()
		{
			numKeys = 0;
		}
};//End of class Node

class BTree
{
	private:
		Node *root;

		void inorder(Node *ptr);
		void display(Node *ptr, int spaces);

		//Functions used in search
		Node* search(int key, Node *p);
		bool searchNode(int key, Node *p, int *n);

		//Functions used in insertion
		bool insert(int key, Node *p, int *iKey, Node **iKeyRchild);
		void insertByShift(Node *p, int n, int iKey, Node *iKeyRchild);
		void split(Node *p, int n, int *iKey, Node **iKeyRchild);

		//Functions used in deletion
		void del(int key, Node *p);
		void delByShift(Node *p, int n);
		void restore(Node *p, int n);
		void borrowLeft(Node *p, int n);
		void borrowRight(Node *p, int n);
		void combine(Node *p, int m);

	public:
		BTree();
		~BTree(){};
		void display();
		void inorder();
		bool search(int key);
		void insert(int key);
		void del(int key);
};//End of class BTree

BTree::BTree()
{
	root = NULL;
}//End of BTree()

void BTree::insert(int key)
{
	int iKey = 0;
	Node *iKeyRchild = NULL;

	bool taller = insert(key, root, &iKey, &iKeyRchild);

	if(taller)	//tree grown in height, new root is created
	{
		Node *temp = new Node();
		temp->child[0] = root;
		temp->key[1] = iKey;
		temp->child[1] = iKeyRchild;
		temp->numKeys = 1;
		root = temp;
	}
}//End of insert()

bool BTree::insert(int key, Node *p, int *iKey, Node **iKeyRchild)
{
	if(p == NULL)	//First Base case : key not found
	{
		*iKey = key;
		*iKeyRchild = NULL;
		return true;
	}

	int n=0;
	if(searchNode(key, p, &n) == true)	//Second Base case : key found
	{
		cout << "Key already present in the tree\n";
		return false;	//No need to insert the key
	}

	bool flag = insert(key, p->child[n], iKey, iKeyRchild);

	if (flag == true)
	{
		if(p->numKeys < MAX)
		{
			insertByShift(p, n, *iKey, *iKeyRchild);
			return false;	//Insertion over
		}
		else
		{
			split(p, n, iKey, iKeyRchild);
			return true;	//Insertion not over : Median key yet to be inserted
		}
	}

	return false;
}//End of insert()

bool BTree::search(int key)
{
	if(search(key,root) == NULL)
		return false;
	return true;
}//End of search()

Node* BTree::search(int key, Node *p)
{
	if(p == NULL)
		return NULL;	//Base case 1 : key is not present in the tree

	int n=0;
	if(searchNode(key, p, &n) == true)	//Base case 2 : key is found in node p
		return p;

	return search(key, p->child[n]);	//Recursive case : Search in node p->child[n]
}//End of search()

bool BTree::searchNode(int key, Node *p, int *n)
{
	if(key < p->key[1])		//key is less than leftmost key
	{
		*n = 0;
		return false;
	}

	*n = p->numKeys;
	while(key<p->key[*n] && *n>1)
		(*n)--;

	if(key == p->key[*n])
		return true;
	else
		return false;

}//End of searchNode()

void BTree::insertByShift(Node *p, int n, int iKey, Node *iKeyRchild)
{
	for(int i=p->numKeys; i>n; i--)
	{
		p->key[i+1] = p->key[i];
		p->child[i+1] = p->child[i];
	}
	p->key[n+1] = iKey;
	p->child[n+1] = iKeyRchild;
	p->numKeys++;
}//End of insertByShift()

void BTree::split(Node *p, int n, int *iKey, Node **iKeyRchild)
{
	int i, j;
	int lastKey;
	Node *lastChild;

	if(n == MAX)
	{
		lastKey = *iKey;
		lastChild = *iKeyRchild;
	}
	else
	{
		lastKey = p->key[MAX];
		lastChild = p->child[MAX];

		for(i=p->numKeys-1; i>n; i--)
		{
			p->key[i+1] = p->key[i];
			p->child[i+1] = p->child[i];
		}
		p->key[i+1] = *iKey;
		p->child[i+1] = *iKeyRchild;
	}

	int d = (M+1)/2;
	int medianKey = p->key[d];
	Node *newNode = new Node();

	for(i=1,j=d+1; j<=MAX; i++,j++)
	{
		newNode->key[i] = p->key[j];
		newNode->child[i] = p->child[j];
	}
	newNode->key[i] = lastKey;
	newNode->child[i] = lastChild;
	newNode->numKeys = M-d;	//Number of keys in the right splitted node

	newNode->child[0] = p->child[d];
	p->numKeys = d-1;	//Number of keys in the left splitted node

	*iKey = medianKey;
	*iKeyRchild = newNode;
}//End of split()

void BTree::del(int key)
{
	if(root != NULL)
	{
		del(key, root);

		//If tree becomes shorter, root is changed
		if(root!=NULL && root->numKeys==0)
		{
			Node *temp = root;
			root = root->child[0];
			delete temp;
		}
	}
	else
		cout << "Tree is empty\n";
}//End of del()

void BTree::del(int key, Node *p)
{
	int n;

	if(p == NULL)	//reached leaf node, key does not exist
	{
		cout << "Key " << key << "not found\n";
	}
	else
	{
		if(searchNode(key, p, &n))	//If found in current node p
		{
			if(p->child[n] == NULL)	//Node p is a leaf node
			{
				delByShift(p, n);
			}
			else	//Node p is a non leaf node
			{
				Node *succ = p->child[n]; //point to the right subtree
				while(succ->child[0] != NULL) //move down till leaf node arrives
					succ = succ->child[0];
				p->key[n] = succ->key[1];
				del(succ->key[1], p->child[n]);
			}
		}
		else	//Not found in current node p
		{
			del(key, p->child[n]);
		}


		if(p->child[n] != NULL)	//If p is not a leaf node
		{
			if(p->child[n]->numKeys < MIN)	//Check underflow in p->child[n]
				restore(p, n);
		}
	}
}//End of del()

void BTree::delByShift(Node *p, int n)
{
	for(int i=n+1; i<=p->numKeys; i++)
	{
		p->key[i-1] = p->key[i];
		p->child[i-1] = p->child[i];
	}
	p->numKeys--;
}//End of delByShift()

void BTree::restore(Node *p, int n)
{
	if(n!=0 && p->child[n-1]->numKeys > MIN)
		borrowLeft(p, n);
	else if(n!=p->numKeys && p->child[n+1]->numKeys > MIN)
		borrowRight(p, n);
	else
	{
		if(n==0)	//If underflow node is leftmost node
			combine(p, n+1);	//combine nth child of p with its right sibling
		else
			combine(p, n);		//combine nth child of p with its left sibling
	}
}//End of restore()

void BTree::borrowLeft(Node *p, int n)
{
	Node *u = p->child[n];		//underflow node
	Node *ls = p->child[n-1];	//left sibling of node u

	//Shift all the keys and children in underflow node u one position right
	for(int i=u->numKeys; i>0; i--)
	{
		u->key[i+1] = u->key[i];
		u->child[i+1] = u->child[i];
	}
	u->child[1] = u->child[0];

	//Move the separator key from parent node p to underflow node u
	u->key[1] = p->key[n];
	
	u->numKeys++;

	//Move the rightmost key of node ls to the parent node p
	p->key[n] = ls->key[ls->numKeys];
	
	//Rightmost child of ls becomes leftmost child of node u
	u->child[0] = ls->child[ls->numKeys];
	
	ls->numKeys--;
}//End of borrowLeft()

void BTree::borrowRight(Node *p, int n)
{
	Node *u = p->child[n];		//underflow node
	Node *rs = p->child[n+1];	//right sibling of node u

	//Move the separator key from the parent node p to the underflow node u
	u->numKeys++;
	u->key[u->numKeys] = p->key[n+1];

	//Leftmost child of node rs becomes the rightmost child of node u
	u->child[u->numKeys] = rs->child[0];

	//Move the leftmost key from node rs to parent node p
	p->key[n+1] = rs->key[1];
	rs->numKeys--;

	//Shift all the keys and children of node rs one position left
	rs->child[0] = rs->child[1];
	for(int i=1; i<=rs->numKeys; i++)
	{
		rs->key[i] = rs->key[i+1];
		rs->child[i] = rs->child[i+1];
	}
}//End of borrowRight()

void BTree::combine(Node *p, int m)
{
	Node *x = p->child[m];
	Node *y = p->child[m-1];

	//Move the separator key from parent node p to node y
	y->numKeys++;
	y->key[y->numKeys] = p->key[m];

	//Shift all the keys and children in node p one position left to fill the gap
	for(int i=m; i<p->numKeys; i++)
	{
		p->key[i] = p->key[i+1];
		p->child[i] = p->child[i+1];
	}
	p->numKeys--;

	//Leftmost child of x becomes rightmost child of y
	y->child[y->numKeys] = x->child[0];

	//Insert all the keys and children of node x at the end of node y
	for(int i=1; i<=x->numKeys; i++)
	{
		y->numKeys++;
		y->key[y->numKeys] = x->key[i];
		y->child[y->numKeys] = x->child[i];
	}

	delete x;
}//End of combine()

void BTree::inorder()
{
	inorder(root);
}//End of inorder()

void BTree::inorder(Node *ptr)
{
	if(ptr != NULL)
	{
		int i;
		for(i=0; i<ptr->numKeys; i++)
		{
			inorder(ptr->child[i]);
			cout << ptr->key[i+1] << " ";
		}
		inorder(ptr->child[i]);
	}
}//End of inorder()

void BTree::display()
{
	display(root, 0);
}//End of display()

void BTree::display(Node *p, int spaces)
{
	if(p != NULL)
	{
		int i;
		for(i=1; i<=spaces; i++)
			cout << " ";

		for(i=1; i<=p->numKeys; i++)
			cout << p->key[i] << " ";
		cout << "\n";

		for(i=0; i<=p->numKeys; i++)
			display(p->child[i], spaces+10);
	}
}//End of display()

int main()
{
	BTree btree;

	cout << "Tree after inserting 10\n";
	btree.insert(10);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 40\n";
	btree.insert(40);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 30\n";
	btree.insert(30);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 35\n";
	btree.insert(35);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 20\n";
	btree.insert(20);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 15\n";
	btree.insert(15);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 50\n";
	btree.insert(50);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 28\n";
	btree.insert(28);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 25\n";
	btree.insert(25);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 5\n";
	btree.insert(5);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 60\n";
	btree.insert(60);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 19\n";
	btree.insert(19);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 12\n";
	btree.insert(12);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 38\n";
	btree.insert(38);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 27\n";
	btree.insert(27);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 90\n";
	btree.insert(90);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 45\n";
	btree.insert(45);
	btree.display();
	cout << "\n";

	cout << "Tree after inserting 48\n";
	btree.insert(48);
	btree.display();
	cout << "\n";

	cout << "Tree after deleting 28\n";
	btree.del(28);
	btree.display();
	cout << "\n";

	cout << "Tree after deleting 40\n";
	btree.del(40);
	btree.display();
	cout << "\n";

	cout << "Tree after deleting 15\n";
	btree.del(15);
	btree.display();
	cout << "\n";

	//Search in B-tree
	cout << "search(48) : " << (btree.search(48) ? "True" : "False");
	cout << "\n";

	cout << "search(15) : " << (btree.search(15) ? "True" : "False");
	cout << "\n";

	return 0;
}//End of main()

