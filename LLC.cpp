#include "LLC.h"

LLC::LLC() {
	first = NULL;
	last = NULL;
}

LLC::~LLC() {
	Node * pos = first;
	while (pos != NULL) {
		first = pos->next;
		delete(pos);
		pos = first;
	}
}

void LLC::insert(int num) {
	Node *temp = new Node;
	temp->data = num;
	temp->next = NULL;
	if (first == NULL) {
		first = temp;
		last = temp;
		temp = NULL;
	} else {
		last->next = temp;
		last = temp;
	}
}

void LLC::view() {
	Node *pos = first;
	int count = 0;
	cout << "[";
	while (pos != NULL) {
		if (count < this->getLen()-1) {
			cout << pos->data << ", ";
			count++;
		} else {
			cout << pos->data << "]" << endl;
		}
		pos = pos->next;
	}
}

int LLC::getLen() {
	Node *pos = first;
	int len = 0;
	while (pos != NULL) {
		len++;
		pos = pos->next;
	}
	return len;
}
