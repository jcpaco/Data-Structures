#include <iostream>
#include "bqueue.h"

using namespace std;

int main()
{
	cout << "/////////////////////////////////  BQUEUE K //////////////////////////////////" << endl;
	BQUEUE  k;

	k.Enqueue(60);
	k.Print();
	k.Enqueue(20);
	k.Print();
	k.Enqueue(30);
	k.Print();
	k.Enqueue(10);
	k.Print();
	k.Print(); 
	k.Enqueue(50);
	k.Enqueue(40);
	k.Print();

	cout << "//////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "/////////////////////////////////  BQUEUE J=K //////////////////////////////////" << endl;

	BQUEUE j = k;
	cout << "////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "/////////////////////////////////  BQUEUE J //////////////////////////////////" << endl;
	j.Print();
	j.Dequeue();
	j.Print();
	j.Dequeue();
	j.Print();
	j.Dequeue();
	j.Print();
	j.Dequeue();
	j.Print();
	j.Dequeue();
	j.Print();
	j.Dequeue();
	j.Print();
	j.Enqueue(80);
	j.Print();
	j.Dequeue();
	cout << "//////////////////////////////////////////////////////////////////////////////" << endl;
	return 0;
}