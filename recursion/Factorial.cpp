//Factorial.cpp : Program to find the factorial of a number using recursion.

#include <iostream>
using namespace std;

long int factorial(int n)
{
	if(n==0)
		return 1;

	return (n * factorial(n-1));
}//End of factorial()

int main()
{
	int num = 5;

	if(num < 0)
		cout << "No factorial for negative number\n";
	else
		cout << "Factorial of " << num << " = " << factorial(num) << "\n";
	return 0;
}//End of main()
