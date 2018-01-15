/* CS261- Assignment 1 - Q.5*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

 /*********************************************************************
 ** Function: 
 ** Description: 
 ** Parameters: 
 ** Pre-Conditions:
 ** Post-Conditions:
 *********************************************************************/
/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*********************************************************************
** Function:
** Description:
** Parameters:
** Pre-Conditions:
** Post-Conditions:
*********************************************************************/
/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

/*********************************************************************
** Function:
** Description:
** Parameters:
** Pre-Conditions:
** Post-Conditions:
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
	scanf("%s", &inputString);

    /*Call sticky*/
	sticky(inputString);

    /*Print the new word*/
	printf("\nWord with \"sticky\" modification: %s\n", inputString);


    return 0;
}
