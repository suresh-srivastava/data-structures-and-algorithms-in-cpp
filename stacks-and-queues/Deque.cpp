//Deque.cpp : Program to implement deque using circular array.

#include <iostream>
using namespace std;

static const int maxSize = 5;

class Deque
{
	private:
		int queueArray[maxSize];
		int front;
		int rear;

	public:
		Deque();
		bool isEmpty();
		bool isFull();
		void insertFrontEnd(int data);
		void insertRearEnd(int data);
		int deleteFrontEnd();
		int deleteRearEnd();
		void display();
		int size();
};//End of class Deque

Deque::Deque()
{ 
	front = -1;
	rear = -1; 
}//End of Deque()

bool Deque::isEmpty()
{
	return (front == -1);
}//End of isEmpty()

bool Deque::isFull()
{
	return ((front==0 && rear==maxSize-1) || (front==rear+1));
}//End of isFull()

void Deque::insertFrontEnd(int data)
{
	if(isFull())
		cout << "Queue Overflow\n";
	else
	{
		if(front == -1) //If queue is initially empty
		{
			front = 0;
			rear = 0;
		}
		else if(front == 0)
			front = maxSize-1;
		else
			front = front-1;

		queueArray[front] = data;
	}
}//End of insertFrontEnd()

void Deque::insertRearEnd(int data)
{
	if(isFull())
		cout << "Queue Overflow\n";
	else
	{
		if(front == -1) //If queue is initially empty
		{
			front = 0;
			rear = 0;
		}
		else if(rear == maxSize-1) //rear is at last position of queue
			rear = 0;
		else
			rear = rear+1;

		queueArray[rear] = data;
	}
}//End of insertRearEnd()

int Deque::deleteFrontEnd()
{
	int retValue;

	if(isEmpty())
		throw exception("Queue is empty");
	else
	{
		retValue = queueArray[front];

		if(front == rear) //queue has only one element
		{
			front = -1;
			rear = -1;
		}
		else if(front == maxSize-1)
			front = 0;
		else
			front = front+1;
	}

	return retValue;
}//End of deleteFrontEnd()

int Deque::deleteRearEnd()
{
	int retValue;

	if(isEmpty())
		throw exception("Queue is empty");
	else
	{
		retValue = queueArray[rear];

		if(front == rear) //queue has only one element
		{
			front = -1;
			rear = -1;
		}
		else if(rear == 0)
			rear = maxSize-1;
		else
			rear = rear-1;
	}

	return retValue;
}//End of deleteRearEnd()

void Deque::display()
{
	cout << "Front = " << front << "	rear = " << rear << "\n";

	if(isEmpty())
		cout << "Queue is empty\n";
	else
	{
		int i = front;
		if(front <= rear)
		{
			while(i <= rear)
				cout << queueArray[i++] << "\n";
		}
		else
		{
			while(i <= maxSize-1)
				cout << queueArray[i++] << "\n";
			
			i=0;
			while(i <= rear)
				cout << queueArray[i++] << "\n";
		}
	}
}//End of display()

int Deque::size()
{
	if(isEmpty())
		return 0;

	if(isFull())
		return maxSize-1;

	int i = front;
	int sz = 0;

	if(front <= rear)
	{
		while(i <= rear)
		{
			sz++;
			i++;
		}
	}
	else
	{
		while(i <= maxSize-1)
		{
			sz++;
			i++;
		}

		i = 0;
		while(i <= rear)
		{
			sz++;
			i++;
		}
	}

	return sz;
}//End of size()

int main()
{
	Deque dq;

	try
	{
		dq.insertFrontEnd(2);
		dq.insertFrontEnd(1);
		dq.insertRearEnd(3);
		dq.insertRearEnd(4);

		cout << "Queue Items : \n";
		dq.display();
		cout << "Total items : " << dq.size() << "\n";

		cout << "Deleted Item from front : " << dq.deleteFrontEnd() << "\n";
		cout << "Deleted Item from Rear : " << dq.deleteRearEnd() << "\n";
		cout << "Queue Items : \n";
		dq.display();

		dq.insertFrontEnd(5);
		dq.insertFrontEnd(6);

		cout << "Queue Items : \n";
		dq.display();

		dq.insertRearEnd(7);

		cout << "Deleted Item : " << dq.deleteFrontEnd() << "\n";
		cout << "Deleted Item : " << dq.deleteRearEnd() << "\n";
		cout << "Deleted Item : " << dq.deleteFrontEnd() << "\n";
		cout << "Deleted Item : " << dq.deleteRearEnd() << "\n";
		cout << "Deleted Item : " << dq.deleteFrontEnd() << "\n";

		cout << "Queue Items : \n";
		dq.display();

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}//End of main()
