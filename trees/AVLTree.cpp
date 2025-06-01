//AVLTree.cpp : Program for AVL Tree.

#include<iostream>

using namespace std;

class Node
{
	public:
		int info;
		int balance;
		Node *lchild;
		Node *rchild;

		Node(int key)
		{
			info = key;
			balance = 0;
			lchild = NULL;
			rchild = NULL;
		}

};//End of class Node

class AVLTree
{
	private:
		Node *root;
		bool taller;
		bool shorter;

		void display(Node *ptr, int level);
		void inorder(Node *ptr);
		Node* insert(Node *ptr, int key);
		void destroy(Node *ptr);

		Node* insertionLeftSubtreeCheck(Node *p);
		Node* insertionRightSubtreeCheck(Node *p);
		Node* insertionLeftBalance(Node *p);
		Node* insertionRightBalance(Node *p);
		Node* rotateRight(Node *p);
		Node* rotateLeft(Node *p);
		Node* del(Node *ptr, int key);
		Node* deletionLeftSubtreeCheck(Node *p);
		Node* deletionRightSubtreeCheck(Node *p);
		Node* deletionRightBalance(Node *p);
		Node* deletionLeftBalance(Node *p);

	public:
		AVLTree();
		~AVLTree();
		bool isEmpty();
		void display();
		void inorder();
		void insert(int key);
		void del(int key);
};//End of class AVLTree

AVLTree::AVLTree()
{
	root = NULL;
}//End of AVLTree()

AVLTree::~AVLTree()
{
	destroy(root);
	root = NULL;
}//End of ~AVLTree()

void AVLTree::destroy(Node *ptr)
{
	if(ptr == NULL)
		return;
	destroy(ptr->lchild);
	destroy(ptr->rchild);

	delete ptr;
}//End of destroy()

bool AVLTree::isEmpty()
{
	return root==NULL;
}//End of isEmpty()

void AVLTree::display()
{
	display(root, 0);
	cout << "\n";
}//End of display()

void AVLTree::display(Node *ptr, int level)
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

void AVLTree::inorder()
{
	inorder(root);
	cout << "\n";
}//End of inorder()

void AVLTree::inorder(Node *ptr)
{
	if(ptr == NULL)	//Base Case
		return;

	inorder(ptr->lchild);
	cout << ptr->info << " ";
	inorder(ptr->rchild);
}//End of inorder()

void AVLTree::insert(int key)
{
	root = insert(root, key);
}//End of insert()

Node* AVLTree::insert(Node *ptr, int key)
{
	if(ptr == NULL)		//Base case
	{
		ptr = new Node(key);
		taller = true;
	}
	else if(key < ptr->info)		//Insertion in left subtree
	{
		ptr->lchild = insert(ptr->lchild, key);
		if(taller == true)
			ptr = insertionLeftSubtreeCheck(ptr);
	}
	else if(key > ptr->info)		//Insertion in right subtree
	{
		ptr->rchild = insert(ptr->rchild, key);
		if(taller == true)
			ptr = insertionRightSubtreeCheck(ptr);
	}
	else	//Base case
	{
		cout << key << " is already there\n";
		taller = false;
	}

	return ptr;
}//End of insert()

Node* AVLTree::insertionLeftSubtreeCheck(Node *p)
{
	switch(p->balance)
	{
		case 0:		//Case L_A : was balanced
			p->balance = 1;	//now left heavy
			break;
		case -1:	//Case L_B : was right heavy
			p->balance = 0;	//now balanced
			taller = false;
			break;
		case 1:		//Case L_C : was left heavy
			p = insertionLeftBalance(p);	//left balancing
			taller = false;
			break;
	}

	return p;
}//End of insertionLeftSubtreeCheck()

Node* AVLTree::insertionLeftBalance(Node *p)
{
	Node *a, *b;

	a = p->lchild;
	if(a->balance == 1)	//Case L_C1 : Insertion in AL
	{
		p->balance = 0;
		a->balance = 0;
		p = rotateRight(p);	
	}
	else	//Case L_C2 : Insertion in AR
	{
		b = a->rchild;
		switch(b->balance)
		{
			case -1:	//Case L_C2a : Insertion in BR
				p->balance = 0;
				a->balance = 1;
				break;
			case 1:		//Case L_C2b : Insertion in BL
				p->balance = -1;
				a->balance = 0;
				break;
			case 0:		//Case L_C2c : B is the newly inserted node
				p->balance = 0;
				a->balance = 0;
				break;
		}

		b->balance = 0;
		p->lchild = rotateLeft(a);
		p = rotateRight(p);
	}

	return p;
}//End of insertionLeftBalance()

