/*********************************************************************
** Program Filename: spellChecker.c (Assignment #5)
** Author: Mario Franco-Munoz
** Due Date: 03/11/2018
** Description: THis file reads a dictionary stored in a text file and compares
** user input against words in the dictionary. Words in dictionary are stored in 
** map implemented as a hash table.
**
*********************************************************************/


#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef MIN3
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#endif 



/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXME: implement
	assert(file != NULL);
	assert(map != NULL);

	char *wordIn = NULL;
	//int wordIndex = 0;

	wordIn = nextWord(file);

	while (wordIn != NULL) {
		//wordIn = nextWord(file);
		if (wordIn != NULL) {
			//wordIndex++;
			hashMapPut(map, wordIn, 1);
			free(wordIn);
			wordIn = nextWord(file);
			//free(wordIn);
		}
	}
}


/**
* Computes the Levenshtein Distance
* Source/Citation: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance
* "C"
*/

int LevenshteinDistance(char *s1, char *s2)
{
	int returnVal = 0;

	unsigned int s1len, s2len, x, y, lastdiag, olddiag;
	s1len = strlen(s1);
	s2len = strlen(s2);
	//unsigned int column[s1len + 1];
	unsigned int *column = malloc(sizeof(unsigned int)*(s1len+1));

	//unsigned int column[s1len + 1];
	for (y = 1; y <= s1len; y++)
		column[y] = y;
	for (x = 1; x <= s2len; x++) {
		column[0] = x;
		for (y = 1, lastdiag = x - 1; y <= s1len; y++) {
			olddiag = column[y];
			column[y] = MIN3(column[y] + 1, column[y - 1] + 1, lastdiag + (s1[y - 1] == s2[x - 1] ? 0 : 1));
			lastdiag = olddiag;
		}
	}
	returnVal = (column[s1len]);
	free(column);

	return returnVal;
}






/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
	while (!quit)
	{
		printf("Enter a word or \"quit\" to quit: ");
		scanf("%s", inputBuffer);

		// Implement the spell checker code here..
		HashLink *itr = NULL;	//iterator for combing through "map"
		HashLink *itr2 = NULL;	//iterator for traversing "closeMatches"
		int found = 0;			//bool for detecting if word was spelled correctly
		int diff;				//Levenshtein Distance
		

		//variables for the storage of words that are "close matches"
		HashMap *closeMatches = hashMapNew(5);
		char default1[256]=  "DEFAULT1asdfqwer";
		char default2[256] = "DEFAULT2asdfqwer";
		char default3[256] = "DEFAULT3asdfqwer";
		char default4[256] = "DEFAULT4asdfqwer";
		char default5[256] = "DEFAULT5asdfqwer";
		int alreadyLoaded = 0;
		int hashIndex = 0;
		int itrIndex = 0;
		int index = 0;

		hashMapPut(closeMatches, default1, 99);
		hashMapPut(closeMatches, default2, 99);
		hashMapPut(closeMatches, default3, 99);
		hashMapPut(closeMatches, default4, 99);
		hashMapPut(closeMatches, default5, 99);

		char closeMatchesArr[5][256];
		strcpy(closeMatchesArr[0], default1);
		strcpy(closeMatchesArr[1], default2);
		strcpy(closeMatchesArr[2], default3);
		strcpy(closeMatchesArr[3], default4);
		strcpy(closeMatchesArr[4], default5);



		itr = map->table[0];
		
		while(itrIndex < map->capacity && found == 0) {
			itr = map->table[itrIndex];
			
			if (itr != NULL) {
				while (itr != NULL && found == 0) {
					if (strcmp(itr->key, inputBuffer) == 0) {
						found = 1;
					}
					else {
						alreadyLoaded = 0;
						diff = LevenshteinDistance(itr->key, inputBuffer);
						if (diff < LevenshteinDistance(inputBuffer, closeMatchesArr[0])) {
							strcpy(closeMatchesArr[0], itr->key);
							alreadyLoaded = 1;
						}
						else if (diff < LevenshteinDistance(inputBuffer, closeMatchesArr[1]) && alreadyLoaded != 1) {
							strcpy(closeMatchesArr[1], itr->key);
							alreadyLoaded = 1;
						}
						else if (diff < LevenshteinDistance(inputBuffer, closeMatchesArr[2]) && alreadyLoaded != 1) {
							strcpy(closeMatchesArr[2], itr->key);
							alreadyLoaded = 1;
						}
						else if (diff < LevenshteinDistance(inputBuffer, closeMatchesArr[3]) && alreadyLoaded != 1) {
							strcpy(closeMatchesArr[3], itr->key);
							alreadyLoaded = 1;
						}
						else if (diff < LevenshteinDistance(inputBuffer, closeMatchesArr[4]) && alreadyLoaded != 1) {
							strcpy(closeMatchesArr[4], itr->key);
							alreadyLoaded = 1;
						}
					}
				
					itr = itr->next;
				}
			}
			itrIndex++;
		}
		

	
		if (found == 0) {
			printf("Did you mean... ");
			for (int i = 0; i < 5; i++) {
				printf("%s, ", closeMatchesArr[i]);
			}
			printf("...?\n");
		}
		else {
			printf("Word spelled correctly.\n");
		}

		
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}