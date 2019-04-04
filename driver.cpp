#include "ReadWrite.h"

void createThreads(ReadWrite *rw, int numReaders, int numWriters) {
	for (int i = 0; i < numReaders; i++) {
		//create reader threads
	}
	for (int i = 0; i < numWriters; i++) {
		//create writer threads
	}
	//create "almost done thread"
}

int main(int argc, char **argv) {
	/*#######################
	  Add in error checking
	#######################*/
	int numRandom = atoi(argv[1]);
	int numReaders = atoi(argv[2]);
	int numWriters = atoi(argv[3]);
	ReadWrite *rw = new ReadWrite (numReaders, numWriters, numRandom);
	createThreads(rw, numReaders, numWriters);
	return 0;
}
