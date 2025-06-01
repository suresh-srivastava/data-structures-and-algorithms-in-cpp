//Stack.cpp : Program to implement stack using array.

#include <iostream>
using namespace std;

static const int maxSize = 5;

class Stack
{
	private:
		int stackArray[maxSize];
		int top;

	public:
		Stack();
		bool isEmpty();
		bool isFull();
		void push(int data);
		int pop();
		int peek();
		void display();
		int size();
};//End of class Stack

Stack::Stack()
{ 
	top = -1;
}//End of Stack()

bool Stack::isEmpty()
{
	return (top == -1);
}//End of isEmpty()

bool Stack::isFull()
{
	return (top == maxSize-1);
}//End of isFull()

void Stack::push(int data)
{
	if(isFull())
		cout << "Stack Overflow\n";
	else
	{
		top++;
		stackArray[top] = data;
	}
}//End of push()

int Stack::pop()
{
	if(isEmpty())
		throw exception("Stack is empty");

	int retValue = stackArray[top];
	top = top-1;

	return retValue;
}//End of pop()

int Stack::peek()
{
	if(isEmpty())
		throw exception("Stack is empty");

	return stackArray[top];
}//End of peek()

int Stack::size()
{
	return (top+1);
}//End of size()

void Stack::display()
{
	if(isEmpty())
		cout << "Stack is empty\n";
	else
		for(int i=top; i>=0; i--)
			cout << stackArray[i] << "\n";
}//End of display()

int main()
{
	Stack st;

	try
	{
		st.push(1);
		st.push(2);
		st.push(3);
		st.push(4);

		cout << "Stack Items : \n";
		st.display();
		cout << "Top Item : " << st.peek() << "\n";
		cout << "Total items : " << st.size() << "\n";

		cout << "Popped Item : " << st.pop() << "\n";
		cout << "Stack Items : \n";
		st.display();

		st.push(4);
		st.push(5);

		cout << "Stack Items : \n";
		st.display();

		cout << "Popped Item : " << st.pop() << "\n";
		cout << "Popped Item : " << st.pop() << "\n";
		cout << "Popped Item : " << st.pop() << "\n";
		cout << "Popped Item : " << st.pop() << "\n";
		cout << "Popped Item : " << st.pop() << "\n";

		cout << "Stack Items : \n";
		st.display();

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}//End of main()

