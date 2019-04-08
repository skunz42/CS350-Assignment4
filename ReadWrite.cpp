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
	sem_init(&rmutex, 0, 1);
	sem_init(&wmutex, 0, 1);
	sem_init(&readTry, 0, 1);
	sem_init(&resource, 0, 1);
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
	
	for(int i = 0; i < this->numRandom; i++){
	
		//Each R reader should inspect the LinkedList N times
		//print number of values ending in R
		//write to file for each R reader
		sem_wait(&readTry);
		sem_wait(&rmutex);
		readcount++;
		if(readcount == 1) {
			sem_wait(&resource);
		}
		sem_post(&rmutex);
		sem_post(&readTry);
		//crit sect
		cout << "reader " << rNum << endl;
		
		int countEnd = this->l->countEnd(rNum);
		cout << "countEnd " << countEnd << endl;
		this->results[rNum-1][i] = countEnd;
		//this->l->view();
		//cout << "Reader " << rNum << ": Read " << i << ": " << countEnd;
	
	
		sem_wait(&rmutex);
		readcount--;
		if(readcount == 0) {
			sem_post(&resource);
		}
		sem_post(&rmutex);
		sleep(1);
		
	}
}

void ReadWrite::writer(int wNum) {
		
	for(int i = 0; i < this->numRandom; i++){
	
		//sleep(1);

		//Each W writer should add N randomly generated numbers to the list
		//Sleep for a few seconds in between writes
		int randNum;
	
		sem_wait(&wmutex);
		writecount++;
		if(writecount == 1) {
			sem_wait(&readTry);
		}
		sem_post(&wmutex);
		
		sem_wait(&resource);
		//crit
		cout << "writer " << wNum << endl;
		
		randNum = rand()%(100) + 1;	
		while(randNum%10 != wNum){
			randNum = rand()%(100) + 1;	
		}
		//cout << randNum << endl;
		this->l->insert(randNum);
		
		this->l->view();
		
	
		//endcrit
		sem_post(&resource);

		sem_wait(&wmutex);
		writecount--;
		if(writecount == 0) {
			sem_post(&readTry);
		}
		sem_post(&wmutex);
		
		//this_thread::sleep_for(std::chrono::milliseconds(3333));
		this_thread::sleep_for(std::chrono::seconds(1));
		
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
