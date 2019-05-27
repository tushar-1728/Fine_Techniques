#ifndef a4_h
#define a4_h
#include <stdio.h>
#include <stdlib.h>

struct node  // structure corresponding to node of binary search tree
{
	int key;
	int left_offset;
	int right_offset;
};
typedef struct node node_t;

struct tree  // structure corresponding to header of binary search tree
{
	int free_head;
	int root;
};
typedef struct tree tree_t;

FILE* init_tree(tree_t*, const char* name);

void close_tree(tree_t *, FILE *fp);

void display_inorder(const tree_t *ptr_tree, FILE *fp);
	// Space separated keys. Last key followed by '\n'
void disp_inorder(FILE *fp_opt, int off, FILE *fp);

void display_preorder(const tree_t *ptr_tree, FILE *fp);
	// Space separated keys. Last key followed by '\n'
void disp_preorder(FILE *fp_opt, int off, FILE * fp);

void insert_key(tree_t *ptr_tree, int key, FILE *fp);

void delete_key(tree_t *ptr_tree, int key, FILE *fp);

#endif
