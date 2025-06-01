//ExpressionTree.cpp : Program for Expression Tree.

#include<iostream>
#include<string>
#include<stack>
using namespace std;

class Node
{
	public:
		char info;
		Node *lchild;
		Node *rchild;

		Node(char ch)
		{
			info = ch;
			lchild = NULL;
			rchild = NULL;
		}

};//End of class Node

class ExpressionTree
{
	private:
		Node *root;
		bool isOperator(char ch);
		void preorder(Node *ptr);
		void postorder(Node *ptr);
		void inorder(Node *ptr);
		void display(Node *ptr, int level);
		int evaluate(Node *ptr);
		void destroy(Node *ptr);

	public:
		ExpressionTree();
		~ExpressionTree();
		void buildTree(string postfix);
		void prefix();
		void postfix();
		void parenthesizedInfix();
		void display();
		int evaluate();

};//End of class ExpressionTree

ExpressionTree::ExpressionTree()
{
	root = NULL;
}//End of ExpressionTree()

ExpressionTree::~ExpressionTree()
{
	destroy(root);
	root = NULL;
}//End of ExpressionTree()

void ExpressionTree::destroy(Node *ptr)
{
	if(ptr == NULL)
		return;
	destroy(ptr->lchild);
	destroy(ptr->rchild);

	delete ptr;
}//End of destroy()

bool ExpressionTree::isOperator(char c)
{
	if(c=='+' || c=='-' || c=='*' || c=='/')
		return true;
	return false;
}//End of isOperator();

void ExpressionTree::buildTree(string postfix)
{
	stack<Node *> treeStack;
	Node *t;

	for(int i=0; i<postfix.length(); i++)
	{
		if(isOperator(postfix[i]))
		{
			t = new Node(postfix[i]);
			t->rchild = treeStack.top();
			treeStack.pop();
			t->lchild = treeStack.top();
			treeStack.pop();
			treeStack.push(t);
		}
		else	//operand
		{
			t = new Node(postfix[i]);
			treeStack.push(t);
		}
	}

	root = treeStack.top();
	treeStack.pop();

}//End of buildTree()

void ExpressionTree::preorder(Node *ptr)
{
	if(ptr == NULL)	//Base case
		return;

	cout << ptr->info;
	preorder(ptr->lchild);
	preorder(ptr->rchild);
}//End of preorder()

void ExpressionTree::prefix()
{
	preorder(root);
	cout << "\n";
}//End of prefix()

void ExpressionTree::postorder(Node *ptr)
{
	if(ptr == NULL)	//Base case
		return;

	postorder(ptr->lchild);
	postorder(ptr->rchild);
	cout << ptr->info;
}//End of postorder()

void ExpressionTree::postfix()
{
	postorder(root);
	cout << "\n";
}//End of postfix()

void ExpressionTree::inorder(Node *ptr)
{
	if(ptr == NULL)	//Base case
		return;

	if(isOperator(ptr->info))
		cout << "(";

	inorder(ptr->lchild);
	cout << ptr->info;
	inorder(ptr->rchild);

	if(isOperator(ptr->info))
		cout << ")";

}//End of inorder()

void ExpressionTree::parenthesizedInfix()
{
	inorder(root);
	cout << "\n";
}//End of parenthesizedInfix()

void ExpressionTree::display(Node *ptr, int level)
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

void ExpressionTree::display()
{
	display(root, 0);
	cout << "\n";
}//End of display()

int ExpressionTree::evaluate(Node *ptr)
{
	if(!isOperator(ptr->info))
		return ptr->info - 48;

	int leftValue = evaluate(ptr->lchild);
	int rightValue = evaluate(ptr->rchild);

	if(ptr->info == '+')
		return leftValue + rightValue;
	else if(ptr->info == '-')
		return leftValue - rightValue;
	else if(ptr->info == '*')
		return leftValue * rightValue;
	else if(ptr->info == '/')
		return leftValue / rightValue;

}//End of evaluate()

int ExpressionTree::evaluate()
{
	if(root == NULL)
		return 0;

	return evaluate(root);
}//End of evaluate()

int main()
{
	ExpressionTree expTree;

	string postfix = "54+12*3*-";

	expTree.buildTree(postfix);
	expTree.display();

	cout << "Prefix : ";
	expTree.prefix();

	cout << "Postfix : ";
	expTree.postfix();

	cout << "Infix : ";
	expTree.parenthesizedInfix();

	cout << "Evaluated Value : " << expTree.evaluate() << "\n";

	return 0;
}//End of main()

