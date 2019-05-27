In bitwise sorting I have sorted distinct whole numbers using bits.
The basic idea is as follows:
First I ask the maximum limit of numbers to be sorted, now knowing the max limit of whole numbers and an int data type takes 32 bits on most machines I have defined an array that has same no of bits as the maximum limit.
Then as the user enters whole numbers the bit of array is made 1. The bit to be made 1 is same as the the entered whole number.
Now for getting sorted whole numbers I have traversed from bit 0 and whenever a bit is found 1 then position of that bit is printed.

For example: max limit is 65 and numbers to be sorted are 24, 35, 10, 63
	then size of array will be 3 to get 65 bits or more (32 bits per element)
	then 24th, 35th 10th and 63rd bit of the array will be set
	after that we traverse from position 0, whichever bit is found 1 then that position is printed generating sorted sequence of elements.
