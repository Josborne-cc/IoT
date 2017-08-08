/*
Program: Convulution of a DTMF filter to determine the tone
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
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
#define WienerLen 513
#define MAXLEN 1025

void convolve(double *signal, const double *filter, double *result);

int main()
{
	int i;
	bool x697 = false;
	bool x770 = false;
	bool x852 = false;
	bool x941 = false;
	bool x1209 = false;
	bool x1336 =false;
	bool x1477 = false;
	bool x1633 = false;
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
	//std::ofstream myfifo;

	int fd;
	char const * myfifo = "myfifo";

	// Gather the input
	input.open("DTMF tones/dtmf_5.samples", std::fstream::in);

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
	
	
	// Print the Sums
	cout << "s697: " << s697 << endl;
	cout << "s770: " << s770 << endl;
	cout << "s852: " << s852 << endl;
	cout << "s941: " << s941 << endl;
	cout << "s1209: " << s1209 << endl;
	cout << "s1336: " << s1336 << endl;
	cout << "s1477: " << s1477 << endl;
	cout << "s1633: " << s1633 << endl;

	/* create the FIFO (named pipe) */
	//mkfifo(myfifo, 0666);
	//fd = open(myfifo, O_WRONLY);

	

	
	
	// if frequeny is present set true
	if(s697 > 50)
		x697 = true;
	if(s770 > 50)
		x770 = true;
	if(s852 > 50)
		x852 = true;
	if(s941 > 50)
		x941 = true;
	if(s1209 > 50)
		x1209 = true;
	if(s1336 > 50);
		x1336 = true;
	if(s1477 > 50)
		x1477 = true;
	if(s1633 > 50)
		x1633 = true;
	
	// print what tone is present
	if (x697 == true && x1209 == true)
	{
		cout << "The tone is: 1" << endl;
		//write(fd, "1", sizeof("1"));
	}
	if (x770 == true && x1209 == true)
	{
		cout << "The tone is: 4" << endl;
		//write(fd, "4", sizeof("4"));
	}
	if (x852 == true && x1209 == true)
	{
		cout << "The tone is: 7" << endl;
		//write(fd, "7", sizeof("7"));
	}
	if (x941 == true && x1209 == true)
	{
		cout << "The tone is: *" << endl;
		//write(fd, "*", sizeof("*"));
	}
	if (x697 == true && x1336 == true)
	{
		cout << "The tone is: 2" << endl;
		//write(fd, "2", sizeof("2"));
	}
	if (x770 == true && x1336 == true)
	{
		cout << "The tone is: 5" << endl;
	
		mkfifo(myfifo, 0666);
		fd = open(myfifo, O_WRONLY);
		write(fd, "5", sizeof("5"));
		close(fd);
		unlink(myfifo);
cout << "josh" << endl;

	}
	if (x852 == true && x1336 == true)
	{
		cout << "The tone is: 8" << endl;
		//write(fd, "8", sizeof("8"));
	}
	if (x941 == true && x1336 == true)
	{
		cout << "The tone is: 0" << endl;
		//write(fd, "0", sizeof("0"));
	}
	if (x697 == true && x1477 == true)
	{
		cout << "The tone is: 3" << endl;
	}
	if (x770 == true && x1477 == true)
	{
		cout << "The tone is: 6" << endl;
		//write(fd, "6", sizeof("6"));
	}
	if (x852 == true && x1477 == true)
	{
		cout << "The tone is: 9" << endl;
		//write(fd, "9", sizeof("9"));
	}
	if (x941 == true && x1477 == true)
	{
		cout << "The tone is: #" << endl;
		//write(fd, "#", sizeof("#"));
	}



	
	
	

	/* remove the FIFO */
	//close(fd);
	//unlink(myfifo);
	

	
	// write the results to a file
	output.open("c697.txt");
	for(i = 0; i < MAXLEN; i++)
		output << r697[i] << endl;
	output.close();
	output.open("c770.txt");
	for(i = 0; i < MAXLEN; i++)
		output << r770[i] << endl;
	output.close();
	output.open("c852.txt");
	for(i = 0; i < MAXLEN; i++)
		output << r852[i] << endl;
	output.close();
	output.open("c941.txt");
	for(i = 0; i < MAXLEN; i++)
		output << r941[i] << endl;
	output.close();
	output.open("c1209.txt");
	for(i = 0; i < MAXLEN; i++)
		output << r1209[i] << endl;
	output.close();
	output.open("c1336.txt");
	for(i = 0; i < MAXLEN; i++)
		output << r1336[i] << endl;
	output.close();
	output.open("c1477.txt");
	for(i = 0; i < MAXLEN; i++)
		output << r1477[i] << endl;
	output.close();
	output.open("c1633.txt");
	for(i = 0; i < MAXLEN; i++)
		output << r1633[i] << endl;
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
	
	for (n = 0; n < WienerLen + WienerLen - 1; n++)
	{
		result[n] = 0;

		kmin = (n >= WienerLen - 1) ? n - (WienerLen - 1) : 0;
		kmax = (n < SignalLen - 1) ? n : SignalLen - 1;

		for (k = kmin; k <= kmax; k++)
		{
			result[n] += signal[k] * filter[n - k];
		}
	}
}
