/* CS261- Assignment 1 - Q.3*/
/* Name: Mario Franco-Munoz
 * Date: 01/14/2018
 * Solution description: This program creates an array of random numbers
 * and then applies a sorting algorithm to sort the values in assending order.
 */

 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

 /*********************************************************************
 ** Function: sort (bubble sort)
 ** Description: This function was taken from the CS 261 class notes. Uses the bubble sort
 ** algorithm to order contents of array in ascending order.
 ** Pre-Conditions: array must be populated with numbers prior to function call.
 ** Post-Conditions: values of array are permanantly re-ordered upon execution of this function.
 *********************************************************************/
void sort(int* number, int n) {
	int temp;				//storage variable since C does not have a built in swap function
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			// data[j] is largest value in 0 .. j
			if (number[j] > number[j + 1]) {
				//swap values
				temp = number[j];
				number[j] = number[j + 1];
				number[j + 1] = temp;
			}
		}
	}
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
	int *arr = (int*)malloc(sizeof(int)*n);

    /*Fill this array with random numbers, using rand().*/
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 100;
	}
    
    /*Print the contents of the array.*/
	printf("Unsorted values stored in array: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

    /*Pass this array along with n to the sort() function of part a.*/
	sort(arr, n);
    
    /*Print the contents of the array.*/    
	printf("Values stored in array (now sorted): ");
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	//deallocate memory
	free(arr);

    return 0;
}
