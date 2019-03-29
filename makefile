all:	readwrite

readwrite:	LLC.o driver.o
	g++ LLC.o driver.o -o readwrite

LLC.o:	LLC.cpp
	g++ -g -Wall -std=c++11 -c LLC.cpp

driver.o:	driver.cpp
	g++ -g -Wall -std=c++11 -c driver.cpp

clean:
	rm -f *.o readwrite
