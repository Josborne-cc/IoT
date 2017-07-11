# Makefile for the socket programming example
#

default: test

test: ClientSocket.o Socket.o c.o
	g++ -o test ClientSocket.o Socket.o c.o

c.o: c.cpp
	g++ -c c.cpp

ClientSocket.o: ClientSocket.cpp ClientSocket.h
	g++ -c ClientSocket.cpp

Socket.o: Socket.cpp Socket.h
	g++ -c Socket.cpp

clean:
	rm -f *.o test

