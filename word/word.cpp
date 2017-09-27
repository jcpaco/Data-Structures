#include <iostream>
#include <string>
#include "word.h"

using namespace std;


/*************************************************************************************
Name:  WORD
Precondition: constructor has not been invoked
Postcondition: WORD has characters in a list
Description: constructs an instance of a WORD object
***************************************************************************************/
WORD::WORD()
{
	front = back = 0;
}

/*************************************************************************************
Name: WORD
Precondition: the constructor has not been invoked
Postcondition: WORD has a list of characters that represent the given string
Description: creates a WORD with a given value
***************************************************************************************/
WORD::WORD(const string & a)
{
	*this = a;
}

/*************************************************************************************
Name: WORD
Precondition: a WORD object is being passed by reference
Postcondition: a hard copy of that object has been created
Description: creates a hard copy of a WORD object
***************************************************************************************/
WORD::WORD(const WORD & a)
{
	*this = a;
}

/*************************************************************************************
Name: ~WORD
Precondition: an object has been created and passed
Postcondition: the object memory has been deallocated
Description: an object has been destroyed
***************************************************************************************/
WORD::~WORD()
{
	cout << "destructor called" << endl;
	character *ptr = front;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		delete front;
		front = ptr;
	}
}

/*************************************************************************************
Name: Insert
Precondition: none
Postcondition: inserts a WORD in an existing WORD at given position
Description: WORD is altered to include given WORD at given position
***************************************************************************************/
void WORD::Insert(const WORD & a, const int & position)
{
	if (position >= 0)
	{
		if (a.front != 0 && front!=0)
		{
			WORD copya = a;
			character *aptr = copya.front;
			if (position == 1 || position == 0)
			{
				character *fptr = new character;
				character *ptr = fptr;
				while (aptr != 0)
				{
					fptr->symbol = aptr->symbol;
					aptr = aptr->next;
					if (aptr == 0)
					{
						break;
					}
					fptr->next = new character;
					fptr = fptr->next;
				}
				fptr->next = front;
				front = ptr;

			}
			else if (position >= 2 && position <= Length())
			{
				character *fptr = front;
				character *ptr;
				for (int i = 1; i < position - 1; i++)
				{
					fptr = fptr->next;
				}
				ptr = fptr->next;
				fptr->next = new character;
				fptr = fptr->next;
				while (aptr != 0)
				{
					fptr->symbol = aptr->symbol;
					aptr = aptr->next;
					if (aptr == 0)
					{
						break;
					}
					fptr->next = new character;
					fptr = fptr->next;
				}
				fptr->next = ptr;
			}
			else if (position > Length())
			{
				character *bptr = back;
				bptr->next = new character;
				bptr = bptr->next;
				while (aptr != 0)
				{
					bptr->symbol = aptr->symbol;
					aptr = aptr->next;
					if (aptr == 0)
					{
						break;
					}
					bptr->next = new character;
					bptr = bptr->next;
				}
				bptr->next = 0;
				back = bptr;
			}
		}
		else if(front==0 && a.front!=0)
		{
			*this = a;
		}
	}
}

/*************************************************************************************
Name: Remove
Precondition: none
Postcondition: removes first instance of given WORD
Description: remove first instance of a WORD in a WORD
***************************************************************************************/
void WORD::Remove(const WORD & a)
{
	if (front != 0 && a.front != 0)
	{
		WORD copya = a;
		character *fptr = front;
		character *aptr = copya.front;
		int count = 0;
		int position = 0;
		int loc = 0;
		if (Length() >= copya.Length())
		{
			while (fptr != 0 && aptr != 0)
			{
				position++;
				if (fptr->symbol == aptr->symbol)
				{
					if (loc == 0)
					{
						loc = position;
					}
					count++;
					aptr = aptr->next;
				}
				else if (count > 0 && fptr->symbol != aptr->symbol)
				{
					loc = 0;
					count = 0;
					aptr = copya.front;
				}
				fptr = fptr->next;
			}
			if (count == copya.Length() && loc == 1)
			{

				character *ptr = front;
				for (int i = 0; i < copya.Length() && ptr != 0; i++)
				{
					ptr = ptr->next;
					delete front;
					front = ptr;
				}
				if (front == 0)
				{
					back = 0;
				}
			}
			else if (count == copya.Length()&&loc>1&&loc<=Length())
			{
				character *ptr;
				character *prev = 0;
				character *curr = front;
				for (int i = 0; i < loc - 1;i++)
				{
					prev = curr;
					curr = curr->next;
				}
				for (int i = 0; i < copya.Length(); i++)
				{
					ptr = curr;
					curr = curr->next;
					delete ptr;
					prev->next = curr;
				}
				if (curr == 0)
				{
					back = prev;
				}
			}
			else
			{
				loc = 0;
			}
		}
	}
}

