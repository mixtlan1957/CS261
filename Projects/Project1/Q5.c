/* CS261- Assignment 1 - Q.5*/
/* Name: Mario Franco-Munoz
 * Date: 01/17/2018
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

 /*********************************************************************
 ** Function: toUpperCase
 ** Description: converts a character from lower case to upper case 
 ** Parameters: single character to be converted
 ** Pre-Conditions: function does not value check. Ensure input is a letter prior to running.
 *********************************************************************/
/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*********************************************************************
** Function: toLowerCase
** Description: converts a character from upper case to lower case
** Parameters: single character to be converted
** Pre-Conditions: function does not value check. Ensure input is a letter prior to running.
*********************************************************************/
/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

/*********************************************************************
** Function: sticky
** Description: converts input word to sticky notation: sticky becomes StIcKy
** Parameters: single word passed as a c-style string (array of characters)
** Pre-Conditions: single word consiting of only letters must be passed to function
** Post-Consitions: converts word to "sticky" notation
*********************************************************************/
void sticky(char* word){
	int index = 0;
	int endStringIndex = -1;

	//find the length of the string
	while (index < 100 && endStringIndex == -1) {
		if (word[index] == 0) {
			endStringIndex = index;
		}
		index++;
	}

	for (int i = 0; i < endStringIndex; i++) {
		//even indexed characters need to be upper case
		if (i % 2 == 0) {
			//check ascii code (captialized letters are at most 90)
			if (word[i] > 'Z') {
				word[i] = toUpperCase(word[i]);
			}
		}
		//odd indexed characters need to be lower case
		else {
			if (word[i] < 'a') {
				word[i] = toLowerCase(word[i]);
			}
		}
	}


}

int main(){
	//input buffer
	char inputString[100];

    /*Read word from the keyboard using scanf*/
	printf("Please enter a single word.\n");
	scanf("%s", inputString);

    /*Call sticky*/
	sticky(inputString);

    /*Print the new word*/
	printf("\nWord with \"sticky\" modification: %s\n", inputString);


    return 0;
}
