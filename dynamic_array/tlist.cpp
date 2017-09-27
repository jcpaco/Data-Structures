#include <string>
#include <iostream>
#include <fstream>
#include "tlist.h"

using namespace std;

/*************************************************************************************
Name: TLIST
Precondition: Constructor has not been invoked.
Postcondition: count=0, array DB of size capacity = 2.
Description:   Constructs an instance of a TLIST object.
***************************************************************************************/
TLIST::TLIST()                //default constructor sets the following: count = 0, capacity = //2, and allocates memory the size of string[capacity]
{
	cout << endl;
	cout << " ##### Default Constructor Invoked  ##### " << endl << endl;
	count = 0;
	capacity = 2;
	DB = new string[capacity];
	string s;
	ifstream in;
	in.open("myData.txt");
	while (in>>s)
	{
		Insert(s);
	}
}

/*************************************************************************************
Name: TLIST
Precondition: A TLIST object is being passed by reference.
Postcondition: A hard copy of a TLIST object has been created.
Description: Creates a hard copy of a TLIST object.
***************************************************************************************/
TLIST::TLIST(const TLIST  &Obj) //copy constructor
{
	cout << endl;
	cout << " ##### Copy  Constructor Invoked ##### " << endl << endl;
	count = Obj.count;
	capacity = Obj.capacity;
	DB = new string[capacity];
	for (int i = 0; i < count; i++)
	{
		DB[i] = Obj.DB[i];
	}
	cout << *this << endl;
}

/*************************************************************************************
Name: ~TLIST
Precondition: Destructor has not been invoked.
Postcondition: array DB deleted.
Description: Deallocates memory of a TLIST object.
***************************************************************************************/
TLIST::~TLIST()              //destructor
{
	cout << endl;
	cout << " ##### Destructor Invoked ##### " << endl << endl;
	delete[] DB;
}

/*************************************************************************************
Name: IsEmpty
Precondition: none
Postcondition: return  true if count == 0, otherwise returns false
Description: checks to see if DB is empty
***************************************************************************************/
bool TLIST::IsEmpty()         //return true if empty; otherwise false
{
	cout << endl;
	cout << "------Is_Empty  Invoked------" << endl << endl;
	return (count==0?true:false);
}

/*************************************************************************************
Name: IsFull
Precondition: none
Postcondition: returns true if count==capacity, otherwise returns false
Description: Checks to see if DB is at full capacity
***************************************************************************************/
bool TLIST::IsFull()        //return true if full; otherwise false
{
	cout << endl;
	cout << "------Is_Full Invoked------" << endl << endl;
	return (count == capacity ? true : false);
}

/*************************************************************************************
Name: Search
Precondition: none
Postcondition: Item Found printed when string is found in DB, else Item Not Found printed
Description: Shows if a string is contained in DB
***************************************************************************************/
int TLIST::Search(const string &key) //returns the location of the string in the dynamic array
{
	cout << endl;
	cout << " ##### Search Invoked ##### " << endl;
	cout<<"Search Key: "<<key << endl;
	for (int i = 0; i < count; i++)
	{
		if (key == DB[i])
		{
			cout << "Item Found" << endl;
			cout<<"loc:"<<i<< endl << endl;

			return i;
		}
	}
	cout << "Item Not Found" << endl;
	cout<<key<<" is not in dynamic array"<< endl<<endl;
	return -1;
}

/*************************************************************************************
Name: Insert
Precondition: none
Postcondition: key is inserted in order
Description: A string, key, is inserted into the array
***************************************************************************************/
void TLIST::Insert(const string & key) //add key to dynamic array if not full; otherwise prints a message stating dynamic array is full
{
	cout << endl;
	cout << " ##### Insert Invoked ##### " << endl << endl;
	cout<<"Insert key: "<<key<<endl << endl << endl;
	cout << *this << endl;
	if (IsEmpty())
	{
		DB[count] = key;
		count++;
		cout << *this << endl;
		return;
	}
	else if (IsFull())
	{
		DoubleSize();
	}
	for (int i = 0; i < count; i++)
	{
		if (key < DB[i])
		{
			for (int j = count; j > i; j--)
			{
				DB[j] = DB[j - 1];
			}
			DB[i] = key;
			count++;
			cout << *this << endl;
			return;
		}
	}
	DB[count] = key;
	count++;
	cout << *this << endl;
}

/*************************************************************************************
Name: Remove
Precondition: none
Postcondition: If key is present, key is deleted from array
Description: Removes an instance of the string, key, from DB
***************************************************************************************/
void TLIST::Remove(const string & key) //removes key from dynamic array if it is there; //otherwise prints a message stating it was not in dynamic array
{
	cout << endl;
	cout << " ##### Remove Invoked ##### " << endl;
	cout << "Remove key: " << key << endl << endl;
	cout << *this << endl;
	int loc = Search(key);
	if (loc != -1)
	{
		for (int i = loc; i+1 < count; i++)
		{
			DB[i] = DB[i + 1];
		}
		count--;
		cout << " '' " << key << " '' removed from dynamic array"<<endl<<endl;
	}
	else
	{
		cout << " '' " << key << " '' not removed from dynamic array" << endl << endl;
	}
	
	cout << *this<<endl;
}

