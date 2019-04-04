all:	readwrite

readwrite:	LLC.o ReadWrite.o driver.o
	g++ LLC.o ReadWrite.o driver.o -o readwrite

LLC.o:	LLC.cpp
	g++ -g -Wall -std=c++11 -c LLC.cpp

ReadWrite.o:	ReadWrite.cpp
	g++ -g -Wall -std=c++11 -c ReadWrite.cpp

driver.o:	driver.cpp
	g++ -g -Wall -std=c++11 -c driver.cpp

clean:
	rm -f *.o readwrite
