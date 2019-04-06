#include "ReadWrite.h"

ReadWrite::ReadWrite(int nr, int nw, int nrand) {
	l = new LLC();
	numReaders = nr;
	numWriters = nw;
	numRandom = nrand;
	rmutex = PTHREAD_MUTEX_INITIALIZER;
	wmutex = PTHREAD_MUTEX_INITIALIZER;
}

void * ReadWrite::reader_helper(void * context) {
	((ReadWrite *)context)->reader();
	return NULL;
}

void * ReadWrite::writer_helper(void * context) {
	((ReadWrite *)context)->writer();
	return NULL;
}

void ReadWrite::reader() {
	//Each R reader should inspect the LinkedList N times
	//print number of values ending in R
	//write to file for each R reader
	pthread_mutex_lock(&rmutex);
	cout << "Hello World!" << endl;
	pthread_mutex_unlock(&rmutex);
}

void ReadWrite::writer() {
	//Each W writer should add N randomly generated numbers to the list
	//Sleep for a few seconds in between writes
	pthread_mutex_lock(&wmutex);
	cout << ":^)" << endl;
	pthread_mutex_unlock(&wmutex);
}

void ReadWrite::almostDone() {
	//print out almost done when there is only a single reader list
	//use a condition variable
}