Node* AVLTree::insertionRightSubtreeCheck(Node *p)
{
	switch(p->balance)
	{
		case 0:		//Case R_A : was balanced
			p->balance = -1;	//now right heavy
			break;
		case 1:		//Case R_B : was left heavy
			p->balance = 0;		//now balanced
			taller = false;
			break;
		case -1:	//Case R_C : was right heavy
			p = insertionRightBalance(p);	//right balancing
			taller = false;
			break;
	}

	return p;
}//End of insertionRightSubtreeCheck()

Node* AVLTree::insertionRightBalance(Node *p)
{
	Node *a, *b;

	a = p->rchild;
	if(a->balance == -1)	//Case R_C1 : Insertion in AR
	{
		p->balance = 0;
		a->balance = 0;
		p = rotateLeft(p);
	}
	else	//Case R_C2 : Insertion in AL
	{
		b = a->lchild;
		switch(b->balance)
		{
			case -1:	//Case R_C2a : Insertion in BR
				p->balance = 1;
				a->balance = 0;
				break;
			case 1:		//Case R_C2b : Insertion in BL
				p->balance = 0;
				a->balance = -1;
				break;
			case 0:		//Case R_C2c : B is the newly inserted node
				p->balance = 0;
				a->balance = 0;
				break;
		}
		b->balance = 0;
		p->rchild = rotateRight(a);
		p = rotateLeft(p);
	}

	return p;
}//End of insertionRightBalance()

Node* AVLTree::rotateRight(Node *p)
{
	Node *a;

	a = p->lchild;			//A is left child of P
	p->lchild = a->rchild;	//Right child of A becomes left child of P	
	a->rchild = p;			//P becomes right child of A
	return a;				//A is the new root of the subtree initially rooted at P
}//End of rotateRight()

Node* AVLTree::rotateLeft(Node *p)
{
	Node *a;

	a = p->rchild;			//A is right child of P
	p->rchild = a->lchild;	//Left child of A becomes right child of P
	a->lchild = p;			//P becomes left child of A
	return a;				//A is the new root of the subtree initially rooted at P
}//End of rotateLeft()

void AVLTree::del(int key)
{
	root = del(root, key);
}//End of del()

Node* AVLTree::del(Node *ptr, int key)
{
	Node *succ, *temp;

	if(ptr == NULL)		//Base case
	{
		cout << key << " not found\n";
		shorter = false;
		return ptr;
	}

	if(key < ptr->info)	//Delete from left subtree
	{
		ptr->lchild = del(ptr->lchild, key);
		if(shorter == true)
			ptr = deletionLeftSubtreeCheck(ptr);
	}
	else if(key > ptr->info)	//Delete from right subtree
	{
		ptr->rchild = del(ptr->rchild, key);
		if(shorter == true)
			ptr = deletionRightSubtreeCheck(ptr);
	}
	else	//key to be deleted is found, Base case
	{
		
		if(ptr->lchild!=NULL && ptr->rchild!=NULL)	//2 children
		{
			succ = ptr->rchild;
			while(succ->lchild != NULL)
				succ = succ->lchild;
			ptr->info = succ->info;
			ptr->rchild = del(ptr->rchild, succ->info);
			if(shorter == true)
				ptr = deletionRightSubtreeCheck(ptr);
		}
		else	//1 child or no child
		{
			temp = ptr;
			if(ptr->lchild != NULL)	//Only left child
				ptr = ptr->lchild;
			else	//Only right child or no child
				ptr = ptr->rchild;
			delete temp;
			shorter = true;
		}
	}

	return ptr;
}//End of del()

Node* AVLTree::deletionLeftSubtreeCheck(Node *p)
{
	switch(p->balance)
	{
		case 0:		//Case L_A : was balanced
			p->balance = -1;	//now right heavy
			shorter = false;
			break;
		case 1:		//Case L_B : was left heavy
			p->balance = 0;		//now balanced
			break;
		case -1:	//Case L_C : was right heavy
			p = deletionRightBalance(p);	//right balancing
			break;
	}

	return p;
}//End of deletionLeftSubtreeCheck()

