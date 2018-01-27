/*********************************************************************
** Program Filename: circularList.c (Part 2 of Assignment 3)
** Author: Mario Franco-Munoz
** Date: 01/26/2018
** Description: This .c file for the implementation of a circular deque.
** Interface functions for deque include: adding/removing links at front/back.
** Printing values in deque (first to last), reversing order of nodes, initializing deque.
** Printing values held in first/last links.
** Input: values for new elements to be inserted at either front or back.
** Output: List of values stored in the deque (front to back) to I/O.
** First element in deque, single value output to I/O.
** last element in deque, single value output to I/O.
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	list->sentinel = malloc(sizeof(struct Link));
	assert(list->sentinel != NULL);

	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;

	list->size = 0;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link *newLink = malloc(sizeof(struct Link));
	assert(newLink != NULL);
	newLink->value = value;

	newLink->next = NULL;
	newLink->prev = NULL;


	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != NULL);
	
	struct Link *newLink = createLink(value);
	struct Link *temp = link->next;
	
	newLink->next = temp;
	newLink->prev = link;

	link->next = newLink;
	temp->prev = newLink;

	list->size++;

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(list != NULL && list->size > 0);

	struct Link *tempFwd = link->next;
	struct Link *tempBwd = link->prev;
	
	tempFwd->prev = tempBwd;
	tempBwd->next = tempFwd;


	free(link);

	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	assert(list != NULL);

	while (list->size > 0) {
		removeLink(list, list->sentinel->next);
	}

	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	assert(list != NULL);
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	assert(list != NULL);
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert(list != NULL && list->size > 0);

	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(list != NULL && list->size > 0);

	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(list != NULL && list->size > 0);

	removeLink(list, list->sentinel->next);

}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert(list != NULL && list->size > 0);

	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	assert(list != NULL);

	if (list->size > 0) {
		return 0;
	}

	else {
		return 1;
	}
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	assert(list != NULL && list->size > 0);

	int count = 0;
	struct Link *temp = list->sentinel->next;

	printf("Values of the links in the deque from front to back: \n");

	while (count < list->size) {
		printf("%g   ", temp->value);
		temp = temp->next;
		count++;
	}
	printf("\n");

}


/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	assert(list != NULL);

	struct Link *temp;
	struct Link *propigator = list->sentinel->next;

	for (int i = 0; i < list->size; i++) {
		temp = propigator->next;
		propigator->next = propigator->prev;
		propigator->prev = temp;

		propigator = temp;
	}

	temp = list->sentinel->next;
	list->sentinel->next = list->sentinel->prev;
	list->sentinel->prev = temp;

	

	
}
