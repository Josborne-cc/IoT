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
#define FilterLen 513
#define MAXLEN 1025

void convolve(double *signal, double *filter, double *result);

int main()
{
	int i;
	double sum = 0.0;
	bool x697;
	double signal[512];
	double r697[MAXLEN];
	double r770[MAXLEN];
	double r852[MAXLEN];
	double r941[MAXLEN];
	double r1209[MAXLEN];
	double r1336[MAXLEN];
	double r1477[MAXLEN];
	double r1633[MAXLEN];
	std::ifstream input;
	std::ofstream output;

	// Gather the input
	input.open("DTMF tones/1336.samples", std::fstream::in);

	if (input.is_open())
	{
		for(i = 0; i < SignalLen; i++)
		{
			input >> signal[i];
			//cout << i << ": " << x1209[i] << endl;
		}
	}
	else
		cout << "file is not open" << endl;

	input.close();

	// Complete the convultion
	convolve(signal,f697,r697);
	convolve(signal,f770,r770);
	convolve(signal,f852,r852);
	convolve(signal,f941,r941);
	convolve(signal,f1209,r1209);
	convolve(signal,f1336,r1336);
	convolve(signal,f1477,r1477);
	convolve(signal,f1633,r1633);

	// Check to see if frequency is present
	for(i = 0; i < MAXLEN; i++)
		sum += r1336[i];

	
	// write the results to a file
	output.open("c1209.txt");
	for(i = 0; i < MAXLEN; i++)
		output << result[i] << endl;
	output.close();
	
	return 0;
}

// Convolution Function
void convolve(double *signal, double *filter, double *result)
{
	int k;
	int n;
	int kmax;
	int kmin;
	
	for (n = 0; n < SignalLen + FilterLen - 1; n++)
	{
		result[n] = 0;

		kmin = (n >= FilterLen - 1) ? n - (FilterLen - 1) : 0;
		kmax = (n < SignalLen - 1) ? n : SignalLen - 1;

		for (k = kmin; k <= kmax; k++)
		{
			result[n] += signal[k] * filter[n - k];
		}
	}
}
