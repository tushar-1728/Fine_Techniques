#include "header.h"  // including header file

// function to create file to store the binary tree
// if the file exists from previous execution, it reopens for appending
// otherwise it creates a new file.

FILE *init_tree(tree_t *ptr_tree, const char* name)
{
	FILE* fp = fopen(name, "r+");  // if the file exists, opening for both reading and writing
	if(fp == NULL)  // if the file does not exist
	{
		printf("empty file\n");
		fp = fopen(name, "w");   // opening .dat file
		ptr_tree->free_head = -1;  // setting freee_head and root to null
		ptr_tree->root = -1;
		fwrite(ptr_tree, sizeof(tree_t), 1, fp);
		fclose(fp);  // closing the file
		fp = fopen(name, "r+");  // opening the file again, in read-write mode
	}
	fread(ptr_tree, sizeof(tree_t), 1, fp);
	return fp;
}

// function to close the file when the user wants to exit

void close_tree(tree_t *ptr_list, FILE *fp)
{
	fclose(fp);
}

// function to print the binary tree in preorder sequence
// the preorder sequence is re-directed to .txt file and the file is opened in append mode
// display_preorder is a wrapper function which calls the recursive function disp_preorder to print binary search tree in preorder sequence

void display_preorder(const tree_t *ptr_tree, FILE *fp)
{
	int off = ptr_tree->root;  // storing the cursor position of root of binary search tree in off
	FILE *opt = fopen("opt.txt","a");  // the output file is opened in append mode here
	if(off != -1)  // if cursor position of root is not null
	{
		disp_preorder(opt,off,fp);  // calling the recursive function with the cursor position of root node
	}
	fprintf(opt,"\n");
	fclose(opt);  // closing the file
}

void disp_preorder(FILE *opt,int off, FILE * fp)
{
	node_t temp;
	if(off != -1)  // if the cursor position of head is not null
	{
		fseek(fp,off,SEEK_SET);  // setting the cursor to cursor position of head in the .dat file where the binary search tree is stored
		fread(&temp, sizeof(node_t), 1, fp);  // reading the head node in the temp variable
		fprintf(opt,"%d ", temp.key);  // printing the key
		disp_preorder(opt,temp.left_offset, fp);  // calling the recursive function again with the position of left node
		disp_preorder(opt,temp.right_offset, fp);  // calling the recursive function again with the position of right node
	}
}

// function to print the binary tree in in-order sequence
// the in-order sequence is re-directed to .txt file and the file is opened in append mode
// display_inorder is a wrapper function which calls the recursive function disp_inorder to print binary search tree in in-order sequence

void display_inorder(const tree_t *ptr_tree, FILE *fp)
{
	int off = ptr_tree->root;  // storing the cursor position of root of binary search tree in off
	FILE *opt = fopen("opt.txt","a");  // the output file is opened in append mode here
	if(off != -1)  // if the cursor position of root is not null
	{
		disp_inorder(opt,off,fp);  // calling the recursive function with the cursor position of root node
	}
	fprintf(opt,"\n");
	fclose(opt);  // closing the file
}

void disp_inorder(FILE *opt, int off, FILE *fp)
{
	node_t temp;
	if(off != -1)  // if the position of head node is not null
	{
		fseek(fp,off,SEEK_SET);// setting the cursor to cursor position of head in the .dat file where the binary search tree is stored
		fread(&temp, sizeof(node_t), 1, fp);  // reading the head node in the temp variable
		disp_inorder(opt,temp.left_offset, fp);  // calling the recursive function again with the position of left node
		fprintf(opt,"%d ", temp.key);  // printing the key
		disp_inorder(opt,temp.right_offset, fp);  // calling the recursive function again with the position of right node
	}
}

