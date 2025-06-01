//BinaryTree.cpp : Program for Binary Tree.

#include<iostream>
#include<stack>
#include<queue>
using namespace std;

class Node
{
	public:
		char info;

		Node *lchild;
		Node *rchild;

		Node(char data)
		{
			info = data;
			lchild = NULL;
			rchild = NULL;
		}
};//End of class Node

class BinaryTree
{
	private:
		Node *root;

		void preorder(Node *ptr);
		void inorder(Node *ptr);
		void postorder(Node *ptr);
		int height(Node *ptr);
		void display(Node *ptr, int level);
		Node* construct(char *in, char *pre, int num);
		Node* construct1(char *in, char *post, int num);

	public:
		BinaryTree();
		~BinaryTree(){};
		bool isEmpty();
		void createTree();
		void preorder();
		void inorder();
		void postorder();
		void levelOrder();
		int height();
		void nrecPreorder();
		void nrecInorder();
		void nrecPostorder();
		void construct(char *in, char *pre);
		void construct1(char *in, char *post);
		void display();
};//End of class BinaryTree

BinaryTree::BinaryTree()
{
	root = NULL;
}//End of BinaryTree()

bool BinaryTree::isEmpty()
{
	return root==NULL;
}//End of isEmpty()

void BinaryTree::createTree()
{
	root = new Node('P');
	root->lchild = new Node('Q');
	root->rchild = new Node('R');

	root->lchild->lchild = new Node('A');
	root->lchild->rchild = new Node('B');

	root->rchild->lchild = new Node('X');
}//End of createTree()

void BinaryTree::preorder(Node *ptr)
{
	if(ptr == NULL)	//Base case
		return;

	cout << ptr->info << " ";
	preorder(ptr->lchild);
	preorder(ptr->rchild);
}//End of preorder()

void BinaryTree::preorder()
{
	preorder(root);
	cout << "\n";
}//End of preorder()

void BinaryTree::inorder(Node *ptr)
{
	if(ptr == NULL)	//Base case
		return;

	inorder(ptr->lchild);
	cout << ptr->info << " ";
	inorder(ptr->rchild);
}//End of inorder()

void BinaryTree::inorder()
{
	inorder(root);
	cout << "\n";
}//End of inorder()

void BinaryTree::postorder(Node *ptr)
{
	if(ptr == NULL)	//Base case
		return;

	postorder(ptr->lchild);
	postorder(ptr->rchild);
	cout << ptr->info << " ";
}//End of postorder()

void BinaryTree::postorder()
{
	postorder(root);
	cout << "\n";
}//End of postorder()

void BinaryTree::levelOrder()
{
	queue<Node *> qu;
	Node *ptr;

	qu.push(root);
	while(!qu.empty())
	{
		ptr = qu.front();
		qu.pop();
		cout << ptr->info << " ";

		if(ptr->lchild != NULL)
			qu.push(ptr->lchild);

		if(ptr->rchild != NULL)
			qu.push(ptr->rchild);
	}
	cout << "\n";
}//End of levelOrder()

int BinaryTree::height(Node *ptr)
{
	int hLeft, hRight;

	if(ptr == NULL)	//Base case
		return 0;

	hLeft = height(ptr->lchild);
	hRight = height(ptr->rchild);

	if(hLeft > hRight)
		return 1+hLeft;
	else
		return 1+hRight;
}//End of height()

int BinaryTree::height()
{
	return height(root);
}//End of height()

//Non recursive Preorder traversal
void BinaryTree::nrecPreorder()
{
	stack<Node *> st;
	Node *ptr = root;

	if(ptr != NULL)
	{
		st.push(ptr);
		while(!st.empty())
		{
			ptr = st.top();
			st.pop();
			cout << ptr->info << " ";
			if(ptr->rchild != NULL)
				st.push(ptr->rchild);
			if(ptr->lchild != NULL)
				st.push(ptr->lchild);
		}
		cout << "\n";
	}
	else
	{
		cout << "Tree is empty\n";
	}
}//End of nrecPreorder()

//Non recursive Inorder traversal
void BinaryTree::nrecInorder()
{
	stack<Node *> st;
	Node *ptr = root;

	if(ptr != NULL)
	{
		while(true)
		{
			while(ptr->lchild != NULL)
			{
				st.push(ptr);
				ptr = ptr->lchild;
			}

			while(ptr->rchild == NULL)
			{
				cout << ptr->info << " ";
				if(st.empty())
				{
					cout << "\n";
					return;
				}
				ptr = st.top();
				st.pop();
			}
			cout << ptr->info << " ";
			ptr = ptr->rchild;
		}
	}
	else
	{
		cout << "Tree is empty\n";
	}
}//End of nrecInorder()

