//BaseConversion.cpp : Program to convert a positive decimal number to Binary, Octal or Hexadecimal.

#include <iostream>
using namespace std;

void convertBase(int num, int base)
{
	int rem = num%base;

	if (num==0)
		return;

	convertBase(num/base, base);

	if(rem < 10)
		cout << rem;
	else
		cout << char(rem-10+'A');
}//End of convertBase()

int main()
{
	int num = 20;

	cout << "Decimal number : " << num << "\n";
	cout << "Binary : ";		convertBase(num, 2);	cout << "\n";
	cout << "Octal : ";			convertBase(num, 8);	cout << "\n";
	cout << "Hexadecimal : ";	convertBase(num, 16);	cout << "\n";

	return 0;
}//End of main()

