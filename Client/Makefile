# Makefile for the socket programming example
#

default: Client

Client: ClientSocket.o Socket.o c.o
	g++ -std=c++11 -o  Client ClientSocket.o Socket.o c.o

c.o: c.cpp
	g++ -c c.cpp

ClientSocket.o: ClientSocket.cpp ClientSocket.h
	g++ -std=c++11 -c ClientSocket.cpp

Socket.o: Socket.cpp Socket.h
	g++ -std=c++11 -c Socket.cpp

clean:
	rm -f *.o Client