void insert_key(tree_t *ptr_tree, int key, FILE *fp)
{ 	
	node_t temp_node;
	int temp;
	if(ptr_tree->free_head == -1)  // if no node is free
	{
		// cursor position corresponding to end of file is stored in temp so that new node can be written there.
		fseek(fp, 0, SEEK_END);
		temp = ftell(fp);
	}
	else
	{
		temp = ptr_tree->free_head;  // temp stores the position of the first free node i.e position for next node to be stored
		fseek(fp, temp, SEEK_SET);  // cursor is set to the position of first free node
		fread(&temp_node, sizeof(node_t), 1, fp);  // first free node is read into temp_node
		ptr_tree->free_head = temp_node.right_offset;  // free_head now stores the cursor position of next free node
	}

	temp_node.key = key;
	temp_node.left_offset = -1;
	temp_node.right_offset = -1;
	if(ptr_tree->root == -1)  // inserting the first node
	{
		// temp stores position of the cursor corresponding to the end of the file, that position is stored to root of ptr_tree
		ptr_tree->root = temp;
		fseek(fp, 0, SEEK_SET);
		fwrite(ptr_tree, sizeof(tree_t), 1, fp);  // header node of binary search tree is written to .dat file
		fseek(fp, temp, SEEK_SET);
		fwrite(&temp_node, sizeof(node_t), 1, fp);  // new node is written to .dat file
	}
	else
	{
		int prev = -1;  // cursor position of prev_node in .dat file
		int pres = ptr_tree->root;  // cursor position of pres_node in the .dat file
		node_t pres_node; node_t prev_node;
		fseek(fp, pres, SEEK_SET);
		fread(&pres_node, sizeof(node_t), 1, fp);  // reading the first node of binary search tree
		// flag denotes if the key user wants to store in the tree is already a part of tree or not
		// 1 - not part of tree
		// 0 - part of tree
		int flag = 1;
		while(pres != -1 && flag)  // finding the position of the key to be inserted
		{
			prev = pres;
			prev_node = pres_node;
			if(key == pres_node.key)  // if the key already exists in the tree, it is not inserted again
			{
				flag = 0;
			}
			else if(key < pres_node.key)  // if the key is less going to the left node
			{
				pres = pres_node.left_offset;  // storing the cursor position of the left node
			}
			else if(key > pres_node.key)  // if the key is large going to the right node
			{
				pres = pres_node.right_offset;  // storing the cursor position of the right node
			}
			if(pres != -1 && flag)  // if the pres_node exists
			{	
				fseek(fp, pres, SEEK_SET);  // setting the cursor position to pres_node location
				fread(&pres_node, sizeof(node_t), 1, fp);  // reading the pres_node
			}
		}
		// temp stores the cursor position of newly inserted node
		if(flag && key > prev_node.key)
		{
			prev_node.right_offset = temp;
		}
		else if(flag && key < prev_node.key)
		{
			prev_node.left_offset = temp;
		}
		if(flag)
		{
			fseek(fp, prev, SEEK_SET);
			fwrite(&prev_node, sizeof(node_t), 1, fp);  // updating the leaf node to which the new node is inserted
			fseek(fp, 0, SEEK_SET);
			fwrite(ptr_tree, sizeof(tree_t), 1, fp);  // updating the header node of the tree
			fseek(fp, temp, SEEK_SET);
			fwrite(&temp_node, sizeof(node_t), 1, fp);  // writing the new node
		}	
	}
}

