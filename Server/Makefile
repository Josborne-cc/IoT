# Makefile for the socket programming example
#

default: test

test: ServerSocket.o Socket.o s.o
	g++ -o test ServerSocket.o Socket.o s.o

s.o: s.cpp
	g++ -c s.cpp

ServerSocket.o: ServerSocket.cpp ServerSocket.h
	g++ -c ServerSocket.cpp

Socket.o: Socket.cpp Socket.h
	g++ -c Socket.cpp

clean:
	rm -f *.o test

