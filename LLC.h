//Linked List Header
#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node {
	struct Node * next;
	int data;
};

class LLC {
	public:
		LLC();
		~LLC();
		void insert(int);
		void view();
		int getLen();
	private:
		Node *first;
		Node *last;
};
