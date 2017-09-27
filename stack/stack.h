#include <iostream>
#include <string>

using namespace std;

typedef string stack_element;


string infix_convert();//converts postfix expression to infix

#ifndef STACK_H
#define STACK_H

class stack_node
{
public:
	stack_element data;
	stack_node *next;
};

class stack
{
public:
	stack();//default constructor for stack
	~stack();//destructor for stack
	stack_element top(); //return the value at the top of a stack
	void pop(); //pop and item from the top from an of object stack
	void push(const stack_element &);//push and item to the top of an object of type stack

private:

	stack_node *s_top;
};
#endif



