//TRFactorial.cpp : Program to find the factorial of a number using tail recursion.

#include <iostream>
using namespace std;

long int trFactorial(int n, int result)
{
	if(n == 0)
		return result;

	return trFactorial(n-1, n*result);
}//End of trFactorial()

long int trFactorial(int n)
{
	return trFactorial(n, 1);
}//End of trFactorial()

int main()
{
	int num = 5;

	if(num < 0)
		cout << "No factorial for negative number\n";
	else
		cout << "Factorial of " << num << " = " << trFactorial(num) << "\n";
	return 0;
}//End of main()

