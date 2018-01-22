/*********************************************************************
** Program Filename: stackapp.c
** Author: Mario Franco-Munoz
** Date: 01/20/2018
** Description: This program implements a stack ADT for the purpose of keeping track of
** parenthesis characters to ensure that parenthesis are balanced.
** Input: character input
** Output: status of expression (parenthesis balanced or not)
*********************************************************************/


/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	DynArr *stack = newDynArr(2);
	char tempLoader;
	
	if (s != NULL) {
		tempLoader = nextChar(s);
		while (tempLoader != '\0') {

			//pushes a bracket on to the stack if the character is appropriate
			//only left brackets can push a bracket onto the stack
			if (tempLoader == '{' || tempLoader == '(' || tempLoader== '[') {

				pushDynArr(stack, tempLoader);
			}

			//pops a bracket off the stack if correct character is detected
			//only right brackets can pop a bracket off the stack
			else if (tempLoader == '}' || tempLoader == ')' || tempLoader == ']') {

				if (topDynArr(stack) == '{' && tempLoader == '}') {

					popDynArr(stack);
				}

				else if (topDynArr(stack) == '(' && tempLoader == ')') {

					popDynArr(stack);
				}

				else if (topDynArr(stack) == '[' && tempLoader == ']') {
					
					popDynArr(stack);
				}

			}

			tempLoader = nextChar(s);
		}
	}

	//if expression was balanced, the stack should be empty upon conclusion of the while loop.
	if (isEmptyDynArr(stack)) {
		deleteDynArr(stack);
		return 1;
	}
	else {
		deleteDynArr(stack);
		return 0;
	}

	

}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);

	_CrtDumpMemoryLeaks();
	
	return 0;	
}

