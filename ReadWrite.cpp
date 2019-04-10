#include "ReadWrite.h"

ReadWrite::ReadWrite(int nr, int nw, int nrand) {
	this->results = new int*[nr];
	for(int i = 0; i < nr; i++){
		results[i] = new int[nrand];
	}	
	srand(std::time(0));	
	l = new LLC();
	numReaders = nr;
	numWriters = nw;
	numRandom = nrand;
	rmutex = PTHREAD_MUTEX_INITIALIZER;
	wmutex = PTHREAD_MUTEX_INITIALIZER;
	readTry = PTHREAD_MUTEX_INITIALIZER;
	resource = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_init(&oneLeft, NULL);
	readcount=0;
	writecount=0;

}

void * ReadWrite::reader_helper(void * context) {
	((Param *)context)->rw->reader(((Param *)context)->threadNum);
	return NULL;
}

void * ReadWrite::writer_helper(void * context) {
	((Param *)context)->rw->writer(((Param *)context)->threadNum);
	return NULL;
}

void ReadWrite::reader(int rNum) {
		
	int randNum;	
	struct timespec tim, tim2;
   	tim.tv_sec =0;
   	tim.tv_nsec = 250000000;
	for(int i = 0; i < this->numRandom; i++){	
		//Each R reader should inspect the LinkedList N times
		//print number of values ending in R
		//write to file for each R reader
		pthread_mutex_lock(&readTry);
		pthread_mutex_lock(&rmutex);
		readcount++;
		if(readcount == 1) {
			pthread_mutex_lock(&resource);
		}
		pthread_mutex_unlock(&rmutex);
		pthread_mutex_unlock(&readTry);
		
		int countEnd = this->l->countEnd(rNum);
		//cout << "countEnd " << countEnd << endl;
		this->results[rNum-1][i] = countEnd;	
		pthread_mutex_lock(&rmutex);
		readcount--;
		if(readcount == 0) {
			pthread_mutex_unlock(&resource);
		}
		pthread_mutex_unlock(&rmutex);
		//sleep(1);
		/*		
		randNum = rand()%(100) + 1;	
		if(randNum <= 20){		
			nanosleep(&tim , &tim2);
		}
		else{
			tim.tv_nsec = 750000000;
			nanosleep(&tim , &tim2);
		}
		*/
		tim.tv_nsec = rand();
		nanosleep(&tim , &tim2);
		
	}
}

void ReadWrite::writer(int wNum) {
	struct timespec tim, tim2;
   	tim.tv_sec = 0;
   	tim.tv_nsec = 250000000;

  	for(int i = 0; i < this->numRandom; i++){
		//Each W writer should add N randomly generated numbers to the list
		//Sleep for a few seconds in between writes
		int randNum;
	
		pthread_mutex_lock(&wmutex);
		writecount++;
		if(writecount == 1) {
			pthread_mutex_lock(&readTry);
		}
		pthread_mutex_unlock(&wmutex);
		
		pthread_mutex_lock(&resource);
		//crit		
		randNum = rand()%(100) + 1;	
		while(randNum%10 != wNum){
			randNum = rand()%(100) + 1;	
		}
		this->l->insert(randNum);
		//endcrit
		pthread_mutex_unlock(&resource);

		pthread_mutex_lock(&wmutex);
		writecount--;
		if(writecount == 0) {
			pthread_mutex_unlock(&readTry);
		}
		pthread_mutex_unlock(&wmutex);
		
		//this_thread::sleep_for(std::chrono::milliseconds(3333));
		//this_thread::sleep_for(std::chrono::seconds(1));
		nanosleep(&tim , &tim2);
		//sleep(2);
	}
}

void ReadWrite::almostDone() {
	//print out almost done when there is only a single reader list
	//use a condition variable
}

void ReadWrite::printResults(){
	for(int i = 0; i < this->numReaders; i++){
		for(int j = 0; j < this->numRandom; j++){
			cout << "Reader " << i+1 << ": Read " << j+1 << ": " << this->results[i][j] << endl;
		}
	}
}

void ReadWrite::writeToFiles(){
	ofstream file;
	ostringstream fileNameBuilder;
	string fileName;
	for(int i = 0; i < this->numReaders; i++){
		//build the file name
		fileNameBuilder << "reader_" << i+1 << ".txt";
		fileName = fileNameBuilder.str();
		// clear the stringStream
		fileNameBuilder.str("");
		fileNameBuilder.clear();
		// openFile
		file.open(fileName);
		// write to file		
		for(int j = 0; j < this->numRandom; j++){
			file << "Reader " << i+1 << ": Read " << j+1 << ": ";
			file << this->results[i][j] << " values ending in " << i+1 << endl;
		}
		// close file
		file.close();
	}
}
