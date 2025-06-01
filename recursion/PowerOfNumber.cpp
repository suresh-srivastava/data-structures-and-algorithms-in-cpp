//PowerOfNumber.cpp : Program to find the exponentiation of a number (a power n, example 2 power 3 = 8).

#include <iostream>
using namespace std;

long int power(int a, int n)
{
	if(n == 0)
		return 1;

	return (a * power(a, n-1));
}//End of power()

int main()
{
	int a=3, n=4;

	cout << a << " power " << n << " = " << power(a, n) << "\n";

	return 0;
}//End of main()



