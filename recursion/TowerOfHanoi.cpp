//TowerOfHanoi.cpp : Program to solve Tower of Hanoi problem using recursion.

#include <iostream>
using namespace std;

void tofh(int ndisk, char source, char temp, char dest)
{
	if(ndisk == 1)
	{
		cout << "Move Disk " << ndisk << " from " << source << "-->" << dest << "\n";
		return;
	}

	tofh(ndisk-1, source, dest, temp);
	cout << "Move Disk " << ndisk << " from " << source << "-->" << dest << "\n";
	tofh(ndisk-1, temp, source, dest);
}//End of tofh()

int main()
{
	char source='A', temp='B', dest='C';
	int ndisk=3;

	cout << "Sequence is :\n";
	tofh(ndisk, source, temp, dest);

	return 0;
}//End of main()