/*************************************************************************************
Name: RemoveAll
Precondition: none
Postcondition: removes all instances of a WORD within a WORD
Description: removes every instance of a WORD within a WORD
***************************************************************************************/
void WORD::RemoveALL(const WORD & a)
{
	if (front != 0 && a.front != 0)
	{
		WORD copya = a;
		character *fptr;
		character *aptr;
		int count;
		int position;
		int loc =1;
		if (Length() >= copya.Length())
		{
			while (loc != 0)
			{ 
				loc = 0;
				fptr = front;
				aptr = copya.front;
				position = 0;
				count = 0;
				while (fptr != 0 && aptr != 0)
				{
					position++;
					if (fptr->symbol == aptr->symbol)
					{
						if (loc == 0)
						{
							loc = position;
						}
						count++;
						aptr = aptr->next;
					}
					else if (count > 0 && fptr->symbol != aptr->symbol)
					{
						loc = 0;
						count = 0;
						aptr = copya.front;
					}
					fptr = fptr->next;
				}
				if (count == copya.Length() && loc == 1)
				{
					character *ptr = front;
					for (int i = 0; i < copya.Length() && ptr != 0; i++)
					{
						ptr = ptr->next;
						delete front;
						front = ptr;
					}
					if (front == 0)
					{
						back = 0;
					}
				}
				else if (count == copya.Length() && loc>1 && loc <=Length())
				{
					character *ptr;
					character *prev = 0;
					character *curr = front;
					for (int i = 0; i < loc - 1; i++)
					{
						prev = curr;
						curr = curr->next;
					}

					for (int i = 0; i < copya.Length(); i++)
					{
						ptr = curr;
						curr = curr->next;
						delete ptr;
						prev->next = curr;
					}
					if (curr == 0)
					{
						back = prev;
					}
				}
				else
				{
					loc = 0;
				}
			}
		}
	}


}






/*************************************************************************************
Name: IsEqual
Precondition: none
Postcondition: True if WORDs are identical
Description: Determines if two WORDs are equal
***************************************************************************************/
bool WORD::IsEqual(const WORD & a)
{
	WORD copya = a;
	character *fptr = front;
	character *aptr = copya.front;
	int size1 = Length();
	int size2 = copya.Length();
	if (size1 != size2)
	{
		return false;
	}
	else
	{
		while (fptr != 0)
		{
			if (fptr->symbol != aptr->symbol)
			{
				return false;
			}
			fptr = fptr->next;
			aptr = aptr->next;
		}
	}

	return true;
}

/*************************************************************************************
Name: Length
Precondition: none
Postcondition: returns length of WORD
Description: gives the length of the WORD
***************************************************************************************/
int WORD::Length()
{
	character *fptr = front;
	int count = 0;
	while (fptr != 0)
	{
		count++;
		fptr = fptr->next;
	}
	return count;
}



/*************************************************************************************
Name: IsEmpty
Precondition: none
Postcondition: checks if WORD is empty
Description: Reports if a WORD is empty
***************************************************************************************/
bool WORD::IsEmpty()
{
	return(front == 0);
}


/*************************************************************************************
Name: operator=
Precondition: none
Postcondition: a WORD object is made from a string
Description: a WORD object is made
***************************************************************************************/
WORD & WORD::operator=(const string & a)
{
	front = new character;
	character *fptr = front;
	int strsize = a.length();
	if (strsize == 0)
	{
		front = back = 0;
		return *this;
	}
	for (int i = 0; i < strsize; i++)
	{
		fptr->symbol = a[i];
		if (i == strsize - 1)
		{
			break;
		}
		fptr->next = new character;
		fptr = fptr->next;
	}
	fptr->next = 0;
	back = fptr;
	return *this;
}



/*************************************************************************************
Name: operator=
Precondition: none
Postcondition: a WORD is copied from a given WORD
Description: a WORD is copied
***************************************************************************************/
WORD & WORD::operator=(const WORD & a)
{
	if(a.front==0)
	{
		front = back = 0;
	}
	else if (this != &a)
	{
		front = new character;
		character *fptr = front;
		character *aptr = a.front;
		while (aptr != 0)
		{
			fptr->symbol = aptr->symbol;

			aptr = aptr->next;
			if (aptr == 0)
			{
				break;
			}
			fptr->next = new character;
			fptr = fptr->next;
		}
		fptr->next = 0;
		back = fptr;

	}
	return *this;
}



/*************************************************************************************
Name: operator+
Precondition: none
Postcondition: a WORD is added to the end of another WORD
Description: a WORD is added to the end of another WORD
***************************************************************************************/
WORD & WORD::operator+(const WORD & b)
{
	WORD copyb = b;

	if (IsEmpty() != 1 && copyb.IsEmpty() != 1)
	{
		character *aptr = back;
		character  *bptr = copyb.front;
		aptr->next = new character;
		aptr = aptr->next;

		while (bptr != 0)
		{
			aptr->symbol = bptr->symbol;

			bptr = bptr->next;
			if (bptr == 0)
			{
				break;
			}
			aptr->next = new character;
			aptr = aptr->next;
		}
		aptr->next = 0;
		back = aptr;
	}
	else if (IsEmpty() == 1 && copyb.IsEmpty()!= 1)
	{
		*this = b;
	}
	return *this;
}


ostream & operator<<(ostream & out, const WORD & a)
{
	if (a.front != 0)
	{
		character *p = a.front;
		while (p != 0)
		{
			out << p->symbol;
			p = p->next;
		}
		out << endl << endl;
	}
	return out;
}