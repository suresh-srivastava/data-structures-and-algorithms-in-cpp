//Display.cpp : Program to display numbers 1 to n and n to 1

#include <iostream>
using namespace std;

void display1(int n)
{
	if (n==0)
		return;

	cout << n << "\n";
	display1(n-1);
}//End of display1()

void display2(int n)
{
	if (n==0)
		return;

	display2(n-1);
	cout << n << "\n";
}//End of display2()

int main()
{
	int n = 5;

	cout << n << " to 1 :\n";
	display1(n);

	cout << "1 to " << n << " :\n";
	display2(n);

	return 0;
}//End of main()

