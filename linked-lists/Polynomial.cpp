//Polynomial.cpp : Program of Polynomial expression creation, addition and multiplication using linked list.

#include<iostream>
using namespace std;

class Node
{
	public:
		int coeff;
		int expo;
		Node *link;

		Node(int coefficient, int exponent)
		{
			coeff = coefficient;
			expo = exponent;
			link = NULL;
		}
};//End of class Node

class Polynomial
{
	private:
		Node *start;
		
	public:
		Polynomial();
		~Polynomial();

		bool isEmpty();
		void display();
		int size();
		void insert(int coefficient, int exponent);
		void insertAtEnd(int coefficient, int exponent);
		void addition(Polynomial& list, Polynomial& resultList);
		void multiplication(Polynomial& list, Polynomial& resultList);

};//End of class Polynomial

Polynomial::Polynomial()
{
	start = NULL;
}//End of Polynomial()

Polynomial::~Polynomial()
{
	Node *ptr;
	while(start != NULL)
	{
		ptr = start->link;
		delete start;
		start = ptr;
	}
}//End of ~Polynomial()

bool Polynomial::isEmpty()
{
	return (start == NULL);
}//End of isEmpty()

void Polynomial::display()
{
	Node *ptr;

	if(!isEmpty())
	{
		ptr = start;
		while(ptr != NULL)
		{
			cout << ptr->coeff;
			if(ptr->expo == 1)
				cout << "x";
			else if(ptr->expo > 1)
				cout << "x^" << ptr->expo;
			ptr = ptr->link;
			if(ptr!=NULL)
				cout << " + ";
		}
		cout << "\n";
	}
	else
		cout << "Zero polynomial\n";
}//End of display()

void Polynomial::insert(int coefficient, int exponent)
{
	Node *ptr, *temp;

	temp = new Node(coefficient, exponent);
	//List empty or exponent greater than first one
	if(isEmpty() || exponent > start->expo)
	{
		temp->link = start;
		start = temp;	
	}
	else
	{
		ptr = start;
		while(ptr->link!=NULL && ptr->link->expo >= exponent)
			ptr = ptr->link;
		temp->link = ptr->link;
		ptr->link = temp;
	}
}//End of insert()

//Required for addition of polynomials
void Polynomial::insertAtEnd(int coefficient, int exponent)
{
	Node *ptr, *temp;

	temp = new Node(coefficient,exponent);

	if(isEmpty())
		start = temp;
	else
	{
		ptr = start;
		while(ptr->link != NULL)
			ptr = ptr->link;

		ptr->link = temp;
	}
}//End of insertAtEnd()

void Polynomial::addition(Polynomial& list, Polynomial& resultList)
{
	Node *p1 = start;
	Node *p2 = list.start;
	
	while(p1!=NULL && p2!=NULL)
	{
		if(p1->expo > p2->expo)
		{
			resultList.insert(p1->coeff, p1->expo);
			p1 = p1->link;
		}
		else if(p2->expo > p1->expo)
		{
			resultList.insert(p2->coeff, p2->expo);
			p2 = p2->link;
		}
		else if(p1->expo == p2->expo)
		{
			resultList.insert(p1->coeff+p2->coeff, p1->expo);
			p1 = p1->link;
			p2 = p2->link;
		}
	}
	//If poly2 is finished and elements left in poly1
	while(p1 != NULL)
	{
		resultList.insert(p1->coeff, p1->expo);
		p1 = p1->link;
	}
	//If poly1 is finished and elements left in poly2
	while(p2 != NULL)
	{
		resultList.insert(p2->coeff, p2->expo);
		p2 = p2->link;
	}

}//End of addition()

void Polynomial::multiplication(Polynomial& list, Polynomial& resultList)
{
	Node *p1 = start;
	Node *p2 = list.start;
	Node *p2Start = p2;

	if(p1==NULL || p2==NULL)
		cout << "Multiplied polynomial is zero polynomial\n";
	else
	{
		while(p1 != NULL)
		{
			p2 = p2Start;
			while(p2 != NULL)
			{
				resultList.insert(p1->coeff*p2->coeff, p1->expo+p2->expo);
				p2 = p2->link;	
			}
			p1 = p1->link;
		}
	}

}//End of multiplication()

int main()
{
	Polynomial list1, list2, list3, list4;

	list1.insert(4,3);
	list1.insert(5,2);
	list1.insert(-3,1);

	cout << "Polynomial List1 :\n";
	list1.display();

	list2.insert(2,5);
	list2.insert(6,4);
	list2.insert(1,2);
	list2.insert(8,0);

	cout << "Polynomial List2 :\n";
	list2.display();

	//Polynomial addition
	list1.addition(list2, list3);

	cout << "After addition of list1 and list2 :\n";
	list3.display();

	//Polynomial multiplication
	list1.multiplication(list2, list4);

	cout << "After multiplication of list1 and list2 :\n";
	list4.display();

	return 0;

}//End of main()

