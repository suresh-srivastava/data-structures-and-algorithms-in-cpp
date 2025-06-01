//Series.cpp : Program to display and find out the sum of series.
//Series : 1 + 2 + 3 + 4 + 5 +.......

#include <iostream>
using namespace std;

//int rseries(int n)
//{
//	if(n == 0)
//		return 0;
//	return n + rseries(n-1);
//	cout << n << " + ";
//}//End of rseries()

int rseries(int n)
{
	int sum;
	if(n == 0)
		return 0;
	sum = (n + rseries(n-1));
	cout << n << " + ";
	return sum;
}//End of rseries()

int main()
{
	int n = 5;

	cout << "\b\b= " << rseries(n) << "\n"; //\b to erase last + sign

	return 0;
}//End of main()
