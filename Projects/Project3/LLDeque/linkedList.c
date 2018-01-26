/*********************************************************************
** Program Filename: linkedList.c (Assignment #3 Part 1)
** Author: Mario Franco-Munoz
** Date: 01/26/2018
** Description: This file implements a doubly linked list (deque) using a sturct for a node.
** Input: struct LinkedList pointer for data structure initialization. Values for
** creation of subsequent nodes.
** Output: Returns values held in nodes when appropriate return functions are called.
*********************************************************************/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	assert(list != NULL);
	
	list->frontSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != NULL);
	
	list->backSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != NULL);

	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
	
	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	struct Link *newLink = malloc(sizeof(struct Link));
	assert(newLink != NULL);

	struct Link *temp = link->prev;
	temp->next = newLink;
	
	link->prev = newLink;

	//udate new link
	newLink->prev = temp;
	newLink->next = link;
	newLink->value = value;

	list->size++;

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(link != NULL);

	struct Link *tempFwd = link->next;
	struct Link *tempBwd = link->prev;

	tempFwd->prev = tempBwd;
	tempBwd->next = tempFwd;

	list->size--;

	free(link);
}




/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		assert(list->size > 0);
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);
	addLinkBefore(list, list->frontSentinel->next, value);

}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);
	addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list->size > 0);
	return list->frontSentinel->next->value;

}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList *list)
{
	assert(list->size > 0);
	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list->size > 0);
	removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list->size > 0);
	removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList *list)
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
void linkedListPrint(struct LinkedList* list)
{
	struct Link *printTemp = NULL;
	printTemp = list->frontSentinel->next;

	printf("Values in linked list: ");
	for (int i = 0; i < list->size; i++) {
		printf("%d  ", printTemp->value);
		printTemp = printTemp->next;
	}
	printf("\n");
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	assert(list != NULL);
	linkedListAddBack(list, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	int count = 0;
	struct Link *temp = NULL;
	temp = list->frontSentinel->next;
	while (temp->value != value && count < list->size) {
		temp = temp->next;
		count++;
	}

	if (count >= list->size) {
		return 0;
	}
	else {
		return 1;
	}
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	int found = 0;
	int count = 0;
	struct Link *temp = NULL;
	temp = list->frontSentinel->next;

	while (found == 0 && (count < list->size)) {
		if (temp->value == value) {
			removeLink(list, temp);
			found = 1;
		}
		temp = temp->next;
		count++;
	}

}
