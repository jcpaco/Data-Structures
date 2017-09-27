#include <iostream>
#include "bqueue.h"
using namespace  std;

/*************************************************************************************
Function Name: BQUEUE
Precondition: The constructor has not been called
Postcondition: A BQUEUE object has been created
Description: Creates a BQUEUE onject with a doubly linked list
***************************************************************************************/
BQUEUE::BQUEUE()
{
	cout << "BQueue default constructor:" << endl;
	back = 0;
}

/*************************************************************************************
Function Name: ~BQUEUE
Precondition: none
Postcondition: object is deleted
Description: deallocates any space allocated with by a BQUEUE object
***************************************************************************************/
BQUEUE::~BQUEUE() 
{
	cout << "~BQueue: destructor:" << endl;
	while (back != 0)
	{
		Dequeue();
	}
}

/*************************************************************************************
Function Name: BQUEUE
Precondition: A BQUEUE object has been passed by reference
Postcondition: A hard copt of that object has been created
Description: Creates a BQUEUE oject with the same data as the object passed
***************************************************************************************/
BQUEUE::BQUEUE(const BQUEUE & a)
{
	cout << "BQueue copy constructor:"<<endl;
	back = 0;
	if (a.back != 0)
	{
		bqnode *f, *ptr;
		f = a.back->next;
		ptr = f;
		do
		{
			Enqueue(ptr->time);
			ptr = ptr->next;
		} while (ptr != f);
	}
}

/*************************************************************************************
Function Name: Enqueue
Precondition: value is to be added to queue
Postcondition: value is added at back of queue
Description: adds a given value to the queue
***************************************************************************************/
void BQUEUE::Enqueue(int insert)
{
	cout << "Enqueue( " << insert << " ):" << endl;
	if (back == 0)
	{
		back = new bqnode;
		back->time = insert;
		back->next = back;
		back->prev = back;
	}
	else
	{
		bqnode *f;
		f = back->next;
		back->next = new bqnode;
		back->next->time = insert;
		back->next->prev = back;
		back = back->next;
		back->next = f;
		f->prev = back;
	}
}

/*************************************************************************************
Function Name: Dequeue
Precondition: a queue object is not empty
Postcondition: value at the front of the queue is removed
Description: Removes a value at the front of the queue
***************************************************************************************/
void BQUEUE::Dequeue()
{
	cout << "Dequeue:" << endl;
	if (back != 0)
	{
		if (back == back->prev && back == back->next && back->next == back->prev)
		{
			delete back;
			back = 0;
		}
		else
		{
			bqnode *f;
			f = back->next;
			back->next = f->next;
			f->next->prev = back;
			delete f;
		}
	}

}

/*************************************************************************************
Function Name: Print
Precondition: ostream out is open
Postcondition: The queues values have been output to console
Description: Prints BQUEUE values
***************************************************************************************/
void BQUEUE::Print() 
{
	cout << "print:" << endl;
	if (back != 0)
	{
		bqnode *f, *ptr;
		f = back->next;
		ptr = f;
		do
		{
			cout << ptr->time << " ";
			ptr=ptr->next;
		} while (ptr != f);
		cout << endl << endl;
	}
}