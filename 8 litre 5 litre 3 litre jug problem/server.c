#include <stdio.h>
#include <stdlib.h>
#include "header.h"


// functions dealing with insertion and deletion of doubly linked list

void init_list(list_t *ptr_list)
{
	// initailises a doubly linked list by making their haed and tail point to null
	ptr_list->head = NULL;
	ptr_list->tail = NULL;
}

void add_at_end(list_t *ptr_list, const state_t* ptr_state) // adding new node at end

{
	// creating a new node temp
	node_t* temp = (node_t*) malloc(sizeof(node_t));
	// ptr_state is pointer to a state
	// assigning given state *ptr_state to state of temp
	temp->st = *ptr_state;
	// making prev and next of temp point to null
	temp->next = temp->prev = NULL;
	// inserting temp into the doubly linked list

	// if the list is empty
	if(ptr_list->tail == NULL)
	{
		temp->prev = temp->next = NULL;
		ptr_list->head = ptr_list->tail = temp;
	}
	// if list is not empty
	else
	{
		temp->prev = ptr_list->tail;
		temp->next = NULL;
		ptr_list->tail = ptr_list->tail->next = temp;
	}
}
void remove_at_end(list_t *ptr_list) // deleting node from end
{
	// if list is empty
	if(ptr_list->tail == NULL)
	{
		printf("empty list\n");
	}
	// if list is not empty
	else  
	{
		node_t* temp = ptr_list->tail;
		ptr_list->tail = ptr_list->tail->prev;
		// if list has only one node
		if(ptr_list->tail == NULL)
		{
			ptr_list->head = NULL;
		}
		// if list has more than one node
		else
		{
			ptr_list->tail->next = NULL;
		}
		free(temp);		
	}
}
void disp_list(const list_t *ptr_list) // displays the whole list
{
	node_t* temp = ptr_list->head;
	while(temp)
	{
		disp_state(&temp->st);
		temp = temp->next;
	}
}

// checks if *ptr_state has already been part of the given list ptr_list
int is_repeated(const list_t* ptr_list, const state_t* ptr_state)
{
	node_t* temp = ptr_list->head;
	int found = 0;
	while(temp && ! found)
	{
		found  = are_same(&temp->st, ptr_state);
		temp = temp->next;
	}
	return found;
}


// functions dealing with states

void init_state(state_t *ptr_state)
{
	ptr_state->jug_8 = 8;
	ptr_state->jug_5 = 0;
	ptr_state->jug_3 = 0;
	ptr_state->fn_index = 0;
}
void disp_state(const state_t *ptr_state)
{
	printf("%d %d %d\n", ptr_state->jug_8, ptr_state->jug_5, ptr_state->jug_3);
}

void pour_8to5(const state_t *src, state_t *dst){
	// calculating amount of liquid that can be put in jug_5
	// because jug_5 can overflow
	int capacity_5 = 5 - src->jug_5;
	dst->jug_3 = src->jug_3;
	dst->jug_8 = src->jug_8 - capacity_5; // moving capacity_5 from jug_8
	dst->jug_5 = src->jug_5 + capacity_5; // moving capacity_5 to jug_5
	dst->fn_index = 0;
}

void pour_8to3(const state_t *src, state_t *dst){
	// calculating amount of liquid that can be put in jug_3
	// because jug_3 can overflow
	int capacity_3 = 3 - src->jug_3;
	dst->jug_5 = src->jug_5;
	dst->jug_8 = src->jug_8 - capacity_3; // moving capacity_3 from jug_8
	dst->jug_3 = src->jug_3 + capacity_3; // moving capacity_5 to jug_3
	dst->fn_index = 0;
}

void pour_5to8(const state_t *src, state_t *dst)
{
	// jug_8 will never overflow hence no calculation of capacity_8
	dst->jug_3 = src->jug_3;
	dst->jug_8 = src->jug_8 + src->jug_5;
	dst->jug_5 = 0;
	dst->fn_index = 0;
}

void pour_5to3(const state_t *src, state_t *dst){
	// calculating amount of liquid that can be put in jug_3
	// because jug_3 can overflow
	int capacity_3 = 3 - src->jug_3;
	dst->jug_8 = src->jug_8;
	// if jug_5 has more contents than capacity of jug_3
	// example jug_8: 4, jug_5: 4, jug_3: 0
	if(src->jug_5 >= capacity_3){
		dst->jug_5 = src->jug_5 - capacity_3;
		dst->jug_3 = src->jug_3 + capacity_3;
	}
	// if jug_5 has less contents than capacity of jug_3
	// example jug_8: 7, jug_5: 0, jug_3: 1
	else{
		dst->jug_5 = 0;
		dst->jug_3 = src->jug_3 + src->jug_5;
	}
	dst->fn_index = 0;
}

void pour_3to8(const state_t *src, state_t *dst)
{
	// jug_8 will never overflow hence no calculation of capacity_8
	dst->jug_5 = src->jug_5;
	dst->jug_8 = src->jug_8 + src->jug_3;
	dst->jug_3 = 0;
	dst->fn_index = 0;
}

void pour_3to5(const state_t *src, state_t *dst){
	// calculating amount of liquid that can be put in jug_5
	// because jug_5 can overflow
	int capacity_5 = 5 - src->jug_5;
	dst->jug_8 = src->jug_8;
	// if capacity of jug_5 is greater than full capacity of jug_3 ie 3 units
	// then empty all contents of jug_3
	if(capacity_5 >= 3){
		dst->jug_5 = src->jug_5 + src->jug_3;
		dst->jug_3 = 0;
	}
	else{
		// if jug_3 has more contents than capacity_5
		// then transfer only capacity_5 from jug_3 to jug_5
		if(src->jug_3 >= capacity_5){
			dst->jug_5 = src->jug_5 + capacity_5;
			dst->jug_3 = src->jug_3 - capacity_5;
		}
		// if jug_3 has less contents than capacity_5
		// then empty all contents of jug_3
		else{
			dst->jug_5 = src->jug_5 + src->jug_3;
			dst->jug_3 = 0;
		}
	}
}

void set_state(state_t *ptr_state, int jug_8, int jug_5, int jug_3)
{
	ptr_state->jug_8 = jug_8;
	ptr_state->jug_5 = jug_5;
	ptr_state->jug_3 = jug_3;
}

int are_same(const state_t *lhs, const state_t *rhs)
{
	// checks equality of two given states
	return lhs->jug_8 == rhs->jug_8 && lhs->jug_5 == rhs->jug_5 && lhs->jug_3 == rhs->jug_3;
}

void print_to_file(const list_t *ptr_list, FILE *fp){
	node_t* temp = ptr_list->head;
	while(temp)
	{
		fprintf(fp,"%d %d %d\n", temp->st.jug_8, temp->st.jug_5, temp->st.jug_3);
		temp = temp->next;
	}
	fprintf(fp,"\n");
}
