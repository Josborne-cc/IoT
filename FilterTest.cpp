/*
Program: Convulution of a DTMF filter to determine the tone
*/

#include <iostream>
#include <vector>
#include <fstream>
#include "1209coefs.h"


using std::cout;
using std::endl;

#define SignalLen 512
#define MAXLEN 2000

void convolve(double *signal, double *result);

int main()
{
	int i;

	double x1209[512];
	double result[MAXLEN];
	std::ifstream input;
	std::ofstream output;

	input.open("DTMF tones/1209.samples", std::fstream::in);

	if (input.is_open())
	{
		for(i = 0; i < SignalLen; i++)
		{
			input >> x1209[i];
			//cout << i << ": " << x1209[i] << endl;
		}
	}
	else
		cout << "file is not open" << endl;

	input.close();


	convolve(x1209,result);



	
	// write the results to a file
	output.open("c1209.txt");
	for(i = 0; i < MAXLEN; i++)
		output << result[i] << endl;
	output.close();
	
	return 0;
}

// Do the convolution
void convolve(double *signal, double *result)
{
	int k;
	int n;
	int kmax;
	int kmin;
	
	  for (n = 0; n < SignalLen + BL - 1; n++)
	  {
	    result[n] = 0;

	    kmin = (n >= BL - 1) ? n - (BL - 1) : 0;
	    kmax = (n < SignalLen - 1) ? n : SignalLen - 1;

	    for (k = kmin; k <= kmax; k++)
	    {
	      result[n] += signal[k] * B[n - k];
	    }
	  }
}
