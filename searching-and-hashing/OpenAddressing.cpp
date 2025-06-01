//OpenAddressing.cpp : Program of Open Addressing - Linear Probing

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

class HashTable
{
	private:
		Employee *arr;
		int m;	//size of array
		int n;	//number of employee records
		int *status;
		static const int EMPTY = 0;
		static const int DELETED = 1;
		static const int OCCUPIED = 2;

	private:
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
	arr = new Employee[m];
	status = new int[m];

	for(int i=0; i<m; i++)
		status[i] = EMPTY;

}//End of HashTable()

HashTable::~HashTable()
{
	delete[] arr;
	delete[] status;
}//End of ~HashTable()

int HashTable::hash(int key)
{
	return key%m;
}//End of hash()

void HashTable::insert(Employee emp)
{
	int key = emp.getEmployeeId();
	int h = hash(key);

	int location = h;

	for(int i=1; i<m; i++)
	{
		if(status[location]==EMPTY || status[location]==DELETED)
		{
			arr[location] = emp;
			status[location] = OCCUPIED;
			n++;
			return;
		}

		if(arr[location].getEmployeeId() == key)
		{
			cout << "Duplicate key\n";
			return;
		}

		location = (h+i)%m;
	}
	
	cout << "Table is full\n";
}//End of insert()

bool HashTable::search(int key)
{
	int h = hash(key);
	int location = h;

	for(int i=1; i<m; i++)
	{
		if(status[location]==EMPTY || status[location]==DELETED)
			return false;

		if(arr[location].getEmployeeId() == key)
		{
			cout << arr[location] << "\n";
			return true; 
		}

		location = (h+i)%m;
	}

	return false;
}//End of search()

void HashTable::del(int key)
{
	int h = hash(key);
	int location = h;

	for(int i=1; i<m; i++)
	{
		if(status[location]==EMPTY || status[location]==DELETED)
		{
			cout << "Key not found\n";
			return;
		}

		if(arr[location].getEmployeeId() == key)
		{
			status[location] = DELETED;
			n--;
			cout <<"Record " << arr[location] << " deleted\n";
			return;
		}

		location = (h + i) % m;
	}
}//End of del()

void HashTable::display()
{
	for(int i=0; i<m; i++)
	{
		cout << "[" << i << "] --> ";

		if(status[i] == OCCUPIED)
			cout << arr[i] << "\n";
		else
			cout << "___" << "\n";
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


