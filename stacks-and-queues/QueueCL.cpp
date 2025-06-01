//QueueCL.cpp : Program to implement queue using circular linked list.

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

class QueueCL
{
    private:
		Node *rear;

    public:
		QueueCL();
		bool isEmpty();
		void enqueue(int data);
		int dequeue();
		int peek();
		void display();
		int size();
};//End of class QueueCL

QueueCL::QueueCL()
{
	rear = NULL;
}//End of QueueL()

bool QueueCL::isEmpty()
{
    return (rear == NULL);
}//End of isEmpty()

void QueueCL::enqueue(int data)
{
	Node *temp;

	temp = new Node(data);

	if(isEmpty()) //If queue is empty
	{
		rear = temp;
		temp->link = rear;
	}
	else
	{
		temp->link = rear->link;
		rear->link = temp;
		rear = temp;
	}
	
}//End of enqueue()

int QueueCL::dequeue()
{
	Node *temp;
	int retValue;

	if(isEmpty())
		throw exception("Queue is empty");

	if(rear->link == rear) //If only one element
	{
		temp = rear;
		rear = NULL;
	}
	else
	{
		temp = rear->link;
		rear->link = rear->link->link;
	}

	retValue = temp->info;
	delete temp;

	return retValue;
}//End of dequeue()

int QueueCL::peek()
{
	if(isEmpty())
		throw exception("Queue is empty");

	return rear->link->info;
}//End of peek()

void QueueCL::display()
{
	Node *ptr;

	if(!isEmpty())
	{
		ptr = rear->link;
		do
		{
			cout << ptr->info << "\n";
			ptr = ptr->link;
		}while(ptr != rear->link);
	}
	else
		cout << "Queue is empty\n";

}//End of display()

int QueueCL::size()
{
	Node *ptr;
	int count = 0;

	if(!isEmpty())
	{
		ptr = rear->link;
		do
		{
			count++;
			ptr = ptr->link;
		}while(ptr != rear->link);
	}

	return count;
}//End of size()

int main()
{
	QueueCL qu;

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








