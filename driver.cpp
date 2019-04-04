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
	int numRandom = atoi(argv[1]);
	int numReaders = atoi(argv[2]);
	int numWriters = atoi(argv[3]);
	if (numRandom < 1 || numRandom > 1000) {
		cout << "Input a number in the range 1-1000" << endl;
		return 1;
	}
	if (numReaders < 1 || numReaders > 9) {
		cout << "Input a number in the range 1-9" << endl;
		return 1;
	}
	if (numWriters < 1 || numWriters > 9) {
		cout << "Input a number in the range 1-9" << endl;
		return 1;
	}

	ReadWrite *rw = new ReadWrite (numReaders, numWriters, numRandom);
	createThreads(rw, numReaders, numWriters);
	delete(rw);
	return 0;
}
