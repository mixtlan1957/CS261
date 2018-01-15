/* CS261- Assignment 1 - Q.2*/
/* Name: Mario Franco-Munoz
 * Date: 01/14/2018
 * Solution description: This program demonstrates the difference between passing parameters
 * by value vs passing parameters by reference. 
 */
 
#include <stdio.h>
#include <stdlib.h>

 /*********************************************************************
 ** Function: foo
 ** Description: This function takes two integers parameters by reference, doubles the 
 ** first integer, and divides the second integer by 2. 
 ** Parameters: Three integers a, b, c. (a and b passed by reference, c passed by value)
 ** Pre-Conditions: 
 *********************************************************************/
int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a *= 2;
    
    /*Set b to half its original value*/
	*b /= 2;

    /*Assign a+b to c*/
	c = *a + *b;

    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5;
	int y = 6;
	int z = 7;
	int temp;
    
    /*Print the values of x, y and z*/
	printf("Value of x:      %d\n", x);
	printf("Value of y:      %d\n", y);
	printf("Value of z:      %d\n", z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
	temp = foo(&x, &y, z);

    /*Print the value returned by foo*/
	printf("Value returned by foo:      %d\n", temp);

    /*Print the values of x, y and z again*/
	printf("Value of x:    %d\n", x);
	printf("Value of y:    %d\n", y);
	printf("Value of z:    %d\n", z);
 
    /*Is the return value different than the value of z?  Why?*/
	//Answer: Unlike a and b, z is not passed by reference, but rather by value.
	//Hence a copy of z is passed to the foo function and as such the value returned
	//by foo is not going to be the same as the value of z, which has remained unchanged.
	//(Again because it was passed by value and not by reference).


    return 0;
}
    
    
