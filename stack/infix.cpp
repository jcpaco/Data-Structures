#include <iostream>
#include <string>
#include "stack.h"
using namespace std;


//PROGRAM HEADER
/********************************************************************************************

Name:  Jan Carlo Aldana                               Z#:23242372
Course: Date Structures and Algorithm Analysis (COP3530)
Professor: Dr. Lofton Bullard
Due Date:      10/14/2015                Due Time: 11:30 P.M.
Total Points: 100
Assignment 5: postfix to infix

Description: this program take in postfix expression and convert it to infix this program checks 
if there is toomany operators, too many operand which it will give error for both of these,
and if only one input, a space input, or completely empty if will output the one input, or the 
space, or stating that it is an empty expression

*********************************************************************************************/


int main()
{
	string output, again, enterkey;
	do
	{
		cout << " please enter a postfix expression (example:  a b * c / d - ), Hit ''Enter'' to end input : " << endl<<endl;
		output = infix_convert();
		cout << output <<endl<<endl;
		cout << "Would you like to enter another expression to convert ( Y / N ) " << endl << endl;
		cin >> again;
		enterkey = cin.get();
	}while (again != "n" && again != "N");
	return 0;
}