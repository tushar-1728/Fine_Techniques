In this memory manager I have taken memory from os using malloc function and then I have maintained book-keeping for the memory that has been allocated.
You can then further allocate and de-allocate memory using mymalloc and free and book-keeping has been taken care for each and every case. Mymalloc function allocates memory on the basis of best-fit technique.

code to run:
gcc client.c server.c
