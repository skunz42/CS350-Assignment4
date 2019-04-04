#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include "LLC.h"

using namespace std;

class ReadWrite {
	public:
		ReadWrite(int, int, int);
		void reader();
		void writer();
		void almostDone();
	private:
		LLC *l;
		int numReaders;
		int numWriters;
		int numRandom;

		//From Wikipedia
		int readcount;
		int writecount;
		pthread_mutex_t rmutex;
		pthread_mutex_t wmutex;
		pthread_mutex_t readTry;
		pthread_mutex_t resource;
};
