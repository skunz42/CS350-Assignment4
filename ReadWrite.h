#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include "LLC.h"
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <sstream>
	
#include <chrono>
#include <thread>

using namespace std;




class ReadWrite {
	public:
		ReadWrite(int, int, int);
		static void * reader_helper(void *);
		static void * writer_helper(void *);
		void reader(int);
		void writer(int);
		void almostDone();
		void printResults();
		void writeToFiles();
		pthread_mutex_t rmutex;
		pthread_mutex_t wmutex;
		pthread_mutex_t readTry;
		pthread_mutex_t resource;
	  
		pthread_cond_t oneLeft;	
	
		int** results;
 
	private:
		LLC *l;
		int numReaders;
		int numWriters;
		int numRandom;

		//From Wikipedia - subject to change
		int readcount;
		int writecount;
		
};




typedef struct {
	int threadNum;
	ReadWrite *rw;
	} Param;