// prints -1 if tree does not exist
// if the key is present deletes it otherwise does nothing
void delete_key(tree_t *ptr_tree, int key, FILE *fp)
{
	// tree does not exist
	if(ptr_tree->root == -1)
	{
		FILE *opt = fopen("opt.txt","a");
		fprintf(opt,"%d\n", -1);
		fclose(opt);
	}
	// tree exists
	else
	{
		int prev = -1;  // prev stores the cursor position of prev_node in .dat file
		int pres = ptr_tree->root;  // pres stores the cursor position of pres_node in .dat file
		node_t pres_node; node_t prev_node;
		fseek(fp, pres, SEEK_SET);  // setting the cursor to the position of first node of binary tree
		fread(&pres_node, sizeof(node_t), 1, fp);  // reading the first node
		while(pres != -1 && pres_node.key != key)  // finding the node with given key
		{
			prev = pres;
			prev_node = pres_node;
			if(key < pres_node.key)
			{
				pres = pres_node.left_offset;
			}
			else if(key > pres_node.key)
			{
				pres = pres_node.right_offset;
			}
			if(pres != -1)
			{	
				// storing the present node in pres_node
				fseek(fp, pres, SEEK_SET);
				fread(&pres_node, sizeof(node_t), 1, fp);
			}
		}
		if(pres_node.key != key) // node not found
		{
			printf("-1\n");
		}
		if(pres_node.key == key) // node found
		{
			if(prev == -1) // the node to be deleted is the root
			{
				// root node does not have any child
				if(pres_node.left_offset == -1 && pres_node.right_offset == -1)
				{
					ptr_tree->root = -1;
				}
				// root node has a right child
				else if(pres_node.right_offset != -1)
				{
					// c_node stores the leftmost child of right child of the root at the end of while loop
					// curr_offset stores the cursor position of c_node
					// p_node is supposed to store just the previous node with respect to c_node
					// prev_offset stores the cursor position of p_node
					node_t c_node; node_t p_node;
					int curr_offset; int prev_offset = -1;
					curr_offset = pres_node.right_offset;
					fseek(fp,curr_offset,SEEK_SET);
					fread(&c_node,sizeof(node_t),1,fp);
					while(c_node.left_offset != -1)  // while loop for going to the leftmost node of right child of root
					{
						p_node = c_node;
						prev_offset = curr_offset;
						curr_offset = c_node.left_offset;
						fseek(fp,curr_offset,SEEK_SET);
						fread(&c_node,sizeof(node_t),1,fp);
					}
					if(prev_offset == -1)  // the right child of the root does not have any left child
					{
						// since right child of root does not have any left child hence left sub-tree of root
						// becomes the left sub-tree of right child of root
						c_node.left_offset = pres_node.left_offset;
						fseek(fp, curr_offset, SEEK_SET); // the above said changes are written to the .dat file here
						fwrite(&c_node, sizeof(node_t), 1, fp);
						// the right child of root becomes the new root node and is written to file at the end of delete function
						ptr_tree->root = pres_node.right_offset;
					}
					else // the right child of root has a left child
					{
						// right sub-tree of leftmost node is made left sub-tree of parent of the leftmost node
						p_node.left_offset = c_node.right_offset;
						// right and left sub-tree of root is become right and left sub-tree of the leftmost node
						c_node.right_offset = pres_node.right_offset;
						c_node.left_offset  = pres_node.left_offset;
						// here above mentioned changes are written to .dat file here
						fseek(fp,prev_offset,SEEK_SET);
						fwrite(&p_node, sizeof(node_t), 1, fp);
						fseek(fp,curr_offset,SEEK_SET);
						fwrite(&c_node, sizeof(node_t), 1, fp);
						ptr_tree->root = curr_offset;
						// read the read-me file for more description
					}
				}
				// root does not have a right child
				else if(pres_node.right_offset == -1)
				{
					// left child of root becomes the new root
					ptr_tree->root = pres_node.left_offset;
				}
				// right child of old root is made to point to free_head and then free_head points to old root
				pres_node.right_offset = ptr_tree->free_head;
				ptr_tree->free_head = pres;
				// here above mentioned changes are written to .dat file here
				fseek(fp, 0, SEEK_SET);
				fwrite(ptr_tree, sizeof(tree_t), 1, fp);
				fseek(fp, pres, SEEK_SET);
				fwrite(&pres_node, sizeof(node_t), 1, fp);
			}
			else // anywhere else
			{
				if(pres_node.left_offset == -1 && pres_node.right_offset == -1) // deletion of leaf node
				{
					// child node of parent is made null depending on whether left child or right child is deleted
					if(pres_node.key < prev_node.key)
					{
						prev_node.left_offset = -1;
						fseek(fp,prev,SEEK_SET);
						fwrite(&prev_node, sizeof(node_t), 1, fp);
					}
					else
					{
						prev_node.right_offset = -1;
						fseek(fp,prev,SEEK_SET);
						fwrite(&prev_node, sizeof(node_t), 1, fp);
					}
					// right child of the deleted node points to free_head
					pres_node.right_offset = ptr_tree->free_head;
					// free_head then points to the deleted node
					ptr_tree->free_head = pres;
					// here above mentioned changes are written to .dat file here
					fseek(fp, 0, SEEK_SET);
					fwrite(ptr_tree, sizeof(tree_t), 1, fp);
					fseek(fp, pres, SEEK_SET);
					fwrite(&pres_node, sizeof(node_t), 1, fp);
				}
				else if(pres_node.right_offset != -1) // deletion of node having right child
				{
					// c_node stores the leftmost child of right child of the node to be deleted at the while loop
					// curr_offset stores the cursor position of c_node
					// p_node is supposed to store just the previous node with respect to c_node
					// prev_offset stores the cursor position of p_node
					node_t c_node; node_t p_node;
					int curr_offset; int prev_offset = -1;
					curr_offset = pres_node.right_offset; // cursor position of right child of the node to be deleted is stored in curr_offset
					fseek(fp,curr_offset,SEEK_SET);
					fread(&c_node,sizeof(node_t),1,fp); // right child of the node to be deleted is read into c_node
					while(c_node.left_offset != -1) // finding the leftmost child of right child of node to be deleted
					{
						p_node = c_node;
						prev_offset = curr_offset;
						curr_offset = c_node.left_offset;
						fseek(fp,curr_offset,SEEK_SET);
						fread(&c_node,sizeof(node_t),1,fp);
					}
					if(prev_offset == -1) // right child of node to be deleted does not have a left child
					{
						// left sub-tree of the node to be deleted becomes left sub-tree of right child of node to be deleted
						c_node.left_offset = pres_node.left_offset;
						// right child of node to be deleted replaces the deleted node based on whether it is left or right child of its parent
						if(pres_node.key > prev_node.key)
						{
							prev_node.right_offset = curr_offset;
						}
						else
						{
							prev_node.left_offset = curr_offset;
						}
						// here above mentioned changes are written to .dat file here
						fseek(fp,curr_offset,SEEK_SET);
						fwrite(&c_node, sizeof(node_t), 1, fp);
						fseek(fp,prev,SEEK_SET);
						fwrite(&prev_node, sizeof(node_t), 1, fp);
					}
					else // right child of node to be deleted has a left child
					{
						// c_node - leftmost node of right child of the node to be deleted
						// p_node - parent of c_node
						// read read-me file for explanation
						p_node.left_offset = c_node.right_offset;
						c_node.left_offset = pres_node.left_offset;
						c_node.right_offset = pres_node.right_offset;
						if(pres_node.key > prev_node.key)
						{
							prev_node.right_offset = curr_offset;
						}
						else
						{
							prev_node.left_offset = curr_offset;
						}
						fseek(fp,prev_offset,SEEK_SET);
						fwrite(&p_node, sizeof(node_t), 1, fp);
						fseek(fp,curr_offset,SEEK_SET);
						fwrite(&c_node, sizeof(node_t), 1, fp);
						fseek(fp,prev,SEEK_SET);
						fwrite(&prev_node, sizeof(node_t), 1, fp);
					}
				}
				else if(pres_node.right_offset == -1) // deletion of node not having right child
				{
					// deleted node is replaced by its left sub-tree
					if(pres_node.key > prev_node.key)
					{
						prev_node.right_offset = pres_node.left_offset;
						fseek(fp, prev, SEEK_SET);
						fwrite(&prev_node, sizeof(node_t), 1, fp);
					}
					else if(pres_node.key < prev_node.key)
					{
						prev_node.left_offset = pres_node.left_offset;
						fseek(fp, prev, SEEK_SET);
						fwrite(&prev_node, sizeof(node_t), 1, fp);
					}
				}
				pres_node.right_offset = ptr_tree->free_head;
				ptr_tree->free_head = pres;
				fseek(fp, 0, SEEK_SET);
				fwrite(ptr_tree, sizeof(tree_t), 1, fp);
				fseek(fp, pres, SEEK_SET);
				fwrite(&pres_node, sizeof(node_t), 1, fp);
			}
		}
	}
}