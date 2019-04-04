#include "ReadWrite.h"

ReadWrite::ReadWrite(int nr, int nw, int nrand) {
	l = new LLC();
	numReaders = nr;
	numWriters = nw;
	numRandom = nrand;
}
