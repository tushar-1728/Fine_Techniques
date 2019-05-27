#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print(int *arr, int n);

int main(){
	int n, maxlimit, inp;
	int arr_no, bit_no;
	int arr_limit;
	printf("Enter no of elements: ");
	scanf("%d", &n);
	// taking input from user the maximum limit of numbers to be sorted
	// and then calculating the size of the array
	printf("Enter the greatest integer among all the elements(exclusive): ");
	scanf("%d", &maxlimit);
	arr_limit = ceil(maxlimit / 32.00);
	// allocating the array
	int *arr = (int*)calloc(arr_limit, sizeof(int));
	// taking input of numbers to be sorted
	// and then making the corresponding bit 1
	printf("Enter the elements: ");
	for(int i = 0; i < n; ++i){
		scanf("%d", &inp);
		arr_no = inp / 32;  // dividing by 32 decides bit of which array element will be modified
		bit_no = inp % 32;	// modulo by 32 decides which bit of selected array element
		arr[arr_no] |= (1 << bit_no);  // setting the bit 1
	}
	// traversing through the bits to get sorted elements
	for(int i = 0; i < arr_limit; ++i){
		for(int j = 0; j < 32; ++j){
			if(arr[i] & (1 << j)){
				printf("%d ", 32*i+j);
			}
		}
	}
	printf("\n");
}
