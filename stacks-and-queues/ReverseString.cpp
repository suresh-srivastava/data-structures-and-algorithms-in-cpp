//ReverseString.cpp : Program of reversing a string using stack.

#include<iostream>
#include<stack>
#include<string>
using namespace std;

string reverseString(string str)
{
	string temp = "";
	stack<char> st;

	for(int i=0; i<str.length(); i++)
		st.push(str[i]);

	while(!st.empty())
	{
		temp += st.top();
		st.pop();
	}

	return temp;
}//End of reverseString()

int main()
{
	string str = "algorithms";
	cout << "String is : " << str << "\n";

	cout << "Reversed string is : " << reverseString(str) << "\n";

	return 0;
}//End of main()
