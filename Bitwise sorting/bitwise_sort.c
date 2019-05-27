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
	int *arr = (int*)calloc(n, sizeof(int));
	printf("Enter the greatest integer among all the elements: ");
	scanf("%d", &maxlimit);
	arr_limit = ceil(maxlimit / 32.00);
	printf("%d\n", arr_limit);
	printf("Enter the elements: ");
	for(int i = 0; i < n; ++i){
		scanf("%d", &inp);
		arr_no = inp / 32;
		bit_no = inp % 32;
		arr[arr_no] |= (1 << bit_no);
	}
	for(int i = 0; i < arr_limit; ++i){
		for(int j = 0; j < 32; ++j){
			if(arr[i] & (1 << j)){
				printf("%d ", 32*i+j);
			}
		}
	}
}
