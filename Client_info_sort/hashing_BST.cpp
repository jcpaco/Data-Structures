
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
 
class BST_Node  //node in a BST
{
  public:
    string lastname, firstname, address, phone_number;
    BST_Node  *lchild, *rchild;   //left and right children pointers
};
 
class Clients_Info_BST //Binary Search Tree
{
   public:
			Clients_Info_BST();//store the data in the hash table
           Clients_Info_BST(const Clients_Info_BST &);//Copy Constructor
            ~Clients_Info_BST();//Destructor           
           void Insert(const string & s);
           void Remove(const string & s);
           void Update(const string & s);
           void Print();
		   void File_Print(ofstream &);
           BST_Node * Search(const string & s);
		   BST_Node * get_root();
		   void set_root(BST_Node*);
            
//other member functions you may need.
    private:
		void delete_BST(BST_Node * &);
		void File_Inorder(BST_Node*, ofstream &);
		void Inorder(BST_Node *);
		void BST_Remove(BST_Node * &, const string & s);
		BST_Node * Remove_replacement(BST_Node * &);
		void copy(BST_Node * &, BST_Node *);

		BST_Node *root; //---state information
};

class Client_Address_Book
{
    public:
            Client_Address_Book();//default constructor will read data from input file "client_address_data.txt".
            Client_Address_Book(const Client_Address_Book &);//Copy Constructor
            ~Client_Address_Book();//Destructor
             void Insert(const string & s);// insert record
             void Remove(const string & s);//remove record
             void Update(const string & s);//update record
             void Print_BST(const string & s);//ornt
             void Print_Hash_Table();
             void Print_Hash_Table_to_File(const string & filename);///function will print hash table to output file                                                                                                                                                                                
             bool Search(const string & s);
             unsigned int Hash_Function(const string & s);
			 void copy(BST_Node * &, BST_Node *);
     // Hint:  Remember that the insert, remove and search function for Clients_Address_Book will use //     
    //Client_Info_BST’s insert, remove and search respectively.
    
  private:
	  
      int capacity;  //SET THIS VALUE EQUAL TO 27  YOUR DEFAULT CONSTRUCTOR
   Clients_Info_BST * hash_table; // USING 1 THROUGH 26 or whatever you like
	// Clients_Info_BST hash_table[27];
};

bool formatcheck(const string & s);
//bool textcheck(const string & s);