Node* AVLTree::deletionRightBalance(Node *p)
{
	Node *a, *b;

	a = p->rchild;
	if(a->balance == 0)		//Case L_C1
	{
		a->balance = 1;
		shorter = false;
		p = rotateLeft(p);
	}
	else if(a->balance == -1)	//Case L_C2
	{
		p->balance = 0;
		a->balance = 0;
		p = rotateLeft(p);
	}
	else	//Case L_C3
	{
		b = a->lchild;
		switch(b->balance)
		{
			case 0:		//Case L_C3a
				p->balance = 0;
				a->balance = 0;
				break;
			case 1:		//Case L_C3b
				p->balance = 0;
				a->balance = -1;
				break;
			case -1:	//Case L_C3c
				p->balance = 1;
				a->balance = 0;
				break;
		}
		b->balance = 0;
		p->rchild = rotateRight(a);
		p = rotateLeft(p);
	}

	return p;
}//End of deletionRightBalance()

Node* AVLTree::deletionRightSubtreeCheck(Node *p)
{
	switch(p->balance)
	{
		case 0:		//Case R_A : was balanced
			p->balance = 1;		//now left heavy
			shorter = false;
			break;
		case -1:	//Case R_B : was right heavy
			p->balance = 0;		//now balanced
			break;
		case 1:		//Case R_C : was left heavy
			p = deletionLeftBalance(p);		//left balancing
			break;
	}

	return p;
}//End of deletionRightSubtreeCheck()

Node* AVLTree::deletionLeftBalance(Node *p)
{
	Node *a, *b;

	a = p->lchild;
	if(a->balance == 0)		//Case R_C1
	{
		a->balance = -1;
		shorter = false;
		p = rotateRight(p);
	}
	else if(a->balance == 1)	//Case R_C2
	{
		p->balance = 0;
		a->balance = 0;
		p = rotateRight(p);
	}
	else	//Case R_C3
	{
		b = a->rchild;
		switch(b->balance)
		{
			case 0:		//Case R_C3a
				p->balance = 0;
				a->balance = 0;
				break;
			case 1:		//Case R_C3b
				p->balance = -1;
				a->balance = 0;
				break;
			case -1:	//Case R_C3c
				p->balance = 0;
				a->balance = 1;
				break;
		}
		b->balance = 0;
		p->lchild = rotateLeft(a);
		p = rotateRight(p);
	}

	return p;
}//End of deletionLeftBalance()

int main()
{
	AVLTree avlTree;

	avlTree.insert(50);
	cout << "Tree after inserting 50\n";
	avlTree.display();
	cout << "\n";

	avlTree.insert(40);
	cout << "Tree after inserting 40\n";
	avlTree.display();
	cout << "\n";

	avlTree.insert(35);
	cout << "Tree after insertiing 35\n";
	avlTree.display();
	cout << "\n";

	avlTree.insert(58);
	cout << "Tree after inserting 58\n";
	avlTree.display();
	cout << "\n";

	avlTree.insert(48);
	cout << "Tree after inserting 48\n";
	avlTree.display();
	cout << "\n";

	avlTree.insert(42);
	cout << "Tree after inserting 42\n";
	avlTree.display();
	cout << "\n";

	avlTree.insert(60);
	cout << "Tree after inserting 60\n";
	avlTree.display();
	cout << "\n";

	avlTree.insert(30);
	cout << "Tree after inserting 30\n";
	avlTree.display();
	cout << "\n";

	avlTree.insert(33);
	cout << "Tree after inserting 33\n";
	avlTree.display();
	cout << "\n";

	avlTree.insert(25);
	cout << "Tree after inserting 25\n";
	avlTree.display();
	cout << "\n";

	avlTree.del(60);
	cout << "Tree after deleting 60\n";
	avlTree.display();
	cout << "\n";

	avlTree.del(48);
	cout << "Tree after deleting 48\n";
	avlTree.display();
	cout << "\n";

	avlTree.del(25);
	cout << "Tree after deleting 25\n";
	avlTree.display();
	cout << "\n";

	avlTree.del(30);
	cout << "Tree after deleting 30\n";
	avlTree.display();
	cout << "\n";

	avlTree.del(35);
	cout << "Tree after deleting 35\n";
	avlTree.display();
	cout << "\n";

	avlTree.del(33);
	cout << "Tree after deleting 33\n";
	avlTree.display();
	cout << "\n";

	avlTree.del(58);
	cout << "Tree after deleting 58\n";
	avlTree.display();
	cout << "\n";

	return 0;
}//End of main()

