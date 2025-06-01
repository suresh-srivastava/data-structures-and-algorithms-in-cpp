//CheckParentheses.cpp : Program to check that parentheses in expression are valid or not.

#include<iostream>
#include<stack>
#include<string>
using namespace std;

bool matchParentheses(char leftPar, char rightPar)
{
	if(leftPar=='(' && rightPar==')')
		return true;

	if(leftPar=='{' && rightPar=='}')
		return true;

	if(leftPar=='[' && rightPar==']')
		return true;

	return false;
}//End of matchParentheses()

bool isValid(string expr)
{
	stack<char> st;

	for(int i=0; i<expr.length(); i++)
	{
		if(expr[i]=='(' || expr[i]=='{' || expr[i]=='[')
			st.push(expr[i]);

		if(expr[i]==')' || expr[i]=='}' || expr[i]==']')
		{
			if(st.empty())
			{
				cout << "Right parentheses are more than left parentheses\n";
				return false;
			}
			else
			{
				char ch = st.top();
				st.pop();
				if(!matchParentheses(ch, expr[i]))
				{
					cout << "Parentheses are : ";
					cout << ch << " and " << expr[i] << "\n";
					return false;
				}
			}
		}//End of if
	}//End of for

	if(st.empty())
	{
		cout << "Balanced Parentheses\n";
		return true;
	}
	else
	{
		cout << "Left parentheses are more than right parentheses\n";
		return false;
	}
}//End of isValid()

int main()
{
	string expression = "[A/(B-C)*D]";

	cout << "Expression is : " << expression << "\n";

	try
	{
		if(isValid(expression))
			cout << "Valid expression\n";
		else
			cout << "Invalid expression\n";
	}
	catch(exception e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}//End of main()
