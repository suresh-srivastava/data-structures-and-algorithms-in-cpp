//SeparateChaining.cpp : Program of Separate Chaining

#include<iostream>
#include<string>
using namespace std;

static const int maxSize = 11;

class Employee
{
	private:
		int employeeId;
		string employeeName;
	public:
		Employee(){};
		Employee(int id, string name);
		int getEmployeeId();
		void setEmployeeId(int id);
		friend ostream& operator<<(ostream& out, const Employee& emp);
};//End of class Employee

Employee::Employee(int id, string name)
{
	employeeId = id;
	employeeName = name;
}//End of Employee()

int Employee::getEmployeeId()
{
	return employeeId;
}//End of getEmployeeId()

void Employee::setEmployeeId(int id)
{
	employeeId = id;
}//End of setEmployeeId()

ostream& operator<<(ostream& out, const Employee& emp)
{
	out << " " << emp.employeeId << " " << emp.employeeName << "  " ;
	return out;
}//End of operator<<

class Node
{
	public:
		Employee info;
		Node *link;

	public:
		Node(Employee data)
		{
			info = data;
			link = NULL;
		}
};//End of class Node

class SingleLinkedList
{
	private:
		Node *start;
	public:
		SingleLinkedList();
		~SingleLinkedList();
		bool isEmpty();
		void display();
		Node* search(int key);
		void insertAtBeginning(Employee data);
		void deleteNode(int key);
};//End of class SingleLinkedList

SingleLinkedList::SingleLinkedList()
{
	start = NULL;
}//End of SingleLinkedList()

SingleLinkedList::~SingleLinkedList()
{
	Node *ptr;
	while(start != NULL)
	{
		ptr = start->link;
		delete start;
		start = ptr;
	}
}//End of ~SingleLinkedList()

bool SingleLinkedList::isEmpty()
{
	return (start == NULL);
}//End of isEmpty()

void SingleLinkedList::display()
{
	Node *ptr;

	if(!isEmpty())
	{
		ptr = start;
		while(ptr != NULL)
		{
			cout << ptr->info;
			ptr = ptr->link;
		}
		cout << "\n";
	}
	else
		cout << "List is empty\n";
}//End of display()

Node* SingleLinkedList::search(int key)
{
	Node *ptr = start;
	
	while(ptr != NULL)
	{
		if(ptr->info.getEmployeeId() == key)
			break;
		ptr = ptr->link;
	}

	return ptr;
}//End of search()

void SingleLinkedList::insertAtBeginning(Employee data)
{
	Node *temp;

	temp = new Node(data);
	if(!isEmpty())
		temp->link = start;

	start = temp;
}//End of insertAtBeginning()

void SingleLinkedList::deleteNode(int key)
{
	Node *ptr, *temp;

	ptr = start;
	if(isEmpty())
		cout << "Key " << key << " not present\n";
	else if(ptr->info.getEmployeeId() == key) //Deletion of first node
	{
		temp = ptr;
		start = ptr->link;
		delete temp;
	}
	else //Deletion in between or at the end
	{
		while(ptr->link != NULL)
		{
			if(ptr->link->info.getEmployeeId() == key)
				break;
			ptr = ptr->link;
		}
		if(ptr->link == NULL)
			cout << "Key " << key << " not present\n";
		else
		{
			temp = ptr->link;
			ptr->link = ptr->link->link;
			delete temp;
		}
	}//End of else
}//End of deleteNode()

class HashTable
{
	private:
		SingleLinkedList *arr;
		int m;  //size of the array
		int n;  //number of records
		int hash(int key);
	public:
		HashTable();
		~HashTable();
		void insert(Employee emp);
		bool search(int key);
		void del(int key);
		void display();
};//End of class HashTable

HashTable::HashTable()
{
	m = maxSize;
	n = 0;
	arr = new SingleLinkedList[m];
}//End of HashTable()

HashTable::~HashTable()
{
	delete[] arr;
}//End of ~HashTable()

int HashTable::hash(int key)
{
	return key%m;
}//End of hash()

bool HashTable::search(int key)
{
	int h = hash(key);
	Node *ptr = arr[h].search(key);

	if(ptr != NULL)
	{
		cout << ptr->info;
		return true;
	}

	return false;
}//End of search()

void HashTable::insert(Employee emp)
{
	int key = emp.getEmployeeId();
	int h = hash(key);
	
	if(search(key))
	{
		cout << " Duplicate key\n";
		return;
	}
	arr[h].insertAtBeginning(emp);
	n++;
}//End of insert()

void HashTable::del(int key)
{
	int h = hash(key);
	arr[h].deleteNode(key);
	n--;
}//End of del()

void HashTable::display()
{
	for(int i=0; i<m; i++)
	{
		cout << "[" << i << "]  -->";

		if(!arr[i].isEmpty())
			arr[i].display() ;
		else
			cout << " ___" << "\n";
	}
}//End of display()

int main()
{
	HashTable table;

	table.insert(Employee(15,"Suresh"));
	table.insert(Employee(28,"Manish"));
	table.insert(Employee(20,"Abhishek"));
	table.insert(Employee(45,"Srikant"));
	table.insert(Employee(82,"Rajesh"));
	table.insert(Employee(98,"Amit"));
	table.insert(Employee(77,"Vijay"));
	table.insert(Employee(9,"Alok"));
	table.insert(Employee(34,"Vimal"));
	table.insert(Employee(49,"Deepak"));

	table.display();

	cout << (table.search(15) ? "Key found" : "Key not found") << "\n";

	table.del(15);
	cout << (table.search(15) ? "Key found" : "Key not found") << "\n";

	table.display();

	return 0;
}//End of main()
