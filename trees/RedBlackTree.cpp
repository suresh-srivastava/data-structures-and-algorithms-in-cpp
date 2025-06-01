//RedBlackTree.cpp : Program for Red Black Tree.

#include<iostream>

using namespace std;

class Node
{
	public:
		enum {black, red} color;
		int info;
		Node *lchild;
		Node *rchild;
		Node *parent;

		Node(int key)
		{
			info = key;
			lchild = NULL;
			rchild = NULL;
			parent = NULL;
		}
};//End of class Node

class RedBlackTree
{
	private:
		Node *root;
		Node *sentinel;	//will be parent of root and replace NULL

		bool find(int key, Node **location);
		void insertionBalance(Node *n);
		void deletionBalance(Node *n);

		void rotateRight(Node *p);
		void rotateLeft(Node *p);
		Node* getSuccessor(Node *location);

		void inorder(Node *ptr);
		void display(Node *ptr, int level);

	public:
		RedBlackTree();
		~RedBlackTree(){};
		void insert(int key);
		void del(int key);
		void inorder();
		void display();

};//End of class RedBlackTree

RedBlackTree::RedBlackTree()
{
	sentinel = new Node(-1);
	sentinel->color = Node::black;
	root = sentinel;
}//End of RedBlackTree()

bool RedBlackTree::find(int key, Node **location)
{
	Node *ptr;

	if(root == sentinel)	//Tree is empty
	{
		*location = sentinel;
		return false;
	}

	if(key == root->info)	//key is at root
	{
		*location = root;
		return true;
	}

	//Initialize ptr
	if(key < root->info)
		ptr = root->lchild;
	else
		ptr = root->rchild;

	while(ptr != sentinel)
	{
		if(key == ptr->info)
		{
			*location = ptr;
			return true;
		}

		if(key < ptr->info)
			ptr = ptr->lchild;
		else
			ptr = ptr->rchild;
	}//End of while

	*location = sentinel;	//key not found
	return false;
}//End of find()

void RedBlackTree::insert(int key)
{
	Node *parent = sentinel;
	Node *ptr = root;

	while(ptr != sentinel)
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
	temp->lchild = sentinel;
	temp->rchild = sentinel;
	temp->color = Node::red;
	temp->parent = parent;

	if(parent == sentinel)
		root = temp;
	else if(temp->info < parent->info)
		parent->lchild = temp;
	else
		parent->rchild = temp;

	insertionBalance(temp);

}//End of insert()

void RedBlackTree::insertionBalance(Node *n)
{
	Node *uncle, *parent, *grandParent;

	while(n->parent->color == Node::red)
	{
		parent = n->parent;
		grandParent = parent->parent;

		if(parent == grandParent->lchild)
		{
			uncle = grandParent->rchild;
			if(uncle->color == Node::red)	//Case L_1
			{
				parent->color = Node::black;
				uncle->color = Node::black;
				grandParent->color = Node::red;
				n = grandParent;
			}
			else	//uncle is black
			{
				if(n == parent->rchild)		//Case L_2a
				{
					rotateLeft(parent);
					n = parent;
					parent = n->parent;
				}
				parent->color = Node::black;	//Case L_2b
				grandParent->color = Node::red;
				rotateRight(grandParent);
			}
		}//End of if
		else
		{
			if(parent == grandParent->rchild)
			{
				uncle = grandParent->lchild;
				if(uncle->color == Node::red)	//Case R_1
				{
					parent->color = Node::black;
					uncle->color = Node::black;
					grandParent->color = Node::red;
					n = grandParent;
				}
				else	//uncle is black
				{
					if(n == parent->lchild)	//Case R_2a
					{
						rotateRight(parent);
						n = parent;
						parent = n->parent;
					}
					parent->color = Node::black;	//Case R_2b
					grandParent->color = Node::red;
					rotateLeft(grandParent);
				}

			}//End of if

		}//End of else

	}//End of while

	root->color = Node::black;

}//End of insertBalance()


Node* RedBlackTree::getSuccessor(Node *location)
{
	Node *ptr = location->rchild;
	while(ptr->lchild != sentinel)
		ptr = ptr->lchild;
	
	return ptr;
}//End of getSuccessor()


void RedBlackTree::del(int key)
{
	Node *ptr;

	if(!find(key, &ptr))
	{
		cout << "Key not present\n";
		return;
	}

	if(ptr->lchild!=sentinel && ptr->rchild!=sentinel)
	{
		Node *succ = getSuccessor(ptr);
		ptr->info = succ->info;
		ptr = succ;
	}

	Node *child;

	if(ptr->lchild != sentinel)
		child = ptr->lchild;
	else
		child = ptr->rchild;

	child->parent = ptr->parent;

	if(ptr->parent == sentinel)
		root = child;
	else if(ptr == ptr->parent->lchild)
		ptr->parent->lchild = child;
	else
		ptr->parent->rchild = child;

	if(child == root)
		child->color = Node::black;
	else if(ptr->color == Node::black)	//black node
	{
		if(child != sentinel)	//one child which is red
			child->color = Node::black;
		else	//no child
			deletionBalance(child);
	}

	delete ptr;

}//End of del()

