//CQueue.cpp : Program to implement circular queue using array.

#include <iostream>
using namespace std;

static const int maxSize = 5;

class CQueue
{
	private:
		int queueArray[maxSize];
		int front;
		int rear;

	public:
		CQueue();
		bool isEmpty();
		bool isFull();
		void enqueue(int num);
		int dequeue();
		int peek();
		void display();
		int size();
};//End of class CQueue

CQueue::CQueue()
{ 
	front = -1;
	rear = -1; 
}//End of CQueue()

bool CQueue::isEmpty()
{
	return (front == -1);
}//End of isEmpty()

bool CQueue::isFull()
{
	return ((front==0 && rear==maxSize-1) || (front==rear+1));
}//End of isFull()

void CQueue::enqueue(int num)
{
	if(isFull())
	{
		cout << "Queue Overflow\n";
	}
	else
	{
		if(front == -1)
			front = 0;

		if(rear == maxSize-1) //rear is at last position of queue
			rear = 0;
		else
			rear = rear+1;

		queueArray[rear] = num;
	}
}//End of enqueue()

int CQueue::dequeue()
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
}//End of dequeue()

int CQueue::peek()
{
	if(isEmpty())
		throw exception("Queue is empty");

	return queueArray[front];
}//End of peek()

void CQueue::display()
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

int CQueue::size()
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
	CQueue cq;

	try
	{
		cq.enqueue(1);
		cq.enqueue(2);
		cq.enqueue(3);
		cq.enqueue(4);

		cout << "Queue Items : \n";
		cq.display();
		cout << "Front Item : " << cq.peek() << "\n";
		cout << "Total items : " << cq.size() << "\n";

		cout << "Deleted Item : " << cq.dequeue() << "\n";
		cout << "Deleted Item : " << cq.dequeue() << "\n";
		cout << "Queue Items : \n";
		cq.display();

		cq.enqueue(5);
		cq.enqueue(6);

		cout << "Queue Items : \n";
		cq.display();

		cq.enqueue(7);

		cout << "Deleted Item : " << cq.dequeue() << "\n";
		cout << "Deleted Item : " << cq.dequeue() << "\n";
		cout << "Deleted Item : " << cq.dequeue() << "\n";
		cout << "Deleted Item : " << cq.dequeue() << "\n";
		cout << "Deleted Item : " << cq.dequeue() << "\n";

		cout << "Queue Items : \n";
		cq.display();

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}//End of main()
