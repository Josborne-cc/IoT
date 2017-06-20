/*
Program: Convulution of a DTMF filter to determine the tone
*/

#include <iostream>
#include <vector>
#include <fstream>
#include "1209coefs.h"


using std::cout;
using std::endl;

int main()
{
	int i;
	int j;
	int k;
	double x1209[512];
	double convolve[512 + BL][BL];
	double result[512 + BL];
	std::ifstream input;
	std::ofstream output;

	input.open("DTMF tones/1209.samples", std::fstream::in);

	if (input.is_open())
	{
		for(i = 0; i < 512; i++)
		{
			input >> x1209[i];
			//cout << i << ": " << x1209[i] << endl;
		}
	}
	else
		cout << "file is not open" << endl;

	input.close();
	
	// Do the Convolution
	k = 0;
	for(i = 0; i < BL; i++)
	{
		for(j = 0; j < 512; j++)
		{
			convolve[k+j][i] = B[i] * x1209[j];
		}
		k++;
	}

	// Add up all the products
	for(i = 0; i < 512 + BL; i++)
	{
		for(j = 0; j < BL; j++)
		{
			result[i] += convolve[i][j];
		}
	}

	// Print the Result
	for(i = 0; i < 512 + BL; i++)
		cout << i << ": " << result[i] << endl;
	
	// write the results to a file
	output.open("c1209.txt");
	for(i = 0; i < 512 + BL; i++)
		output << result[i] << endl;
	output.close();
	
	return 0;
}
