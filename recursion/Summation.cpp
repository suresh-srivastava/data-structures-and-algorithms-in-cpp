//Summation.cpp : Program to find summation of numbers from 1 to n

#include <iostream>
using namespace std;

int summation(int n)
{
	if(n==0)
		return 0;

	return (n + summation(n-1));
}//End of summation()

int main()
{
	int n = 5;

	cout << "Summation(" << n << ") = " << summation(n) << "\n";

	return 0;
}//End of main()

