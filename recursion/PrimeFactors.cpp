//PrimeFactors.cpp : Program to find the prime factors of a number.

#include <iostream>
using namespace std;

void primeFactors(int num)
{
	int i=2;

	if(num == 1)
		return;

	while(num%i != 0)
		i++;

	cout << i << " ";
	primeFactors(num/i);
}//End of primeFactors()

int main()
{
	int num = 84;

	cout << "Prime factors of " << num << " :\n";
	primeFactors(num);
	cout << "\n";

	return 0;
}//End of main()


