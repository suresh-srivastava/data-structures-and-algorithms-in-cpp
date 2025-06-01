//PQueue.cpp : Program to implement priority queue using linked list.

#include <iostream>
using namespace std;

class Node
{
	public:
		int info;
		int priority;
		Node *link;

		Node(int data, int priority)
		{
			info = data;
			this->priority = priority;
			link = NULL;
		}
};//End of class Node

class PQueue
{
	private:
		Node *front;

	public:
		PQueue();
		bool isEmpty();
		void enqueue(int data, int priority);
		int dequeue();
		int peek();
		void display();
		int size();
};//End of class PQueue

PQueue::PQueue()
{
	front = NULL;
}//End of PQueue()

bool PQueue::isEmpty()
{
    return (front == NULL);
}//End of isEmpty()

void PQueue::enqueue(int data, int priority)
{
	Node *temp, *ptr;

	temp = new Node(data, priority);

	//Queue is empty or element to be added has priority more than first element
	if(isEmpty() || priority < front->priority)
	{
		temp->link = front;
		front = temp;
	}
	else
	{
		ptr = front;
		while(ptr->link!=NULL && ptr->link->priority<=priority)
			ptr = ptr->link;
		temp->link = ptr->link;
		ptr->link = temp;
	}
}//End of enqueue()

int PQueue::dequeue()
{
	Node *temp;
	int retValue;

	if(isEmpty())
		throw exception("Queue is empty");
	else 
	{
		retValue = front->info;
		temp = front;
		front = front->link;

		delete temp;
	}

	return retValue;
}//End of dequeue()

int PQueue::peek()
{
	if(isEmpty())
		throw exception("Queue is empty");

	return front->info;
}//End of peek()

void PQueue::display()
{
	Node *ptr;

	if(!isEmpty())
	{
		cout << "Priority, Data Item\n";
		ptr = front;
		while(ptr != NULL)
		{
			cout << ptr->priority << ", " << ptr->info << "\n";
			ptr = ptr->link;
		}
	}
	else
		cout << "Queue is empty\n";

}//End of display()

int PQueue::size()
{
	Node *ptr;
	int count = 0;

	ptr = front;
	while(ptr != NULL)
	{
		count++;
		ptr = ptr->link;
	}

	return count;
}//End of size()

int main()
{
	PQueue pq;

	try
	{
		pq.enqueue(20,2);
		pq.enqueue(10,1);
		pq.enqueue(50,4);
		pq.enqueue(30,3);

		cout << "Queue Items : \n";
		pq.display();
		cout << "Front Item : " << pq.peek() << "\n";
		cout << "Total Items : " << pq.size() << "\n";

		cout << "Deleted Item : " << pq.dequeue() << "\n";
		cout << "Queue Items : \n";
		pq.display();

		pq.enqueue(40,5);

		cout << "Queue Items : \n";
		pq.display();

		cout << "Deleted Item : " << pq.dequeue() << "\n";
		cout << "Deleted Item : " << pq.dequeue() << "\n";
		cout << "Deleted Item : " << pq.dequeue() << "\n";
		cout << "Deleted Item : " << pq.dequeue() << "\n";

		cout << "Queue Items : \n";
		pq.display();

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}//End of main()
