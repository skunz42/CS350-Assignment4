#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include "LLC.h"

using namespace std;

class ReadWrite {
	public:
		ReadWrite(int, int, int);
		static void * reader_helper(void *);
		static void * writer_helper(void *);
		void reader();
		void writer();
		void almostDone();
		pthread_mutex_t rmutex;
		pthread_mutex_t wmutex;
	private:
		LLC *l;
		int numReaders;
		int numWriters;
		int numRandom;

		//From Wikipedia - subject to change
		int readcount;
		int writecount;
		pthread_mutex_t readTry;
		pthread_mutex_t resource;
};
