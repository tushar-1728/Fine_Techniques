#include <stdlib.h>
#include <stdio.h>
#include "a.h"

int main(){
	allocate(265);
	void *a = mymalloc(50);
	void *b = mymalloc(30);
	void *c = mymalloc(10);
	void *d = mymalloc(20);
	void *e = mymalloc(75);
	display_mem_map();
	myfree(d);
	display_mem_map();
	myfree(e);
	display_mem_map();
	// myfree(c);
	// display_mem_map();
	// mymalloc(25);
	// display_mem_map();
	free(p);
	return 0;
}