Client_Address_Book::Client_Address_Book()
{
	capacity = 27;
	hash_table = new  Clients_Info_BST[capacity];
	string s;
	ifstream in;
	in.open("client_address_data.txt");
	while (getline(in,s))
	{
		if(!s.empty())
			Insert(s);
	}
	in.close();
}
Client_Address_Book::Client_Address_Book(const Client_Address_Book &org)
{
	capacity = 27;
	hash_table = new  Clients_Info_BST[capacity];
	BST_Node *f1, *f2;
	for(int i = 0; i < 27;i++)
	{
		f1 = hash_table[i].get_root();
		f2 = org.hash_table[i].get_root();
		copy(f1, f2);
		hash_table[i].set_root(f1);

	}
}
Client_Address_Book::~Client_Address_Book()
{
	for (int i = 1; i < 27; i++)
	{
		hash_table[i].~Clients_Info_BST();
	}
	delete[] hash_table;
	hash_table = 0;
}
void Client_Address_Book::Insert(const string & s)
{

	int index = Hash_Function(s);//(int)s[0] - 64;
	
	if (formatcheck(s) == false)
	{
		if (index >= 33 && index <= 58)
		{
			cout << "please capitalize the first letter of your first and last name" << endl;
		}
		else
		cout << "invalid input" << endl;
		
	}
	else if (index >= 1 && index <= 26)
	{
		hash_table[index].Insert(s);
	}
	else if (s != "")
	{
		cout << "Please enter a valid name" << endl;
	}
}
void Client_Address_Book::Remove(const string & s)
{
	int index = Hash_Function(s);
	if (index >= 1 && index <= 26)
	{
		hash_table[index].Remove(s);
	}
	else if (index >= 33 && index <= 58)
	{
		cout << "please capitalize the first letter of your first and last name" << endl;
		cout<<"to be able to find the  client and delete them"<< endl;
	}
	else if(s!="")
	{
		cout << "Please enter a valid name" << endl;
	}
}
void Client_Address_Book::Update(const string & s)
{
	string function, lname, fname, change;
	int check = 0;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
		{
		
			if (function.empty())
			{
				function= s.substr(check, i);
				check = i + 1;
			}
			else if (lname.empty())
			{
				lname = s.substr(check, i - check);
				check = i + 1;
			}
			else if (fname.empty())
			{
				fname = s.substr(check, i - check);
				check = i + 1;
			}
			else if (change.empty())
			{
				change = s.substr(check);
				break;
			}
		}
	}
	int index = Hash_Function(lname);
	if (index == 30)
	{
		cout << "client not found" << endl;
		return;
	}
	BST_Node*update = hash_table[index].Search(lname + " " + fname);
	
	if (update == 0)
	{
		cout << "client not found" << endl;
		return;
	}
	else if(function=="1")
	{ 
		if (formatcheck(change) == true)
		{
			hash_table[index].Remove(lname + " " + fname);
			index = Hash_Function(change);
			hash_table[index].Insert(change);
		}
		else
			cout << "Client Cannot Be Updated" << endl;
	}
	else if(function == "2")
	{ 
		if (formatcheck(change + " " + update->phone_number) == true)
		{
			
			index = Hash_Function(change);
			hash_table[index].Insert(change + " " + update->phone_number);
			index = Hash_Function(lname);
			hash_table[index].Remove(lname + " " + fname);
		}
		else
			cout << "Client Cannot Be Updated" << endl;
	}
	else if (function == "3")
	{
		hash_table[index].Update(s);
	}
	else if (function == "4")
	{
		string templ, tempf, tempph;
		int position = 0;
		for (unsigned int i = 0; i < change.length(); i++)
		{
			if (change[i] == ' ')
			{
				if (templ.empty())
				{
					templ = change.substr(position, i);
					position = i + 1;
				}
				else if (tempf.empty())
				{
					tempf= change.substr(position, i-position);
					position = i + 1;
					tempph = change.substr(position);
					break;
				}
			}
		}
		if (formatcheck(templ + " " + tempf + " " + update->address + " " + tempph) == true)
		{
			
			index = Hash_Function(templ);
			hash_table[index].Insert(templ + " " + tempf + " " + update->address + " " + tempph);
			index = Hash_Function(lname);
			hash_table[index].Remove(lname + " " + fname);
		}
		else
			cout << "Client Cannot Be Updated" << endl;
	}
	else if (function == "5")
	{
		if (formatcheck(change + " " + update->address + " " + update->phone_number) == true)
		{
			
			index = Hash_Function(change);
			hash_table[index].Insert(change +" "+update->address+" " +update->phone_number);
			index = Hash_Function(lname);
			hash_table[index].Remove(lname + " " + fname);
		}
		else
			cout << "Client Cannot Be Updated" << endl;
	}
	else if (function == "6")
	{
		hash_table[index].Update(s);
	}
	else if (function == "7")
	{
		hash_table[index].Update(s);
	}
	else
	{
		cout << "invalid update function" << endl;
	}
}
void Client_Address_Book::Print_BST(const string & s)
{
	int index = Hash_Function(s);
	if (index >= 1 && index <= 26)
	{
		
		//BST_Node * Client= 
		hash_table[index].Print();
		/*if (Client != 0)
		{
			cout << Client->lastname << " " << Client->firstname << " " << Client->address << " " << Client->phone_number << endl;
		}
		else
		{
			cout << "client not found" << endl;
		}*/
	}
	else if (index >= 33 && index <= 58)
	{
		cout << "please capitalize the first letter of your first and last name" << endl;
		cout << "to be able to find the  client and delete them" << endl;
	}
	else if (s != "")
	{
		cout << "Please enter a valid name" << endl;
	}
}
void Client_Address_Book::Print_Hash_Table()
{
	cout<<"Inside Client_Address_Book Print_Hash_Table\n\n";
	for (int i = 1; i < 27; i++)
	{
		hash_table[i].Print();
	}
}
void Client_Address_Book::Print_Hash_Table_to_File(const string & filename)
{
	ofstream out;
	out.open(filename);
	for (int i = 1; i < 27; i++)
	{
		hash_table[i].File_Print(out);
	}
	out.close();
}
bool Client_Address_Book::Search(const string & s)
{
	cout<<"Inside Client_Address_Book Search\n";
	int index = Hash_Function(s);
	if (index >= 1 && index <= 26)
	{
		BST_Node *hold=hash_table[index].Search(s);
		if(hold!=0)
			return true;
	}
	else if (index >= 33 && index <= 58)
	{
		cout << "please capitalize the first letter of your first and last name" << endl;
	}
	else if (s != "")
	{
		cout << "Please enter a valid name" << endl;
	}
	return false;
}
unsigned int Client_Address_Book::Hash_Function(const string & s)
{
	if (s.empty() != 1)
		return (int)s[0] - 64;
	else
		return 30;

}
void  Client_Address_Book::copy(BST_Node * & ptr, BST_Node * org)
{
	if (org != 0)
	{
		ptr = new BST_Node;
		ptr->lastname = org->lastname;
		ptr->firstname = org->firstname;
		ptr->address = org->address;
		ptr->phone_number = org->phone_number;
		ptr->lchild = 0;
		ptr->rchild = 0;
		copy(ptr->lchild, org->lchild);
		copy(ptr->rchild, org->rchild);
	}
	else
		ptr = org;
}









