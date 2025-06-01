//Divisibility9.cpp : Program to find a number is divisible from 9 or not. A number is divisible by 9 if and only if the sum of 
//digits of the number is divisible by 9.

#include <iostream>
using namespace std;

bool isDivisibleBy9(long int n)
{
	int sumOfDigits=0;

	if(n == 9)
		return true;

	if(n < 9)
		return false;

	while(n > 0)
	{
		sumOfDigits += n%10;
		n /= 10;
	}

	isDivisibleBy9(sumOfDigits);
}//End of isDivisibleBy9()

int main()
{
	long int num=1469358;

	cout << num << " is divisible by 9 : " << (isDivisibleBy9(num) ? "True" : "False") << "\n";

	return 0;
}//End of main()


