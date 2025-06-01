//SumOfDigits.cpp : Program to display digits of a number and sum of digits of that number.

#include <iostream>
using namespace std;

//Displays digits of a number and finds the sum of digits of an integer
int sumOfDigits(long int n)
{
	int sum;

	if(n/10 == 0) //if n is a single digit number
	{
		cout << n%10;
		return n;
	}

	sum = (n%10 + sumOfDigits(n/10));
	cout << n%10;

	return sum;
}//End of sumOfDigits()

////Finds the sum of digits of an integer
//int sumOfDigits(long int n)
//{
//	if(n/10 == 0) //if n is a single digit number
//		return n;
//	return n%10 + sumOfDigits(n/10);
//}//End of sumOfDigits()

////Displays the digits of an integer
//void display(long int n)
//{
//	if(n/10 == 0)
//	{
//		cout << n;
//		return;
//	}
//	cout << n%10;
//	display(n/10);
//}//End of display()

////Displays the digits of an integer
//void display(long int n)
//{
//	if(n/10 == 0)
//	{
//		cout << n;
//		return;
//	}
//	display(n/10);
//	cout << n%10;
//}//End of display()

int main()
{
	long int num = 45329;

	cout << "Digits = ";
	//display(num);
	cout << "\nSum of digits = " << sumOfDigits(num) << "\n";

	return 0;
}
