#include "LLC.h"

int main(int argc, char **argv) {
	LLC *l = new LLC();
	l->insert(3);
	l->insert(5);
	l->insert(1);
	l->view();
	delete(l);
	return 0;
}