Clients_Info_BST::Clients_Info_BST()
{
	root = 0;
}
Clients_Info_BST::Clients_Info_BST(const Clients_Info_BST &org)
{
	root = 0;
	if (org.root != 0)
	{
		copy(root, org.root);
	}
}
Clients_Info_BST::~Clients_Info_BST()
{
	delete_BST(root);
	root = 0;
}
void Clients_Info_BST::Insert(const string & s)
{
	BST_Node *ptr = new BST_Node;
	string holder;
	int position = 0;
	int adresslength = 0;
	int slength = s.length();
	cout << "   Inside Client_Info_BST Insert\n";
	if (s[0] <= 0x5a && s[0] >= 0x41)
	{
		for (unsigned int i = 0; i < s.length(); i++)
		{
			if (s[i]==' ')
			{
				if (s[position] <= 0x5a && s[position] >= 0x41)
				{
					if (ptr->lastname.empty())
					{
						ptr->lastname = s.substr(position, i);
						position = i + 1;
					}
					else if (ptr->firstname.empty())
					{
						ptr->firstname = s.substr(position, i - position);
						position = i + 1;
					}
					else if (ptr->address.empty())
					{
						adresslength = slength - ptr->lastname.length() - ptr->firstname.length() - 8 - 3;
						ptr->address = s.substr(position, adresslength);
						ptr->phone_number = s.substr(slength - 8, 8);
						break;
					}
				}
				else if (s[position] <= 0x39 && s[position] >= 0x30)
				{
					if (ptr->address.empty())
					{
						adresslength = slength - ptr->lastname.length() - ptr->firstname.length() - 8 - 3;
						ptr->address = s.substr(position, adresslength);
					}
					ptr->phone_number = s.substr(slength - 8, 8);
					break;
				}
			}
		}
		ptr->lchild = 0;
		ptr->rchild = 0;
		if (root == 0)
		{
			root = ptr;
		}
		else
		{
			BST_Node * fptr = root;
			while (1)
			{
				if (ptr->lastname > fptr->lastname)
				{
					if (fptr->rchild == 0)
					{
						fptr->rchild = ptr;
						break;
					}
					else
					{
						fptr = fptr->rchild;
					}
				}
				else if (ptr->lastname < fptr->lastname)
				{
					if (fptr->lchild == 0)
					{
						fptr->lchild = ptr;
						break;
					}
					else
					{
						fptr = fptr->lchild;
					}
				}
				else if (ptr->lastname == fptr->lastname)
				{
					if (ptr->firstname>fptr->firstname)
					{
						if (fptr->rchild == 0)
						{
							fptr->rchild = ptr;
							break;
						}
						else
						{
							fptr = fptr->rchild;
						}
					}
					else if(ptr->firstname<fptr->firstname)
					{
						if (fptr->lchild == 0)
						{
							fptr->lchild = ptr;
							break;
						}
						else
						{
							fptr = fptr->lchild;
						}
					}
					else if (ptr->firstname == fptr->firstname)
					{
						if (ptr->address != fptr->address && ptr->phone_number != fptr->phone_number)
						{
							if (ptr->address > fptr->address)
							{
								if (fptr->rchild == 0)
								{
									fptr->rchild = ptr;
									break;
								}
								else
								{
									fptr = fptr->rchild;
								}
							}
							else if (ptr->address < fptr->address)
							{
								if (fptr->lchild == 0)
								{
									fptr->lchild = ptr;
									break;
								}
								else
								{
									fptr = fptr->lchild;
								}
							}
						}
						else
						{
							cout << "replica info cannot be inserted"<<endl;
							break;
						}
					}
					
				}
			}
		}
	}
}
void Clients_Info_BST::Remove(const string & s)
{
	cout<<"   Inside Client_Info_BST Remove\n";
	BST_Remove(root, s);
}
void Clients_Info_BST::Update(const string & s)
{
	cout<<"   Inside Client_Info_BST Update\n";
	string function, lname, fname, change;
	int check = 0;
	BST_Node*ptr;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
		{

			if (function.empty())
			{
				function = s.substr(check, i);
				check = i + 1;
			}
			else if (lname.empty())
			{
				lname = s.substr(check, i - check);
				check = i + 1;
			}
			else if (fname.empty())
			{
				fname = s.substr(check, i - check);
				check = i + 1;
				change = s.substr(check);
				break;
			}
			
		}
	}
	ptr = Search(lname + " " + fname);
	if (ptr == 0)
	{
		cout << "Client not found"<<endl;
		return;
	}
	if (function=="3")
	{
		string a, p;
		if (change.length() < 10)
		{
			cout << "Client Cannot Be Updated" << endl;
			return;
		}
		a = change.substr(0, change.length() - 9);
		p = change.substr(change.length() - 8, 8);
		if (formatcheck(ptr->lastname+" "+ptr->firstname+" "+a+" "+p) == true)
		{
			ptr->address = a;
			ptr->phone_number = p;
		}
		else
			cout << "Client Cannot Be Updated" << endl;
			
	}
	else if (function=="6")
	{
		if (change.length() < 1)
		{
			cout << "Client Cannot Be Updated" << endl;
			return;
		}
		if (formatcheck(ptr->lastname + " " + ptr->firstname + " "+change+" "+ptr->phone_number ) == true)
		{
			ptr->address = change;

		}
		else
			cout << "Client Cannot Be Updated" << endl;
	}
	else if (function=="7")
	{
		if (change.length() < 8)
		{
			cout << "Client Cannot Be Updated" << endl;
			return;
		}
		if (formatcheck(ptr->lastname + " " + ptr->firstname + " "+ptr->address+" "+change) == true)
		{

			ptr->phone_number = change;
		}
		else
			cout << "Client Cannot Be Updated" << endl;
	}

}
void Clients_Info_BST::Print( )
{
	//cout<<"   Inside Client_Info_BST Print\n";
	if (root!=0)
	{
		Inorder(root);
	}
}
BST_Node * Clients_Info_BST::Search(const string & s)
{
	cout<<"   Inside Client_Info_BST Search\n";
	string name[2];
	int index = 0;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
			index++;
		else if (index == 0)
			name[index] = name[index] + s[i];
		else if (index == 1)
			name[index] = name[index] + s[i];
	}
	string lname = name[0], fname = name[1];
	if (root != 0)
	{
		BST_Node *ptr = root;
		while (ptr != 0)
		{
			if (lname > ptr->lastname)
				ptr = ptr->rchild;
			else if (lname < ptr->lastname)
				ptr = ptr->lchild;
			else if (lname == ptr->lastname)
			{
				if (fname > ptr->firstname)
					ptr = ptr->rchild;
				else if (fname < ptr->firstname)
					ptr = ptr->lchild;
				else if (fname == ptr->firstname)
				{
					return ptr;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
	
}
void Clients_Info_BST::Inorder(BST_Node *ptr)
{
	if (ptr!=0)
	{
		Inorder(ptr->lchild);
		cout << ptr->lastname<<" "<< ptr->firstname << " "<<ptr->address<< " " << ptr->phone_number << " "<< endl<<endl;
		Inorder(ptr->rchild);
	}
}
void Clients_Info_BST::File_Inorder(BST_Node*ptr, ofstream & out)
{
	if (ptr != 0)
	{
		File_Inorder(ptr->lchild, out);
		out << ptr->lastname << " " << ptr->firstname << " " << ptr->address << " " << ptr->phone_number << " " << endl << endl;
		File_Inorder(ptr->rchild, out);
	}
}

void Clients_Info_BST::File_Print(ofstream & out)
{
	if (root != 0)
	{
		File_Inorder(root,out);
	}
}
void Clients_Info_BST::delete_BST(BST_Node * &ptr)
{
	if (ptr != 0)
	{
		if(ptr->lchild!=0)
			delete_BST(ptr->lchild);
		if(ptr->rchild!=0)
			delete_BST(ptr->rchild);
		delete ptr;
	}
	ptr = 0;
}
void Clients_Info_BST::BST_Remove(BST_Node * & ptr, const string & s)
{
	string name[2];
	int index = 0;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
			index++;
		else if (index == 0)
			name[index] = name[index] + s[i];
		else if (index == 1)
			name[index] = name[index] + s[i];
	}
	string lname = name[0], fname = name[1];
	if (ptr != 0)
	{
		BST_Node * hold;
		string replace;
		if (lname > ptr->lastname)
			BST_Remove(ptr->rchild, s);
		else if (lname < ptr->lastname)
			BST_Remove(ptr->lchild, s);
		else if (lname == ptr->lastname)
		{
			if (fname > ptr->firstname)
				BST_Remove(ptr->rchild, s);
			else if (fname < ptr->firstname)
				BST_Remove(ptr->lchild, s);
			else if (fname == ptr->firstname)
			{
				if (ptr->lchild == 0)
				{
					hold = ptr->rchild;
					delete ptr;
					ptr = hold;
				}
				else if (ptr->rchild == 0)
				{
					hold = ptr->lchild;
					delete ptr;
					ptr = hold;
				}
				else
				{
					hold = Remove_replacement(ptr);
					ptr->lastname = hold->lastname;
					ptr->firstname = hold->firstname;
					ptr->address = hold->address;
					ptr->phone_number = hold->phone_number;
					replace = hold->lastname + " " + hold->firstname;
					BST_Remove(ptr->rchild, replace);
				}
			}
		}
	}
	else
		cout << "Client not found" << endl;
}
BST_Node * Clients_Info_BST::Remove_replacement(BST_Node * &in)
{
	BST_Node * ptr = in->rchild;
	while (ptr->lchild != 0)
	{
		ptr = ptr->lchild;
	}
	return ptr;
}
void Clients_Info_BST::copy(BST_Node * & ptr, BST_Node * org)
{
	if (org != 0)
	{
		ptr = new BST_Node;
		ptr->lastname = org->lastname;
		ptr->firstname = org->firstname;
		ptr->address = org->address;
		ptr->phone_number = org->phone_number;
		ptr->lchild = 0;
		ptr->rchild = 0;
		copy(ptr->lchild, org->lchild);
		copy(ptr->rchild, org->rchild);
	}
	else
		ptr = org;

}
BST_Node * Clients_Info_BST::get_root()
{
	return root;
}
void Clients_Info_BST::set_root(BST_Node*f)
{
	root = f;
}

bool formatcheck(const string & s)
{
	int position = 0, adresslength;
	string l, f, a, ph;
	unsigned int checklength = 0;
	if (s.empty() != 1 && s[0] <= 0x5a && s[0] >= 0x41)
	{
		for (unsigned int i = 0; i < s.length(); i++)
		{
			if (s[i] == ' ')
			{
				if (s[position] <= 0x5a && s[position] >= 0x41)
				{
					if (l.empty())
					{
						l = s.substr(position, i);
						position = i + 1;
					}
					else if (f.empty())
					{
						f = s.substr(position, i - position);
						position = i + 1;
					}
					else if (a.empty())
					{
						adresslength = s.length() - l.length() - f.length() - 8 - 3;
						a = s.substr(position, adresslength);
						ph = s.substr(s.length() - 8, 8);
						break;
					}
				}
				else if (s[position] <= 0x39 && s[position] >= 0x30)
				{
					if (a.empty())
					{
						adresslength = s.length() - l.length() - f.length() - 8 - 3;
						a = s.substr(position, adresslength);
					}
					ph = s.substr(s.length() - 8, 8);
					break;
				}
			}
		}
		checklength = l.length() + f.length() + ph.length() + 4;
		if (s.length() < checklength || l.empty() || f.empty() || a.empty() || ph.empty())
		{
			cout << "incorrect format" << endl;
			return false;
		}
		if (ph.length() != 8)
		{
			cout << "incorrect format" << endl;
			return false;
		}
		int num = 0;
		for (unsigned int f = 0; f < ph.length(); f++)
		{
			if (ph[f] <= 0x39 && ph[f] >= 0x30 || ph[f] == '-')
			{
				num++;
			}
			else
			{
				cout << "incorrect format" << endl;
				return false;
			}
		}
		if (ph[3] != '-')
		{
			cout << "incorrect format" << endl;
			return false;
		}
		num = 0;
		for (unsigned int b = 0; b < l.length(); b++)
		{
			if (l[b] <= 0x5a && l[b] >= 0x41 || l[b] <= 0x7a && l[b] >= 0x61)
			{
				num++;
			}
			else
			{
				cout << "incorrect format" << endl;
				return false;
			}
		}
		num = 0;
		for (unsigned int c = 0; c < f.length(); c++)
		{
			if (f[c] <= 0x5a && f[c] >= 0x41 || f[c] <= 0x7a && f[c] >= 0x61)
			{
				num++;
			}
			else
			{
				cout << "incorrect format" << endl;
				return false;
			}
		}
		num = 0;
		for (unsigned int d = 0; d < a.length(); d++)
		{
			if (a[d] <= 0x39 && a[d] >= 0x30 ||a[d] == '-')
			{
				num++;
				if (num == 8)
				{
					cout << "incorrect format" << endl;
					return false;
				}
			}
			else
			{
				num = 0;
			}
		}
		return true;
	}

	return false;

}
/*bool textcheck(const string &s)
{
	if (s.empty())
	{
		return false;
	}
	int count = 0;
	int space = 0;

	if (s[0] <= 0x5a && s[0] >= 0x41)
	{
		for (unsigned int i = 0; i < s.length(); i++)
		{
			if (s[i] <= 0x5a && s[i] >= 0x41 || s[i] <= 0x7a && s[i] >= 0x61 || s[i] <= 0x39 && s[i] >= 0x30 || s[i] == ' ' || s[i] == '-')
			{
				count++;
			}
			else
			{
				return false;
			}
			if (s[i] == ' ')
			{
				space++;
			}
			if (s[i] == '\0')
			{
				return false;
			}
		}
		if (space < 3)
		{
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}*/

int main()
{
	
	/*Client_Address_Book b;
	b.Print_Hash_Table();
	b.Insert("Tommtyt");
	b.Print_Hash_Table_to_File("sorted_client_address_bk.txt");
	b.Print_BST("Tom Cat");
	//b.Remove("Tom Cat");
	b.Print_Hash_Table();
	b.Update("3 Tom Cat ere 788-8886");
	b.Print_Hash_Table();*/
	Client_Address_Book My_Book;

	My_Book.Insert("Bullard Lofton 777 Glades Road 207-2780");

	//My_Book.Remove("Bullard Lofton");

	My_Book.Print_BST("B");
	My_Book.Print_BST("C");

	//My_Book.Update("1 Bullard Lofton Clark James 888 Glades Run 527-9985");
	//My_Book.Update("2 Bullard Lofton Clark James 887 Glades Run");
	//My_Book.Update("3 Bullard Lofton 784 Glades Run 585-6666");
	//My_Book.Update("4 Bullard Lofton Clark James 554-8952");
	//My_Book.Update("5 Bullard Lofton Clark James");
	//My_Book.Update("6 Bullard Lofton 857 Dixie Hwy");
	//My_Book.Update("7 Bullard Lofton 425-3345");
	//My_Book.Print_BST("B");
	//My_Book.Print_BST("C");
	if (My_Book.Search("Bullarod Lofton"))
		cout << "here"<<endl;
	else
		cout << "not here"<<endl;
//	My_Book.Print_Hash_Table();

	My_Book.Print_Hash_Table_to_File("b.txt");

//	Client_Address_Book b = My_Book;

	return 0;

}