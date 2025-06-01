//Fibonacci.cpp : Program to generate fibonacci series.

#include <iostream>
using namespace std;

int fib(int n)
{
	if(n==0 || n==1)
		return 1;

	return (fib(n-1) + fib(n-2));
}//End of fib()

int main()
{
	int nterms=10;

	for (int i=0; i < nterms ; i++)
		cout << fib(i) << " ";

	cout << "\n";

	return 0;
}//End of main()


