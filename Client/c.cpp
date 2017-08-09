#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <errno.h>

int main ( int argc, int argv[] )
{
	int fd;
	int tone;
	
	try
	{

		ClientSocket client_socket ( "142.156.193.84", 5000 );

		std::string reply;

		try
		{
			//client_socket << "Test message.";
			fd = open_pipe("/home/josh/IoT/myfifo");
			read_pipe(fd, &tone);
			client_socket << tone;
			client_socket >> reply;
		}
		catch ( SocketException& ) {}

		std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

	}
	catch ( SocketException& e )
	{
	  std::cout << "Exception was caught:" << e.description() << "\n";
	}

	return 0;
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