//Non recursive Postorder traversal
void BinaryTree::nrecPostorder()
{
	stack<Node *> st;
	Node *ptr = root;
	Node *visited = root;

	if(ptr != NULL)
	{
		while(true)
		{
			while(ptr->lchild != NULL)
			{
				st.push(ptr);
				ptr = ptr->lchild;
			}

			while(ptr->rchild==NULL || ptr->rchild==visited)
			{
				cout << ptr->info << " ";
				visited = ptr;
				if(st.empty())
				{
					cout << "\n";
					return;
				}
				ptr = st.top();
				st.pop();
			}
			st.push(ptr);
			ptr = ptr->rchild;
		}
	}
	else
	{
		cout << "Tree is empty\n";
	}
}//End of nrecPostorder()

void BinaryTree::display(Node *ptr, int level)
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

void BinaryTree::display()
{
	display(root, 0);
	cout << "\n";
}//End of display()

//Creation of binary tree from inorder and preorder traversal
Node* BinaryTree::construct(char *in, char *pre, int num)
{
	Node *temp;
	char *q;
	
	if(num == 0)
		return NULL;

	temp = new Node(pre[0]);

	if(num == 1)	//if only one node in tree
		return temp;

	q = in;
	int i;
	for(i=0; q[0]!=pre[0]; i++)
		q++;

	//Now q points to root in inorder list and number of nodes in its left subtree is i
	//For left subtree
	temp->lchild = construct(in, pre+1, i);

	//For right subtree
	int j;
	for(j=1; j<=i+1; j++)
		pre++;
	temp->rchild = construct(q+1, pre, num-i-1);

	return temp;
}//End of construct()

void BinaryTree::construct(char *in, char *pre)
{
	root = construct(in, pre, strlen(in));
}//End of construct()

//Creation of binary tree from inorder and postorder traversal
Node* BinaryTree::construct1(char *in, char *post, int num)
{
	Node *temp;
	char *q, *ptr;

	int i, j;

	if(num == 0)
		return NULL;

	ptr = post;
	for(i=1; i<num; i++)
		ptr++;

	//Now ptr points to last node of postorder which is root
	temp = new Node(ptr[0]);

	if(num == 1)	//if only one node in tree
		return temp;

	q = in;
	for(i=0; q[0]!=ptr[0]; i++)
		q++;

	//Now i denotes the number of nodes in left subtree
	//and q points to root node in inorder list
	//For left subtree
	temp->lchild = construct1(in, post, i);

	//For right subtree
	for(j=1; j<=i; j++)
		post++;

	temp->rchild = construct1(q+1, post, num-i-1);

	return temp;
}//End of construct1()

void BinaryTree::construct1(char *in, char *post)
{
	root = construct1(in, post, strlen(in));
}//End of construct1()

int main()
{
	BinaryTree bnTree;

	bnTree.createTree();
	bnTree.display();
	cout << "\n";

	cout << "Preorder traversal :\n";
	bnTree.preorder();

	cout << "Inorder traversal :\n";
	bnTree.inorder();

	cout << "Postorder traversal :\n";
	bnTree.postorder();

	cout << "Level order traversal :\n";
	bnTree.levelOrder();

	cout << "Height = " << bnTree.height() << "\n";

	cout << "Non Recursive Preorder traversal :\n";
	bnTree.nrecPreorder();

	cout << "Non Recursive Inorder traversal :\n";
	bnTree.nrecInorder();

	cout << "Non Recursive Postorder traversal :\n";
	bnTree.nrecPostorder();

	char inorder[] = "GDHBEIACJFK";

	char preorder[] = "ABDGHEICFJK";
	BinaryTree bnTree1;
	cout << "Creation of binary tree from Inorder = " << inorder << ", Preorder = " << preorder << " :\n";
	bnTree1.construct(inorder, preorder);
	bnTree1.display();
	cout << "\n";

	char postorder[] = "GHDIEBJKFCA";
	BinaryTree bnTree2;
	cout << "Creation of binary tree from Inorder = " << inorder << ", Postorder = " << postorder << " :\n";
	bnTree2.construct1(inorder, postorder);
	bnTree2.display();
	cout << "\n";

	return 0;

}//End of main()


