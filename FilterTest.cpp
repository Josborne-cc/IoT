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

int open_pipe(char *pipe);
int write_pipe(int fd, int *address);
int read_pipe(int fd, int *address);

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

	int tone;
	int fd;
	char pro1[] = "Client";
	int Client_id;


	if(mkfifo("/home/josh/IoT/myfifo", 0666) != 0)
	{
		perror("pipe open error");
		exit(1);
	}
	
	Client_id = create_process(pro1);
	
	printf("Starting Client, Process ID %d\n", Client_id);

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
		tone = 1;
	}
	if (x770 == true && x1209 == true)
	{
		cout << "The tone is: 4" << endl;
		tone = 4;
	}
	if (x852 == true && x1209 == true)
	{
		cout << "The tone is: 7" << endl;
		tone = 7;
	}
	if (x941 == true && x1209 == true)
	{
		cout << "The tone is: *" << endl;
		tone = 42;
	}
	if (x697 == true && x1336 == true)
	{
		cout << "The tone is: 2" << endl;
		tone = 2;
	}
	if (x770 == true && x1336 == true)
	{
		cout << "The tone is: 5" << endl;
		tone = 5;
	}
	if (x852 == true && x1336 == true)
	{
		cout << "The tone is: 8" << endl;
		tone = 8;
	}
	if (x941 == true && x1336 == true)
	{
		cout << "The tone is: 0" << endl;
		tone = 0;
	}
	if (x697 == true && x1477 == true)
	{
		cout << "The tone is: 3" << endl;
		tone = 3;
	}
	if (x770 == true && x1477 == true)
	{
		cout << "The tone is: 6" << endl;
		tone = 6;
	}
	if (x852 == true && x1477 == true)
	{
		cout << "The tone is: 9" << endl;
		tone = 9;
	}
	if (x941 == true && x1477 == true)
	{
		cout << "The tone is: #" << endl;
		tone = 35;
	}



	fd = open_pipe("/home/josh/IoT/myfifo");
	write_pipe(fd, &tone);
	close(fd);
	
	
/*
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
	*/
	
	// Wait for each process to finish
	for(i = 0; i < NUM_CHILDREN; i++)
		wait(NULL);
	
	printf("Shutting Down All Processes!\n");

	unlink("/home/josh/IoT/myfifo");
	
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

/***************open_pipe()****************************************************
Purpose: Open a pipe for communication
Input:   char* pipe - name of pipe to open
Output:  int fd - file descripter to referecnce pipe
******************************************************************************/
int open_pipe(char *pipe)
{
	int fd;

	fd = open(pipe, (O_RDWR));
	if (fd == -1)
	{
		perror("Open Failed");
		exit(1);
	}

	return fd;
}

/*************************write_pipe()*****************************************
Purpose: Write a message to a pipe
Input:   int fd - file descripter of pipe to be written to
	 int *address - address of message to be written
******************************************************************************/
int write_pipe(int fd, int *address)
{
	if(write(fd, address, sizeof(int)) == -1)
		perror("Write Failed");
	return 0;
}



/*******************read_pipe()************************************************
Purpose: Read data from the pipe
Input:   int fd - file descriptor for the pipe
	 int *address - address of the location where the data is to be written
******************************************************************************/
int read_pipe(int fd, int *address)
{
	if(read(fd, address, sizeof(int)) == -1)
		perror("Read Failed");
	return 0;
}

/**********************create_process()****************************************
Purpose: Fork a new process
Input:   char* name - name of the process to be started
******************************************************************************/
int create_process(char *name)
{
	pid_t  pid;
	char path[] = "/home/josh/IoT/Client/";
	char exepath[PATH_LEN] = {0};
	
	//create the file path for exelp
	exepath[0] = '\0';
	strncpy(exepath, path, strlen(path));
	strncat(exepath, name, (strlen(path) + strlen(name)));
	
	
	pid = fork();	//create the child
	//fork failed
	if (pid < 0) 
	{ 
		fprintf(stderr, "Fork Failed");
		exit(-1);
	}
	//child process
	else if (pid == 0) 
	{
		execlp(exepath, name, NULL);
	}
	//parent process
	else 
	{
		//wait (NULL);
		return pid;
		//printf ("Child Complete\n");
		//exit(0);
	}
	return 0;
}
