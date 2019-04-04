#include "ReadWrite.h"

ReadWrite::ReadWrite(int nr, int nw, int nrand) {
	l = new LLC();
	numReaders = nr;
	numWriters = nw;
	numRandom = nrand;
}

void ReadWrite::reader() {
	//Each R reader should inspect the LinkedList N times
	//print number of values ending in R
	//write to file for each R reader
}

void ReadWrite::writer() {
	//Each W writer should add N randomly generated numbers to the list
	//Sleep for a few seconds in between writes
}

void ReadWrite::almostDone() {
	//print out almost done when there is only a single reader list
	//use a condition variable
}