void RedBlackTree::deletionBalance(Node *n)
{
	Node *sib;

	while(n != root)
	{
		if(n == n->parent->lchild)
		{
			sib = n->parent->rchild;

			if(sib->color == Node::red)		//Case L_1
			{
				sib->color = Node::black;
				n->parent->color = Node::red;
				rotateLeft(n->parent);
				sib = n->parent->rchild;	//new sibling
			}

			if(sib->lchild->color==Node::black && sib->rchild->color==Node::black)
			{
				sib->color = Node::red;
				if(n->parent->color == Node::red)	//Case L_2a
				{
					n->parent->color = Node::black;
					return;
				}
				else
					n = n->parent;	//Case L_2b
			}
			else
			{
				if(sib->rchild->color == Node::black)	//Case L_3a
				{
					sib->lchild->color = Node::black;
					sib->color = Node::red;
					rotateRight(sib);
					sib = n->parent->rchild;
				}
				sib->color = n->parent->color;	//Case L_3b
				n->parent->color = Node::black;
				sib->rchild->color = Node::black;
				rotateLeft(n->parent);
				return;
			}

		}//End of if
		else
		{
			sib = n->parent->lchild;
			if(sib->color == Node::red)		//Case R_1
			{
				sib->color = Node::black;
				n->parent->color = Node::red;
				rotateRight(n->parent);
				sib = n->parent->lchild;
			}

			if(sib->rchild->color==Node::black && sib->lchild->color==Node::black)
			{
				sib->color = Node::red;
				if(n->parent->color == Node::red)	//Case R_2a
				{
					n->parent->color = Node::black;
					return;
				}
				else
					n = n->parent;	//Case R_2b
			}
			else
			{
				if(sib->lchild->color == Node::black)	//Case R_3a
				{
					sib->rchild->color = Node::black;
					sib->color = Node::red;
					rotateLeft(sib);
					sib = n->parent->lchild;
				}
				
				sib->color = n->parent->color;	//Case R_3b
				n->parent->color = Node::black;
				sib->lchild->color = Node::black;
				rotateRight(n->parent);
				return;
			}

		}//End of else

	}//End of while

}//End of deletionBalance()

void RedBlackTree::rotateRight(Node *p)
{
	Node *a;

	a = p->lchild;			//A is left child of P
	p->lchild = a->rchild;	//Right child of A becomes left child of P

	if(a->rchild != sentinel)
		a->rchild->parent = p;
	a->parent = p->parent;

	if(p->parent == sentinel)
		root = a;
	else if(p == p->parent->rchild)
		p->parent->rchild = a;
	else
		p->parent->lchild = a;

	a->rchild = p;			//P becomes right child of A
	p->parent = a;
}//End of rotateRight()

void RedBlackTree::rotateLeft(Node *p)
{
	Node *a;

	a = p->rchild;			//A is right child of P
	p->rchild = a->lchild;	//Left child of A becomes right child of P

	if(a->lchild != sentinel)
		a->lchild->parent = p;
	a->parent = p->parent;

	if(p->parent == sentinel)
		root = a;
	else if(p == p->parent->lchild)
		p->parent->lchild = a;
	else
		p->parent->rchild = a;

	a->lchild = p;			//P becomes left child of A
	p->parent = a;
}//End of rotateLeft()

void RedBlackTree::inorder(Node *ptr)
{
	if(ptr != sentinel)
	{
		inorder(ptr->lchild);
		cout << ptr->info;
		inorder(ptr->rchild);
	}
}//End of inorder()

void RedBlackTree::inorder()
{
	inorder(root);
}//End of inorder()

void RedBlackTree::display(Node *ptr, int level)
{
	if(ptr != sentinel)
	{
		display(ptr->rchild, level+1);
		cout << "\n";
		
		for(int i=0; i<level; i++)
			cout << "    ";
		cout << ptr->info;
		if(ptr->color == Node::red)
			cout << "^";
		else
			cout << "*";
		
		display(ptr->lchild, level+1);
	}
}//End of display()

void RedBlackTree::display()
{
	display(root, 1);
}//End of display()

int main()
{
	RedBlackTree rbTree;

	cout << "Tree after inserting 50\n";
	rbTree.insert(50);
	rbTree.display();
	cout << "\n";

	cout << "Tree after inserting 60\n";
	rbTree.insert(60);
	rbTree.display();
	cout << "\n";

	cout << "Tree after inserting 70\n";
	rbTree.insert(70);
	rbTree.display();
	cout << "\n";

	rbTree.insert(40);
	cout << "Tree after inserting 40\n";
	rbTree.display();
	cout << "\n";

	cout << "Tree after inserting 55\n";
	rbTree.insert(55);
	rbTree.display();
	cout << "\n";

	cout << "Tree after inserting 75\n";
	rbTree.insert(75);
	rbTree.display();
	cout << "\n";

	cout << "Tree after inserting 53\n";
	rbTree.insert(53);
	rbTree.display();
	cout << "\n";

	cout << "Tree after inserting 54\n";
	rbTree.insert(54);
	rbTree.display();
	cout << "\n";

	cout << "Tree after inserting 30\n";
	rbTree.insert(30);
	rbTree.display();
	cout << "\n";

	cout << "Tree after inserting 45\n";
	rbTree.insert(45);
	rbTree.display();
	cout << "\n";

	cout << "Tree after inserting 35\n";
	rbTree.insert(35);
	rbTree.display();
	cout << "\n";

	cout << "Tree after inserting 51\n";
	rbTree.insert(51);
	rbTree.display();
	cout << "\n";

	cout << "Tree after deleting 55\n";
	rbTree.del(55);
	rbTree.display();
	cout << "\n";

	cout << "Tree after deleting 50\n";
	rbTree.del(50);
	rbTree.display();
	cout << "\n";

	cout << "Tree after deleting 75\n";
	rbTree.del(75);
	rbTree.display();
	cout << "\n";

	cout << "Tree after deleting 45\n";
	rbTree.del(45);
	rbTree.display();
	cout << "\n";

	return 0;
}//End of main()

