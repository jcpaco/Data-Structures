#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

/*************************************************************************************
Name: stack
Precondition: constructor has not been called
Postcondition:  a liststack object has been made
Description: creates a stack implemented with a singly linked list
***************************************************************************************/
stack::stack()
{
	s_top = 0;
}

/*************************************************************************************
Name: ~stack
Precondition: none
Postcondition: object is deleted
Description: deallocates any space allocated with by stack object
***************************************************************************************/
stack::~stack()
{
	while (s_top != 0)
	{
		pop();
	}
}

/*************************************************************************************
Name: top
Precondition: none 
Postcondition: return a string which is the top of the stack
Description: a string/stack_element is returned
***************************************************************************************/
stack_element stack::top()
{
	if (s_top != 0)
		return s_top->data;
	else
		return "";


}

/*************************************************************************************
Name: pop
Precondition: none
Postcondition: a value is popped off stck from the top
Description: pops value from stack
***************************************************************************************/
void stack::pop()
{
	if (s_top != 0)
	{
		stack_node * sptr = s_top;
		sptr = sptr->next;
		delete s_top;
		s_top = sptr;
	}
}

/*************************************************************************************
Name: push
Precondition: stack object
Postcondition: string is pushed onto a stack
Description: sting is pushed to the top of a stack
***************************************************************************************/
void stack::push(const stack_element & key)
{
	if (key.length() != 0 && key != " ")
	{
		stack_node *ptr = new stack_node;
		ptr->data = key;
		ptr->next = s_top;
		s_top = ptr;
	}
}


/*************************************************************************************
Name: infix_converter
Precondition: takes in a string of postfix
Postcondition: retrun a string of infix that has been converted from postfix
Description: infix expression returned
***************************************************************************************/
string infix_convert()//const string & postfix, stack & infixex, int &  opnd, int & oprt)
{
	stack infixex;
	char enter;
	string postfix,leftover;
	int opnd = 0, oprt = 0;
	while (1)
	{ 
		enter = cin.get();
		if (enter == '\n')
			break;
		if (enter != ' ')
		{
			cin.unget();
			cin >> postfix;
			if (postfix == "+" || postfix == "-" || postfix == "/" || postfix == "*")
			{
				oprt++;
				string a, b, output;
				b = infixex.top();
				infixex.pop();
				a = infixex.top();
				infixex.pop();
				if (a == "" || b == "")
				{
					getline(cin, leftover);
					return " too many operator, not enough operand ";
				}
				output = " ( " + a + " " + postfix + " " + b + " ) ";
				infixex.push(output);
			}
			else
			{
				opnd++;
				infixex.push(postfix);
			}
		}
	}
	if (opnd > oprt + 1)
	{
		return " too many operand, not enough operator";
	}
	return infixex.top();

}