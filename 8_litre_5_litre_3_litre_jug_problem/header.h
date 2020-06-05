#include <stdio.h>
#include <stdlib.h>

struct state // defines every component of a state
{
	int jug_8; // # of units of liquid in 8 litre jug
	int jug_5; // # of units of liquid in 5 litre jug
	int jug_3; // # of units of liquid in 3 litre jug

	// implementation field
	int fn_index;
};
typedef struct state state_t;


struct node // structure of node of doubly linked list
{
	state_t st; // states
	struct node *next;
	struct node *prev;
};
typedef struct node node_t;
struct list  // a doubly linked list and its head and tail
{
	node_t* head;
	node_t* tail;
};
typedef struct list list_t;


void init_list(list_t *ptr_list);

void add_at_end(list_t *ptr_list, const state_t* ptr_state);
void remove_at_end(list_t *ptr_list);

void disp_list(const list_t *ptr_list);

int is_repeated(const list_t* ptr_list, const state_t* ptr_state);

void print_to_file(const list_t *ptr_list, FILE *fp);


void init_state(state_t *ptr_state); // initialises a given state
void disp_state(const state_t *ptr_state); // displays a given state
void set_state(state_t *ptr_state, int jug_8, int jug_5, int jug_3); // sets the state variables with given inputs

void pour_8to5(const state_t *src, state_t *dst);
void pour_8to3(const state_t *src, state_t *dst);
void pour_5to8(const state_t *src, state_t *dst);
void pour_5to3(const state_t *src, state_t *dst);
void pour_3to8(const state_t *src, state_t *dst);
void pour_3to5(const state_t *src, state_t *dst);

int are_same(const state_t *lhs, const state_t *rhs); // checks equality of two given states
