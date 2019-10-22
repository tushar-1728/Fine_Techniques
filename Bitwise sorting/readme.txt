In bitwise sorting I have sorted distinct whole numbers using bits.
The basic idea is as follows:
First I ask the maximum limit of numbers to be sorted, now knowing the max limit of whole numbers and an int data type takes 32 bits on most machines, I have defined an array that on memory has allocated same no of bits as the maximum limit.
Then as the user enters whole numbers the bit of array is made 1. The bit to be made 1 is same as the the entered whole number.
Now the array has a sequence of bits 0 and 1, and if the ith bit is 1 it means the the ith number has been entered by the user.
Now I traversw from 0th bit to last bit and whenever a bit is found 1 then position of that bit is printed.

For example: max limit is 65 and numbers to be sorted are 24, 35, 10, 63
	then size of array will be 3 to get 96 bits (32 bits per element and because 65 is'nt a multiple of 32)
	then 24th, 35th, 10th and 63rd bit of the array will be set to 1
	after that we traverse from position 0, whichever bit is found 1 then that position is printed generating sorted sequence of elements.
