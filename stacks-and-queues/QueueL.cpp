//QueueL.cpp : Program to implement queue using linked list.

#include <iostream>
using namespace std;

class Node
{
    public:
        int info;
        Node *link;

        Node(int data)
        {
            info = data;
            link = NULL;
        }
};//End of class Node

class QueueL
{
    private:
		Node *front;
		Node *rear;

    public:
		QueueL();
		bool isEmpty();
		void enqueue(int data);
		int dequeue();
		int peek();
		void display();
		int size();
};//End of class QueueL

QueueL::QueueL()
{
	front = NULL;
	rear = NULL;
}//End of QueueL()

bool QueueL::isEmpty()
{
    return (front == NULL);
}//End of isEmpty()

void QueueL::enqueue(int data)
{
	Node *temp;

	temp = new Node(data);

	if(isEmpty()) //If queue is empty
		front = temp;
	else
		rear->link = temp;

	rear = temp;
}//End of enqueue()

int QueueL::dequeue()
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

int QueueL::peek()
{
	if(isEmpty())
		throw exception("Queue is empty");

	return front->info;
}//End of peek()

void QueueL::display()
{
	Node *ptr;

	if(!isEmpty())
	{
		ptr = front;
		while(ptr != NULL)
		{
			cout << ptr->info << "\n";
			ptr = ptr->link;
		}
	}
	else
		cout << "Queue is empty\n";
}//End of display()

int QueueL::size()
{
	Node* ptr;
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
	QueueL qu;

	try
	{
		qu.enqueue(1);
		qu.enqueue(2);
		qu.enqueue(3);
		qu.enqueue(4);

		cout << "Queue Items :\n";
		qu.display();
		cout << "Front Item : " << qu.peek() << "\n";
		cout << "Total items : " << qu.size() << "\n";

		cout << "Deleted Item : " << qu.dequeue() << "\n";
		cout << "Queue Items :\n";
		qu.display();

		qu.enqueue(5);

		cout << "Queue Items :\n";
		qu.display();

		cout << "Deleted Item : " << qu.dequeue() << "\n";
		cout << "Deleted Item : " << qu.dequeue() << "\n";
		cout << "Deleted Item : " << qu.dequeue() << "\n";
		cout << "Deleted Item : " << qu.dequeue() << "\n";

		cout << "Queue Items :\n";
		qu.display();

	}//End of try
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}//End of main()


