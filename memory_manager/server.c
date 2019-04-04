#include <stdio.h>
#include <stdlib.h>
#include "a.h"

typedef struct header{
	unsigned size;
	char status;
	struct header *next;
}Header;

char * p;

void allocate(int n){
	Header *freeptr;
	p = (char*)malloc(sizeof(char)*n);
	freeptr = (Header*)p;
	freeptr->size = n - sizeof(Header);
	freeptr->status = 0;
	freeptr->next = NULL;
}

void display_mem_map(){
	Header *head = (Header*)p;
	unsigned long long start_addr;
	while(head){
		start_addr = (unsigned long long)head - (unsigned long long)p;
		printf("%6llu %6llu \t book\n", start_addr, sizeof(Header));
		start_addr = (unsigned long long)(head+1) - (unsigned long long)p;
		if(head->status == 0){
			printf("%6llu %6llu \t free\n", start_addr, head->size);
		}
		else{
			printf("%6llu %6llu \t allocated\n", start_addr, head->size);
		}
		head = head->next;
	}
	printf("\n\n");
}

void* mymalloc(int size){
	Header *curr = (Header*)p;
	Header *mem_block = NULL;
	int diff = INT_MAX;
	int temp_diff;
	while(curr){
		temp_diff = curr->size - size;
		if((temp_diff < diff) && (temp_diff >= 0) && (curr->status == 0)){
			diff = temp_diff;
			mem_block = curr;
		}
		curr = curr->next;
	}
	if(mem_block){
		if((mem_block->size - size) <= sizeof(Header)){
			mem_block->status = 1;
		}
		else{
			Header *temp = mem_block->next;
			int mem_size = mem_block->size;
			mem_block->status = 1;
			mem_block->size = size;
			mem_block->next = (Header*)((char*)(mem_block + 1) + size);
			mem_block->next->status = 0;
			mem_block->next->size = mem_size - size - sizeof(Header);
			mem_block->next->next = temp;
		}
		return (void*)(mem_block+1);
	}
	return NULL;
}

void myfree(void *b){
	Header *prev = NULL;
	Header *curr = (Header*)p;
	while(curr && (curr + 1) != b){
		prev = curr;
		curr = curr->next;
	}
	if(curr){
		if(prev == NULL){
			if(curr->next != NULL){
				if(curr->next->status == 1){
					curr->status = 0;
				}
				else{
					curr->status = 0;
					curr->size += curr->next->size;
					curr->next = curr->next->next;
				}
			}
			else{
				curr->status = 0;
			}
		}
		else if(curr->next == NULL){
			if(prev->status == 0){
				prev->size += (curr->size + sizeof(Header));
				prev->next = NULL;
			}
			else{
				curr->status = 0;
			}
		}
		else if(prev->status == 1 && curr->next->status == 1){
			curr->status = 0;
		}
		else if(prev->status == 1 && curr->next->status == 0){
			curr->status = 0;
			curr->size += (curr->next->size + sizeof(Header));
			curr->next = curr->next->next;
		}
		else if(prev->status == 0 && curr->next->status == 1){
			prev->size += (curr->size + sizeof(Header));
			prev->next = curr->next;
		}
		else if(prev->status == 0 && curr->next->status == 0){
			prev->next = curr->next->next;
			prev->size += (curr->size + curr->next->size + 2*sizeof(Header));
		}
	}
}

void print_book(){
	printf("free chunk bookkeeping: %d\n", sizeof(Header));
	printf("allocated chunk bookkeeping: %d\n", sizeof(Header));
}