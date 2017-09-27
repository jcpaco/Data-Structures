#include <iostream>
#include <fstream>
#include <string>
#include "tlist.h"

using namespace std;

//PROGRAM HEADER
/********************************************************************************************

Name:  Jan Carlo Aldana                               Z#:23242372
Course: Date Structures and Algorithm Analysis (COP3530)
Professor: Dr. Lofton Bullard
Due Date:      09/15/2015                Due Time: 11:00 P.M.
Total Points: 100
Assignment 3: TLIST program

Description: This program read list of string from a file and inserts them into an object of type 
TLIST in alphabetical. TList represents an ordered list, accessible by an index. You can add, change,
insert or remove an item from a list, or clear the entire list. Count contains the number 
of items in the queue. Capacity is the number of items the list can hold before being 
resized.  Locate and access objects in the list. Also resorts entire array if substring have been
added or removed.
*********************************************************************************************/

int main()
{
	cout<<endl << "****************Testing the Functionality of the TLIST class*********************************" << endl << endl;
	
	
	cout << "******************Testing default constructor********************" << endl;
	TLIST T;
	cout << "*****************Default constructor testing complete************" << endl << endl << endl;


	cout << "******************Testing copy constructor***********************" << endl;
	TLIST S(T);
	cout << "***************Copy constructor testing complete*****************" << endl << endl << endl;


	cout << "**************Testing Insert with (''errubfrrkirrdere'')********* " << endl << endl;
	T.Insert("errubfrrkirrdere");
	cout << "*********************Insert testing complete*********************" << endl << endl << endl;


	cout << "*************Testing Remove with (''stringtrist'')***************" << endl << endl;
	T.Remove("stringtrist");
	cout << "********************Remove testing complete**********************" << endl << endl << endl;


	cout << "*************Testing Remove with (''   fert    '')***************" << endl << endl;
	T.Remove("fert");
	cout << "********************Remove testing complete**********************" << endl << endl << endl;


	cout << "*************Testing SubstringInsert with (2, 2,''zez'')*********" << endl << endl;
	cout << T;
	T.SubstringInsert(2, 2, "zez");
	cout << T;
	cout << "*****************SubstringInsert testing complete****************" << endl << endl << endl;


	cout << "***********Testing SubstringInsert with (3, 20,''ahab'')*********" << endl << endl;
	cout << T;
	T.SubstringInsert(3, 20, "ahab");
	cout << T;
	cout << "*****************SubstringInsert testing complete****************" << endl << endl << endl;


	cout << "**********Testing SubstringInsert with (12, 2,''uijyt'')*********" << endl << endl;
	cout << T;
	T.SubstringInsert(12, 2, "uijyt");
	cout << T;
	cout << "*****************SubstringInsert testing complete****************" << endl << endl << endl;


	cout << "*****************Testing SubstringRemove with (1,''ab'')*********" << endl << endl;
	cout << T;
	T.SubstringRemove(1, "ab");
	cout << T;
	cout << "*****************SubstringRemove testing complete****************" << endl << endl << endl;


	cout << "*****************Testing SubstringRemove with (9,''a'')*********" << endl << endl;
	cout << T;
	T.SubstringRemove(9, "a");
	cout << T;
	cout << "*****************SubstringRemove testing complete****************" << endl << endl << endl;


	cout << "*****************Testing SubstringRemove with (15,''c'')*********" << endl << endl;
	cout << T;
	T.SubstringRemove(15, "c");
	cout << T;
	cout << "*****************SubstringRemove testing complete****************" << endl << endl << endl;


	cout << "*****************Testing SubstringCount with (10,''a'')**********" << endl << endl;
	cout<<T.SubstringCount(10, "a") << endl << endl;
	cout << "*****************SubstringCount testing complete*****************" << endl << endl << endl;


	cout << "*****************Testing SubstringCount with (9,''p'')**********" << endl << endl;
	cout<<T.SubstringCount(9, "p") << endl << endl;
	cout << "*****************SubstringCount testing complete*****************" << endl << endl << endl;


	cout << "*****************Testing SubstringCount with (0,''z'')**********" << endl << endl;
	cout << T.SubstringCount(0, "z") << endl << endl;
	cout << "*****************SubstringCount testing complete*****************" << endl << endl << endl;


	cout << "******************Testing Search with (''abc'')******************" << endl << endl;/////////
	T.Search("abc");
	cout << "**********************Search testing complete********************" << endl << endl << endl;


	cout << "**************Testing Search with (''fertyxcwt'')****************" << endl << endl;/////////
	T.Search("fertyxcwt");
	cout << "**********************Search testing complete********************" << endl << endl << endl;
	

	cout << "******************************************************************" << endl ;
	cout << "************************* TLIST T: OUTPUT*************************" << endl;
	cout << "******************************************************************" << endl << endl;
	cout << T << endl<<endl;
	cout << "******************************************************************" << endl;
	cout << "************************* TLIST S: OUTPUT*************************" << endl;
	cout << "******************************************************************" << endl << endl;
	cout << S << endl<<endl;
	return 0;
}