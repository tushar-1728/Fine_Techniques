# Introduction
- In this memory manager I have taken memory from os using malloc function and then I have maintained book-keeping for the memory that has been allocated.
- You can then further allocate and de-allocate memory using mymalloc and myfree, book-keeping has been taken care for each and every case.
- Mymalloc function allocates memory on the basis of best-fit technique.
# Implementation
- When we call malloc(sizeof(int) * num) for the first time, the os does't exactly gives us (sizeof(int) * num) units of memory, but instead it gives the whole page and then internally in the whole page, (sizeof(int) * num) units of memory gets allocated to us.

- Here allocate function is like allocating page from the os and mymalloc function divides the whole page according to our needs.
```c
extern char *p; // pointer which stores the address of the page.
void allocate(int n); // fundction allocating page of size n bytes long and global variable p is the pointer to that memory

void* mymalloc(int size); //function to allocate a block of size "size" from p

void myfree(void *b); //free the block pointed to by the parameter

// prints bytes required for allocated chunk's bookkeeping followed by bytes required for
// free chunk's bookkeeping on the next line.Can be the same value. For example:
// 4  for allocated chunk
// 10  for free chunk
void print_book();

// prints the memory map of the page allocated
void display_mem_map(); 
// Assume n = 1000
// assume book keeping : 10 bytes for both allocated and free cases
// 
// start_addr   block_in_bytes status
// 0		10		book-keeping
// 10           990             free
// mymalloc(100)
// 0		10		book-keeping	
// 10           100             allocated
// 110		10		book-keeping
// 120          (1000 -120) = 880  free
// mymalloc(200)
// 0		10		book-keeping
// 10           100             allocated
// 110		10		book-keeping
// 120          200             allocated
// 320		10		book-keeping
// 330          670             free
// mymalloc(150)
// 0		10		book-keeping
// 10           100             allocated
// 110		10		book-keeping
// 120          200             allocated
// 320		10		book-keeping
// 330          150             allocated
// 480		10		book-keeping
// 490          510             free
// free(addr 120)
// 0		10		book-keeping
// 10           100             allocated
// 110		10		book-keeping
// 120          200             free
// 320		10		book-keeping
// 330          150             allocated
// 480		10		book-keeping
// 490          510             free
```

# Code to run:
```bash
gcc client.c server.c
```
