//InfixToPostfix.cpp : Program to covert infix to postfix and evaluate the postfix expression.
//It will evaluate only single digit numbers.

#include<iostream>
#include<stack>
#include<string>
using namespace std;

string infixToPostfix(string infix);
int evaluatePostfix(string postfix);
int precedence(char symbol);
int power(int b, int a);

int power(int b, int a)
{
	int result=1;

	for(int i=1; i<=a; i++)
		result *= b;

	return result;
}//End of power()

int evaluatePostfix(string postfix)
{
	char symbol;
	int a, b, temp;
	stack<int> st;

	for(int i=0; i<postfix.length(); i++)
	{
		symbol = postfix[i];

		if(symbol-'0' >= 0 && symbol-'0' <= 9)
		{
			st.push(symbol-'0');
		}
		else
		{
			a = st.top();
			st.pop();
			b = st.top();
			st.pop();

			switch(symbol)
			{
				case '+':
					temp = b+a; break;
				case '-':
					temp = b-a; break;
				case '*':
					temp = b*a; break;
				case '/':
					temp = b/a; break;
				case '%':
					temp = b%a; break;
				case '^':
					temp = power(b, a); break;
			}//End of switch

			st.push(temp);
		}//End of else
	}//End of for

	return st.top();
}//End of evaluatePostfix()

int precedence(char symbol)
{
	switch(symbol)
	{
		case '(':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 3;
		default:
			return 0;
	}
}//End of precedence()

string infixToPostfix(string infix)
{
	string postfix = "";
	char symbol;
	stack<char> st;

	for(int i=0; i<infix.length(); i++)
	{
		symbol = infix[i];

		switch(symbol)
		{
			case '(':
				st.push(symbol);
				break;
			case ')':
				while(st.top() != '(')
				{
					postfix += st.top();
					st.pop();
				}
				st.pop();
				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '^':
				while( !st.empty() && ( precedence(st.top()) >= precedence(symbol) ) )
				{
					postfix += st.top();
					st.pop();
				}
				st.push(symbol);
				break;
			default:
				postfix += symbol;
				break;
		}//End of switch
	}//End of for

	while(!st.empty())
	{
		postfix += st.top();
		st.pop();
	}

	return postfix;
}//End of infixToPostfix()

int main()
{
	string infix = "7+5*3^2/(9-2^2)+6*4";
	string postfix;

	cout << "Infix expression is : " << infix << "\n";

	postfix = infixToPostfix(infix);

	cout << "Postfix expression is :\n";
	cout << postfix << "\n";

	cout << "Value of expression is :\n";
	cout << evaluatePostfix(postfix) << "\n";

	return 0;
}//End of main()





