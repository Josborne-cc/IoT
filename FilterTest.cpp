/*
Program: Convulution of a DTMF filter to determine the tone
*/

#include <iostream>
#include <vector>
#include "1209coefs.h"


using std::cout;
using std::endl;

int main()
{
	int i;

	for(i = 0; i < BL; i++)
		cout << B[i] << endl;
	
	return 0;
}
