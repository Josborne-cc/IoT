CFLAGS = -Wall -std=c++11

default: FilterTest

FilterTest: FilterTest.o
	g++ $(CFLAGS) -o FilterTest FilterTest.o

FilterTest.o: FilterTest.cpp
	g++ $(CFLAGS) -c FilterTest.cpp

clean:
	$(RM) count *.o *~
