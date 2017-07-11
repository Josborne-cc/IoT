/*
Purpose: Server Socket program
 Author: Josh Osborne
*/
#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <fstream>

int main (void)
{
	std::cout << "running....\n";
	std::string data;
	std::string line;
	std::fstream fd;
	int i = 0;

	// Clear the file
	fd.open("flat", std::ios::out);
	fd << data;
	fd.close();

	try
	{
	// Create the socket
		ServerSocket server ( 5000 );

		while ( true )
		{

			ServerSocket soc;
			server.accept ( soc );

			try
			{
				while ( true )
				{
					
					// grab the socket
					soc >> data;
					// output the socket for debug
					std::cout << data << std::endl;
	

					// write to the flat file
					fd.open("flat", std::ios::out | std::ios::app);
					fd << i;
					fd << '%';
					fd << data;
					fd << std::endl;
					
					fd.close();
							
					// read from the flat file
					// This will just grab the current entry but any entry could be grabbed depending on aplication
					// For simplicity I assumed a max of 10 entries I just restarted the program if I got to this it can go much higher 
					fd.open("flat", std::ios::in);
					// assumes max of 10 lines in file
					for (int j = 0; std::getline (fd,line) && j < 10; j++)
					{
						if (j == i)
							soc << line;
					}
					fd.close();

					i++;
					sleep(1);
				}
			}
			catch ( SocketException& ) {}
		}
	}
	catch ( SocketException& e )
	{
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}

	return 0;
}

