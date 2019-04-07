#include "ReadWrite.h"

void createThreads(ReadWrite *rw, int numReaders, int numWriters) {
	
	pthread_t rt[numReaders];
	void *rtRetVals[numReaders];

	pthread_t wt[numWriters];
	void *wtRetVals[numWriters];

	int rtcount;
	int wtcount;
///*
	for (wtcount = 0; wtcount < numWriters; wtcount++) {
		//create struct to pass params to thread
 		Param *p = (Param *)malloc(sizeof(Param));
		p->threadNum = wtcount+1;
		p->rw = rw;
		//create writer threads
		pthread_create(&wt[wtcount], NULL, ReadWrite::writer_helper, p);
	}

	//Make reader threads
	for (rtcount = 0; rtcount < numReaders; rtcount++) {
		//create struct to pass params to thread
		Param *p = (Param *)malloc(sizeof(Param));
		p->threadNum = rtcount+1;
		p->rw = rw;
		//create reader threads
		pthread_create(&rt[rtcount], NULL, ReadWrite::reader_helper, p);
	}
//*/	

	//sleep(4);
/*
	//experiment
	for (rtcount = 0; rtcount < numReaders; rtcount++) {
		//create struct to pass params to thread
		Param *p = (Param *)malloc(sizeof(Param));
		p->threadNum = rtcount+1;
		p->rw = rw;
		//create reader threads
		pthread_create(&rt[rtcount], NULL, ReadWrite::reader_helper, p);
		pthread_create(&wt[rtcount], NULL, ReadWrite::writer_helper, p);
	}
*/	
	


	for (int i = 0; i < rtcount; i++) {
		pthread_join(rt[i], &rtRetVals[i]);
	}	
	
	for (int i = 0; i < rtcount; i++) {   // changes wt to rt for experiment
		pthread_join(wt[i], &wtRetVals[i]);
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
	rw->printResults();
	rw->writeToFiles();
	//delete(rw);
	return 0;
}
