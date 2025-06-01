//String3.cpp : Program to display the string in reverse order.

#include <iostream>
using namespace std;

void rdisplay(char *str)
{
	if(*str == '\0')
		return;

	rdisplay(str+1);
	cout << *str;
}//End of rdisplay()

int main()
{
	char stringArr[80] = "Newyork";

	cout << "String is : ";
	rdisplay(stringArr);
	cout << "\n";

	return 0;
}//End of main()


