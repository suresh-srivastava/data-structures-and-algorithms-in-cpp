//String2.cpp : Program to display the string.

#include <iostream>
using namespace std;

void display(char *str)
{
	if(*str == '\0')
		return;

	cout << *str;

	display(str+1);
}//End of display()

int main()
{
	char stringArr[80] = "Bangalore";

	cout << "String is : ";
	display(stringArr);
	cout << "\n";

	return 0;
}//End of main()


