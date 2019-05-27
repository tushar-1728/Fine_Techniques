This program implements persistent binary search tree with insertion, deletion preorder and post-order traversal. The output of preorder and post-order traversal is re-directed to file. The program is divided into three parts client file, header file, implementation file.
Header file contains structure for required data types and declarations of all the functions.
Client file contains code for taking input from the user and calls the required functions as when required and also declares the header of the binary tree and also the file pointer referring to the file to which binary tree is written.
Implementation file is the heart of the whole program which contains definition of all the functions.
There are total  functions namely :
1) init_tree
2) close_tree
3) display_preorder
4) disp_preorder
5) display_inorder
6) disp_inorder
7) insert_key
8) delete_key

1) init_tree: Initializes the head of the binary tree and also initializes the pointer referring to the file in which binary tree is written.
2) close_tree: closes the file in which binary tree is written.
3) display_preorder: acts as a wrapper function to call disp_preorder. takes file pointer and head of binary tree as arguments.
4) disp_preorder: this function is called recursively to perform the preorder traversal of binary tree. the function takes output file pointer, binary tree pointer and cursor position as argument.
5) display_inorder: acts as a wrapper function to call disp_preorder. takes file pointer and head of binary tree as arguments.
6) disp_inorder: this function is called recursively to perform the in-order traversal of binary tree. the function takes output file pointer, binary tree pointer and cursor position as argument.
7)insert_key: the head of binary search tree contains two pointers:
	root - pointing to root of binary tree
	free_head - pointing to the head of free locations, free locations are maintained as a linked list, always moving towards the right child
	first it is checked that whether a free position exists or not, if yes variable temp stores that position otherwise temp stores the cursor position corresponding to the end of the file.
	then the new node is inserted to that position.
8) delete_key:
	case 1: first node of binary tree has to be deleted.
		sub-case 1: the root has no child
			the link of root node is cut from the tree and right child of root points to free_head and then free_head points to root
		sub-case 2: the root has right child
			sub-case a: the right child of root does not have any left child
				the left sub-tree of the root is linked to left sub-tree of right child of root and the right child becomes the new root
				right child of old root points to free_head and then free_head points to old root
			sub-case b: the right child of the root has a left child
				then we traverse to the leftmost child of the right child of root
				the right sub-tree of the leftmost child becomes the left sub-tree of the parent of the leftmost child
				now the left sub-tree and right sub-tree of root becomes the left and right sub-tree of this leftmost child and this leftmost child becomes the new root
				right child of old root points to free_head and then free_head points to old root
		sub-case 3: the root does not have a right child and has a left child
			left child of root becomes the new root and old root is added to free_head
		all these changes are written to the .dat file.
	case 2: node to be deleted is not the root node
		sub-case 1: node to be deleted does not have any left and right child
			depending on whether node to be deleted is left or right child of its parent, the parent is modified accordingly.
			right child of deleted node points to free_head and then free_head points to deleted node
		sub-case 2: node to be deleted has a right child
			sub-case a: right child of deleted node does not have any left child
				left sub-tree of the deleted node becomes left sub-tree of right child of node to be deleted
				right child of node to be deleted replaces the deleted node based on whether it is left or right child of its parent
			sub-case b: right child of deleted node has a left child
				right sub-tree of leftmost node(n1) of right child of the node to be deleted becomes left sub-tree of parent of n1
				left and right sub-tree of deleted node becomes left and right sub-tree of n1
		sub-case 3: node to be deleted does not have a right child
			left sub-tree of deleted node replaces the deleted node
