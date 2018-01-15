/* CS261- Assignment 1 - Q.4*/
/* Name: Mario Franco-Munoz
 * Date: 01/14/2018
 * Solution description: This program generates unique random IDs and random scores
 * for a predefined number of student structs. The array of student structs is then
 * sorted by score in ascending order.
 */
 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	int id;
	int score;
};


/*********************************************************************
** Function: sort
** Description: applies bubble sort to the elements in the array of student structs sorted by score.
** code for this bubble sort is based on the code found in the CS 261 class notes.
** Parameters: array of student structs, and number of array elements 
** Pre-Conditions: id and scores need to be populated prior to function call
** Post-Conditions: 
*********************************************************************/
void sort(struct student* students, int n){
	int temp;			//temp int variables for exchanging ids and scores
	int temp2;
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			//swap values if applicable
			if (students[j].score > students[j + 1].score) {
				temp = students[j].score;
				temp2 = students[j].id;
				students[j].score = students[j + 1].score;
				students[j].id = students[j + 1].id;
				students[j+1].score = temp;
				students[j+1].id = temp2;
			}
		}
	}
}

int main(){
    /*Declare an integer n and assign it a value.*/
	int n = 8;				//n represents hte number of students
	int maxID = 10;         //largets generated ID can be
    
    /*Allocate memory for n students using malloc.*/
	struct student *studPtr = malloc(n * sizeof(struct student));

	//the following code is based on the Knuth algorithm as found on stackoverflow post:
	//https://stackoverflow.com/questions/1608181/unique-random-numbers-in-an-integer-array-in-the-c-programming-language
	int im;

	im = 0;

	for (int i = 0; i < maxID && im < n; ++i) {
		int rn = maxID - i;
		int rm = n - im;
		if (rand() % rn < rm)
			/* Take it */
			studPtr[im++].id = i + 1; /* +1 since your range begins from 1 */
	}
	
	//unique random elements shuffled for more complete "randomization" of values
	//using the fisher-yates shuffle as found on:
	//https://www.quora.com/What-is-a-simple-implementation-of-the-Fisher%E2%80%93Yates-shuffle-in-C
	int j, temp;

	for (int i = n - 1; i >= 0; i--) {
		j = rand() % (i + 1);

		temp = studPtr[j].id;
		studPtr[j].id = studPtr[i].id;
		studPtr[i].id = temp;
	}

	//generate random score using rand() for the different students.
	for (int i = 0; i < n; i++) {

		studPtr[i].score = rand() % 101;		//in the range 0 to 100 inclusive
	}


    /*Print the contents of the array of n students.*/
	printf("Unsorted:\n");
	for (int i = 0; i < n; i++) {
		printf("%*d  %d\n", 3, studPtr[i].id, studPtr[i].score);
	}
	printf("\n");

    /*Pass this array along with n to the sort() function*/
	sort(studPtr, n);

    /*Print the contents of the array of n students.*/
	printf("Sorted by score (ascending order): \n");
	for (int i = 0; i < n; i++) {
		printf("%*d  %d\n", 3, studPtr[i].id, studPtr[i].score);
	}

	free(studPtr);
   

    return 0;
}
