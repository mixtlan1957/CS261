/* CS261- Assignment 1 - Q. 0*/
/* Name: Mario Franco-Munoz
 * Date: 01/13/2018
 * Solution description: This source file contains a function that prints the value to by that of the input
 * pointer, the address pointed to by the input pointer, and the address of the pointer passed to the fooA function
 * itself.
 */
 
#include <stdio.h>
#include <stdlib.h>


 /*********************************************************************
 ** Function: fooA
 ** Description: This function prints the following three items: 1) The value pointed to by 
 ** integer pointer pararmeter. 2) The address pointed to by the integer pointer. 3) Address of the 
 ** integer pointer itself.
 ** Parameters: pointer to an int
 ** Pre-Conditions: Pointer must be created, and point to the address of the integer variable for 
 ** for which the function will operate on - prior to calling the function fooA.
 ** Post-Conditions: None
 *********************************************************************/
void fooA(int* iptr){

	/*Print the value pointed to by iptr*/
	printf("Value pointed to by iptr* :    %p\n", *iptr);
     
     /*Print the address pointed to by iptr*/
	printf("Address pointed to by iptr*:   %p\n", iptr);
     
     /*Print the address of iptr itself*/
	printf("Address of iptr itself:        %p\n", &iptr);
}

int main(){
    
    /*declare an integer x*/
	int x = 7;
	int *iptr = &x;
	

    /*print the address of x*/
	printf("Address of x:                  %p\n", &x);

    /*Call fooA() with the address of x*/
	fooA(iptr);
    
    /*print the value of x*/
	printf("Value of x:                    %d\n", x);
     
    return 0;
}
