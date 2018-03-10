/*********************************************************************
** Program Filename: hashMap.c (Assignment #5)
** Author: Mario Franco-Munoz
** Due Date: 03/11/2018
** Description: This file implements a hash map using chaining (or buckets).
** Functionality includes declaring new hash map, removing hash map and deallocating
** associated memory, resising hash map, removing and adding elements.
** 
*********************************************************************/


/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: 
 * Date: 
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement

	struct HashLink *itr;
	struct HashLink *nextItr;


	for (int i = 0; i < map->capacity; i++) {
		itr = map->table[i];
		
		while (itr != NULL) {
			nextItr = itr->next;
			hashLinkDelete(itr);
			itr = nextItr;
		}
	}

	free(map->table);
	map->size = 0;

}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
	// FIXME: implement
	assert(map != NULL);

	int hashIndex = HASH_FUNCTION(key) % map->capacity;
	if (hashIndex < 0) {
		hashIndex += map->capacity;
	}

	struct HashLink *baseLink = map->table[hashIndex];

	while (baseLink != NULL) {
		if (strcmp(baseLink->key, key) != 0) {
			baseLink = baseLink->next;
		}
		else {
			return &(baseLink->value);
		}
	}

	return NULL;

}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 *
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 *
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
	// FIXME: implement
	assert(map != NULL);
	assert(capacity > 0);

	//iter
	struct HashLink *itr = NULL;

	//assign temp map for transfer and assign size
	HashMap *newMap = hashMapNew(capacity);
	assert(newMap != NULL);
	newMap->size = map->size;

	//re-hash links
	for (int i = 0; i < map->capacity; i++) {
		itr = map->table[i];

		while (itr != NULL) {
			hashMapPut(newMap, itr->key, itr->value);
			itr = itr->next;
		}
	}

	hashMapCleanUp(map);
	map->table = newMap->table;
	map->size = newMap->size;
	map->capacity = newMap->capacity;

	free(newMap);
	newMap = NULL;

}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
	// FIXME: implement
	assert(map != NULL);
	assert(key != NULL);

	int hashIndex = HASH_FUNCTION(key) % map->capacity;
	struct HashLink *itr = NULL;
	struct HashLink *prevItr = NULL;
	int found = 0;

	if (hashIndex < 0) {
		hashIndex += map->capacity;
	}
	

	itr = map->table[hashIndex];
	prevItr = itr;

	//there are no links in the bucket we are searching in itr will be NULL
	if (itr == NULL) {
		struct HashLink *newLink = hashLinkNew(key, value, NULL);
		assert(newLink != NULL);
		map->table[hashIndex] = newLink;
		found = 1;
		map->size++;
	}



	while (itr != NULL && found == 0) {
		
		if (strcmp(itr->key, key)==0) {
			itr->value = value;
			found = 1;
		}
		else {
			prevItr = itr;
			itr = itr->next;
		}	
	}

	if (found == 0) {
		struct HashLink *newLink = hashLinkNew(key, value, NULL);
		assert(newLink != NULL);
		prevItr->next = newLink;

		map->size++;
	}


	if (hashMapTableLoad(map) >= MAX_TABLE_LOAD ) {
		resizeTable(map, (map->capacity) * 2);
	}

}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
	assert(map != NULL);
	int hashIndex = HASH_FUNCTION(key) % map->capacity;
	if (hashIndex < 0) {
		hashIndex += map->capacity;
	}

	struct HashLink *itr = NULL;
	struct HashLink *prev = NULL;
	struct HashLink *temp = NULL;
	
	int found = 0;
	
	itr = map->table[hashIndex];

	//link is first linked list element of that array element, no need to manipulate "prev" pointer
	if (strcmp(itr->key, key)== 0) {
		temp = itr->next;

		hashLinkDelete(itr);
		map->table[hashIndex] = temp;
		
		found = 1;

		map->size--;
	}

	while (itr != NULL && found == 0) {
		if (strcmp(itr->key, key) == 0) {
			
			temp = itr->next;
			hashLinkDelete(itr);
			
			prev->next = temp;

			found = 1;

			map->size--;
		}

		else {
			prev = itr;
			itr = itr->next;
		}
	}
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
	assert(map != NULL);
	int hashIndex = HASH_FUNCTION(key) % map->capacity;
	if (hashIndex < 0) {
		hashIndex += map->capacity;
	}

	struct HashLink *itr = NULL;
	
	itr = map->table[hashIndex];

	while (itr != NULL) {
		if (strcmp(itr->key, key) == 0) {
			return 1;
		}
		else {
			itr = itr->next;
		}
		
	}

    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
	assert(map != NULL);

	return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
	assert(map != NULL);

	return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
	assert(map != NULL);
	int count = 0;
	struct HashLink *itr = NULL;

	for (int i = 0; i < map->capacity; i++) {
		itr = map->table[i];
		if (itr == NULL) {
			count++;
		}
	}

	return count;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
	assert(map != NULL);
	assert(map->capacity != 0);
	
	float loadRatio = 0.0;

	loadRatio = ((float)map->size) / ((float)map->capacity);

    return loadRatio;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {

		HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}


