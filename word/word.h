
#include <iostream>
#include <string>

using namespace std;

#ifndef WORD_H
#define WORD_H


class character
{
public:
	char symbol;
	character *next;
};

class WORD
{
public:

	WORD(); /*The default constructor will initialize your state 
	variables.  The front of the linked list is initially set to 
	NULL or 0; this implies a non-header node implementation of 
	the link list.*/

	WORD(const string & key); /*This constructor will have one 
	argument;  a C-style string or a C++ string representing the 
	word to be created;*/
	
	WORD(const WORD & Org); /*Used during a call by value, 
	return, or initialization/declaration of a word object;*/
	
	~WORD(); /*The destructor will de-allocate all memory 
	allocated for the word. Put the message "destructor called" 
	inside the body of the destructor.*/
	
	void Insert(const WORD & a, const int & position); /*Inserts 
	a copy of WORD a before the give value of position, if 
	position is 0 or 1 a is inserted at the front of current object
	*/
	
	int	Length(); /*Determines the length of the current object*/
	
	void Remove(const WORD & a); /*Deletes the first occurrence of 
	word a (removes the first set of characters that makeup a's 
	linked list from the current object linked list) from current 
	object;*/
	
	void RemoveALL(const WORD & a); /*Deletes the all occurrence of 
	word a (removes the all set of characters that makeup a's 
	linked list from the current object linked list) from current 
	object;*/
	
	bool IsEqual(const WORD & a); /*Returns true if two word objects 
	are equal; otherwise false; remember A is the current */
	
	bool IsEmpty(); /*Check to see if the word A is empty; A is the
	current object*/
	
	WORD & operator=(const string & a); /*Overload the assignment 
	operator as a member function to take a string (C-style or C++ 
	string, just be consistent in your implementation) as an 
	argument and assigns its value to A, the current object;*/
	
	WORD & operator=(const WORD & a); /*Overload the assignment 
	operator as a member function with chaining to take a word object
	as an argument and assigns its value to A, the current object;*/
	
	WORD & operator+(const WORD & b); /*Overload the ‘+” operator 
	as a member function without chaining  to add word B (adds the 
	set of symbols that makep B's linked list to the back of A's 
	linked list) to the back of word A; remember A is the current 
	object;*/
	
	friend ostream & operator<<(ostream & out, const WORD & a);/*
	Overload the insertion operator as a friend function with 
	chaining to print a word A; */

private:

	character *front, *back;

};
#endif

