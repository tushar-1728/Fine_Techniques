#include "header.h"

int main()
{
	FILE *fp;
	tree_t t;  // t is the header node of the binary search tree
  // init_tree function initialises the tree
  // mytree.dat - file in which binary search tree is written
	fp = init_tree(&t, "mytree.dat");
	int key;
	int opt;
	printf("Codes to perform operations in persistent binary search tree:\n");
	printf("1: Insertion\n2: Deletion\n3: Inorder traversal\n4: Postorder traversal\n");
	scanf("%d", &opt);
	while(opt)
	{
		switch(opt)
		{
			case 1 : printf("Enter key to insert : ");
					 scanf("%d", &key);
					 insert_key(&t, key, fp);
					 break;
			case 2 : printf("Enter key to delete : ");
					 scanf("%d", &key);
					 delete_key(&t, key, fp);
					 break;
			case 3 : printf("tree begin\n");
					 display_inorder(&t, fp);
					 printf("list end\n");
					 break;
			case 4 : printf("tree begin\n");
					 display_preorder(&t, fp);
					 printf("list end\n");
					 break;
		}
		printf("Enter code : ");
		scanf("%d", &opt);
	}
	close_tree(&t, fp);
}
