/*
Program: Convulution of a DTMF filter to determine the tone
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "697coefs.h"
#include "770coefs.h"
#include "852coefs.h"
#include "941coefs.h"
#include "1209coefs.h"
#include "1336coefs.h"
#include "1477coefs.h"
#include "1633coefs.h"


using std::cout;
using std::endl;

#define SignalLen 512
#define FilterLen 513
#define MAXLEN 1025

void convolve(double *signal, const double *filter, double *result);

int main()
{
	int i;
	bool x697;
	bool x770;
	bool x852;
	bool x941;
	bool x1209;
	bool x1336;
	bool x1477;
	bool x1633;
	double s697;
	double s770;
	double s852;
	double s941;
	double s1209;
	double s1336;
	double s1477;
	double s1633;
	double r697[MAXLEN];
	double r770[MAXLEN];
	double r852[MAXLEN];
	double r941[MAXLEN];
	double r1209[MAXLEN];
	double r1336[MAXLEN];
	double r1477[MAXLEN];
	double r1633[MAXLEN];
	double signal[SignalLen];
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
	{
		if(r697[i] > 0)
			s697 += r697[i];
		if(r770[i] > 0)
			s770 += r770[i];
		if(r852[i] > 0)
			s852 += r852[i];
		if(r941[i] > 0)
			s941 += r941[i];
		if(r1209[i] > 0)
			s1209 += r1209[i];
		if(r1336[i] > 0)
			s1336 += r1336[i];
		if(r1477[i] > 0)
			s1477 += r1477[i];
		if(r1633[i] > 0)
			s1633 += r1633[i];
	}

	cout << "s697: " << s697 << endl;
	cout << "s770: " << s770 << endl;
	cout << "s852: " << s852 << endl;
	cout << "s941: " << s941 << endl;
	cout << "s1209: " << s1209 << endl;
	cout << "s1336: " << s1336 << endl;
	cout << "s1477: " << s1477 << endl;
	cout << "s1633: " << s1633 << endl;
	

	
	// write the results to a file
	output.open("c1209.txt");
	for(i = 0; i < MAXLEN; i++)
		output << r1336[i] << endl;
	output.close();
	
	return 0;
}

// Convolution Function
void convolve(double *signal, const double *filter, double *result)
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
