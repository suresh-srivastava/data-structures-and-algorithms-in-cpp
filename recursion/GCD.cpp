//GCD.cpp : Program to find greatest common divisor of two numbers.

#include <iostream>
using namespace std;

int GCD(int a, int b)
{
	if(b == 0)
		return a;

	return GCD(b, a%b);
}//End of GCD()

int main()
{
	int num1=35, num2=21;

	cout << "GCD = " << GCD(num1, num2) << "\n";

	return 0;
}//End of main()



