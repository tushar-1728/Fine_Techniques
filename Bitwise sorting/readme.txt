In bitwise sorting I have sorted distinct whole numbers using bits.
The basic idea is as follows:
First I ask the maximum limit of numbers to be sorted, now knowing the max limit of whole numbers and an int data type takes 32 bits on most machines I have defined an array that has same no of bits as the maximum limit.
Then as the user enters whole numbers the bit of array is made 1. The bit to be made 1 is same as the the entered whole number.
Now for getting sorted whole numbers I have traversed from bit 0 and whenever a bit is found 1 then position of that bit is printed.