/*************************************************************************************
Name: SubstringCount
Precondition: loc must be lest than count
Postcondition: return the amount of substring in the string at location loc of DB
Description: goes through a string from the array and count the amount of the time the 
substring is seen in the string
***************************************************************************************/
int TLIST::SubstringCount(const int loc, const string & substring)//loc is the location of //the string in the array and substring is the string you are counting
{
	cout << endl;
	cout << " ##### SubstringCount Invoked ##### " << endl << endl;
	int substringcount = 0;
	if(loc<count)
	{
		cout << "string: " << DB[loc] << endl << endl;
		cout << "substring: " << substring << endl << endl;
		string locstring = DB[loc];
		for (unsigned int i = 0; i < locstring.length() - substring.length() + 1; i++)
		{
			if (locstring.substr(i, substring.length()) == substring)
			{
				substringcount++;
			}
		}
	}
	else
	{
		cout << "Invalid location" << endl << endl;
		substringcount = -1;
	}

	return substringcount;
}

/*************************************************************************************
Name: SubstringInsert
Precondition: none
Postcondition: substring is inserted at specified loc, and pos
Description:insert the substring at position pos of the string  inside the array located at  loc
***************************************************************************************/
void TLIST::SubstringInsert(const int loc, const int pos , const string &substring)
{
	cout << endl;
	cout << " ##### SubstringInsert Invoked ##### " << endl;
	if (loc < count)
	{
		string str = DB[loc];
		int last = str.length();
		if (pos < last)
		{
			str.insert(pos, substring);
			cout << "substring key: '' " << substring << " '' inserted in " << DB[loc] << " at pos: " << pos << endl << endl;
		}
		else if(pos>=last)
		{
			str.insert(last, substring);
			cout << "substring key: '' " << substring << " '' inserted in " << DB[loc] << " at pos: " << last << endl << endl;
		}
		DB[loc] = str;
		Modifysort();
	}
	else
	{
		cout << "substring key: ''" << substring<<"'' not inserted loc is not a valid location" << endl << endl;
	}
}

/*************************************************************************************
Name: SubstringRemove
Precondition: loc must be less than count
Postcondition: remove all substring from string in the location loc of DB
Description:   goes through a string from the array and removes all the substring that
can be found
***************************************************************************************/
void TLIST::SubstringRemove(const int loc, const string & substring)//loc is the location of //the string in the array and substring is the to be removed
{
	cout << endl;
	cout << " ##### SubstringRemove Invoked ##### " << endl<<endl;
	cout << "substring key: " << substring << endl << endl;
	int subcount = SubstringCount(loc, substring);
	int substringloc;
	string locstring = DB[loc];
	if (subcount == -1)
	{
		cout << "  " << loc << " is not a valid index" << endl << endl;
	}
	else if (subcount>0)
	{
		cout << " '' " << substring << " '' removed from " << DB[loc] << endl << endl;
		for (int subcount1 = 0; subcount!=subcount1;subcount1++)
		{ 
			substringloc = locstring.find(substring);
			locstring.erase(substringloc, substring.length());
		}
		DB[loc] = locstring;
		Modifysort();
	}
	else if(subcount==0)
	{
		cout << " '' " << substring << " ''  not inside the string"<< endl << endl;
	}

}

/*************************************************************************************
Name: DoubleSize
Precondition: none
Postcondition:  DB has double the capacity before this function was called
Description: deallocate old memory and allocate new memory double the size of the old 
memory
***************************************************************************************/
void TLIST::DoubleSize()//doubles the capacity of the array, copies the contains of the old //arrry, and de-allocates the old array's memory
{
	cout << endl;
	cout << "------DoubleSize Invoked------" << endl << endl;
	capacity *= 2;
	string *temp = new string[capacity];
	for (int i = 0; i<count; i++)
	{
		temp[i] = DB[i];
	}

	delete[] DB;
	DB = temp;
}
/*************************************************************************************
Name: Submodifysort
Precondition: none
Postcondition: Db is sorted
Description: setup copy of db to a string array and the deallocate and reallocate new memory
for DB and then calls sort to insert the string that have been copied but now in order only 
used by Modifysort
***************************************************************************************/
void TLIST::Submodifysort(const string & key)
{
	if (count==0)
	{
		DB[count] = key;
		count++;
		return;
	}
	else if (count==capacity)
	{
		DoubleSize();
	}
	for (int i = 0; i < count; i++)
	{
		if (key < DB[i])
		{
			for (int j = count; j > i; j--)
			{
				DB[j] = DB[j - 1];
			}
			DB[i] = key;
			count++;
			return;
		}
	}
	DB[count] = key;
	count++;
}

/*************************************************************************************
Name:Modifysort
Precondition: none
Postcondition: DB is sorted
Description: works like insert and insert the string in DB in alphabetical order, only 
can be used by substringInsert and substringremove to resort the array affter the strings
in the array have been modified
***************************************************************************************/
void TLIST::Modifysort()
{
	string *temp = new string[capacity];
	int size = count;
	for (int i = 0; i<count; i++)
	{
		temp[i] = DB[i];
	}
	count = 0;
	delete[]DB;
	DB = new string[capacity];
	for (int j = 0; j < size; j++)
	{
		Submodifysort(temp[j]);
	}
	delete[]temp;
}



ostream & operator<<(ostream & out, const TLIST & Org)// print the contents of //the dynamic array
{
	for (int i = 0; i < Org.count; i++)
	{
		out << Org.DB[i] <<endl;
	}
	out << endl;
	return out;
}
