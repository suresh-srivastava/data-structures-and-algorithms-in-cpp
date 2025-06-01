//String1.cpp : Program to find the length of a string.

#include <iostream>
using namespace std;

int length(char *str)
{
	if(*str == '\0')
		return 0;

	return (1 + length(str+1));
}//End of length()

int main()
{
	char stringArr[80] = "Lucknow";

	cout << "String is : " << stringArr << "\n";
	cout << "Length : " << length(stringArr) << "\n";

	return 0;
}//End of main()



