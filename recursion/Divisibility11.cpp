//Divisibility11.cpp : Program to find a number is divisible from 11 or not.
//A number is divisible by 11 if and only if the difference of the sums of digits at odd positions and even positions is either zero 
//or divisible by 11.

#include <iostream>
using namespace std;

bool isDivisibleBy11(long int n)
{
	int s1=0, s2=0, diff;

	if (n==0)
		return true;

	if (n<10)
		return false;

	while(n>0)
	{
		s1 += n%10;
		n /= 10;

		s2 += n%10;
		n /= 10;
	}

	diff = s1>s2 ? (s1-s2) : (s2-s1);

	isDivisibleBy11(diff);
}//End of isDivisibleBy11()

int main()
{
	long int num=62938194;

	cout << num << " is divisible by 11 : " << (isDivisibleBy11(num) ? "True" : "False") << "\n";

	return 0;
}//End of main()


