/*********************************************************************
** Program Filename: stack_from_queue.c (Part 3 of Assignment 3)
** Author: Mario Franco-Munoz
** Date: 01/27/2018
** Description: this program implments a stack ADT using two queues. Interface functions
** for the stack are the same as a typical stack ADT: push, pop, peek, isEmpty, createStack.
*********************************************************************/

/*
 * This is the file in which you'll write the functions required to implement
 * a stack using two queues.  Make sure to add your name and @oregonstate.edu
 * email address below:
 *
 * Name: Mario Franco-Munoz
 * Email: francomm@oregonstate.edu
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef TYPE
#define TYPE int
#endif  


struct listQueue {
	struct link *sentinel;		//sentinel was added to listQueue data struct so it could be deallocated
	struct link *firstLink;
	struct link *lastLink;
};


struct link {
	struct link *next;
	TYPE value;
};

struct QueueStack {
	struct listQueue *pushQueue;
	struct listQueue *popQueue;
};


//stack functions: interface for client
void push(struct QueueStack*, TYPE);
void pop(struct QueueStack*);
TYPE peek(struct QueueStack*);
int isEmpty(struct QueueStack*);
static struct QueueStack* createStack();
void destroyStack(struct QueueStack *);


//internal QUEUE functions NOT for client use
void listQueueAddBack(struct listQueue *q, TYPE input);
TYPE listQueueFront(struct listQueue *q);
void listQueueRemoveFront(struct listQueue *q);
int listQueueIsEmpty(struct listQueue *q);
struct listQueue* listQueueInit();
void destroyQueue(struct listQueue *q);


//STACK FUNCTIONS

/*
* stack function: destroyStack
* destroyStack takes a stack implemented using two queues and
* deallocates the memory associated with the queues by calling the
* respective queue destroy function and then frees the stack pointer.
* Input: QueueStack pointer.
*/
void destroyStack(struct QueueStack *stack) {
	assert(stack != NULL);
	
	destroyQueue(stack->pushQueue);
	destroyQueue(stack->popQueue);

	free(stack);
}


/*
* stack function: createStack
* This stack function initializes the stack (implemented using two queues).
*/
struct QueueStack* createStack() {
	struct QueueStack *newStack = malloc(sizeof(struct QueueStack));
	assert(newStack != NULL);

	newStack->pushQueue = listQueueInit();
	newStack->popQueue = listQueueInit();

	return newStack;
}

/*
* stack function: push
* "Standard" or typical PUSH stack function. Takes input value and adds
* new value to top of stack. In this case, value is pushed internally to
* queue where new values are being written to.
* Input: input value for new element pushed to stack, pointer to QueueStack
*/
void push(struct QueueStack *stackIn, TYPE inputVal) {
	assert(stackIn != NULL);

	//add new link to back of "push queue"
	listQueueAddBack(stackIn->pushQueue, inputVal);
	

}

/*
* stack function: pop
* "Standard" or typical POP stack function. 
* Using the second queue as for transfer, all elements in the "push" queue are removed and transfered
* to the "pop" queue.
* EXCEPT for the last element (that which is to be poped as per FIFO stack behavior)
* After this "cut and paste," the last remaining element in the first queue is removed.
* And the first (the "push" queue) and the second queue ("pop" queue) swap. Using a simple pointer swap.
* Input: QueueStack pointer
*/
void pop(struct QueueStack *stackIn) {
	

	//pop the element - first transfer all but the last element, then pop it off then transfer it back.;
	
	struct link *temp = stackIn->pushQueue->firstLink->next;
	while (temp != stackIn->pushQueue->lastLink) {

		listQueueAddBack(stackIn->popQueue, temp->value);
		
		listQueueRemoveFront(stackIn->pushQueue);

		temp = stackIn->pushQueue->firstLink->next;
	}
	
	listQueueRemoveFront(stackIn->pushQueue);

	
	//make it so that the "pop queue" is once again empty
	struct listQueue *swaper = stackIn->pushQueue;
	stackIn->pushQueue = stackIn->popQueue;
	stackIn->popQueue = swaper;
	
}

/*
* stack function: isEmpty
* Function returns whether or not the stack is empty.
* Because values are being pushed and stored on the "push queue" the 
* internal queue function "listQueueIsEmpty" is called.
*/
int isEmpty(struct QueueStack *stackIn) {

	if (listQueueIsEmpty(stackIn->pushQueue)) {
		return 1;
	}
	else {
		return 0;
	}

}

/*
* stack function: peek
* Function returns the value stored in the last element added to the stack.
* Output: value stored on the top link on the stack.
*/
TYPE peek(struct QueueStack *stackIn) {

	assert(stackIn != NULL);

	return stackIn->pushQueue->lastLink->value;
}



//QUEUE functions

/*
* queue function: listQueueInit
* This function intializes a listQueue struct prior to being used.
* 
* Output: returns pointer to newly allocated queue struct.
*/
struct listQueue* listQueueInit() {
	struct listQueue *newQueue = malloc(sizeof(struct listQueue));
	assert(newQueue != NULL);
	
	newQueue->sentinel = malloc(sizeof(struct link));
	assert(newQueue->sentinel != 0);
	newQueue->sentinel->next = 0;
	newQueue->firstLink = newQueue->lastLink = newQueue->sentinel;

	return newQueue;
}


/*
* queue function: listQueueAddBack
* Adds a new element with user input value to the back of the queue. 
*
* Input: value to be inserted to the back of queue, pointer to listQueue where
* new element is to be inserted to.
*/
void listQueueAddBack(struct listQueue *q, TYPE e) {
	struct link *newLink = malloc(sizeof(struct link));
	assert(newLink != NULL);

	newLink->value = e;
	newLink->next = NULL;
	
	q->lastLink->next = newLink;

	q->lastLink = newLink;

	assert(q->firstLink != NULL);
}


/*
* queue function: listQueueFront
* Returns the value contained in the element at the front of the queue.
* (this element is queue->firstLink->next.)
* Output: value of user defined type.
*/
TYPE listQueueFront(struct listQueue *q) {

	assert(q->firstLink->next != NULL);

	//return the value the sentinel is pointing to at the
	//front of the queue
	return q->firstLink->next->value;
}


/*
* queue function: listQueueRemoveFront
* Removes the element at the front of the queue. 
*/
void listQueueRemoveFront(struct listQueue *q) {

	assert(q->firstLink->next != NULL);

	struct link *temp = q->firstLink->next;
	

	if (temp->next == NULL) {
		q->firstLink = q->lastLink;
	}
	else {
		q->firstLink->next = temp->next;
	}
	

	free(temp);
	
	assert(q->firstLink->next != NULL);

}

/*
* queue function: listQueueIsEmpty
* Checks for condition in which only the sentinel is left in the queue. In this case
* the first link is the same as the last link (the sentinel).
*
* Output: Returns a 1 if list queue is empty, returns 0 if queue is not empty
*/
int listQueueIsEmpty(struct listQueue *q) {

	if (q->firstLink == q->lastLink) {
		return 1;
	}

	else {
		return 0;
	}
}

/*
* queue function: destroyQueue
* Empties the queue from front to back by calling the listQueueRemoveFront
* function and then frees the memory allocated for the sentinel and the queue struct itself.
* 
*/
void destroyQueue(struct listQueue *q) {
	assert(q != NULL);

	while (!listQueueIsEmpty(q)) {
		listQueueRemoveFront(q);
	}


	//free the sentinel
	free(q->sentinel);

	free(q);

}




int main() {
	
	struct QueueStack *test = createStack();

	printf("Is empty? (value returned at this point should be a 1):  %d\n", isEmpty(test));
	printf("Pushing value to stack.... (1)\n");
	push(test, 1);
	printf("Value at top of stack:  %d\n", peek(test));
	printf("Pushing value to stack.... (2)\n");
	push(test, 2);
	printf("Value at top of stack:  %d\n", peek(test));
	printf("Pushing value to stack.... (3)\n");
	push(test, 3);
	printf("Value at top of stack:  %d\n", peek(test));
	printf("Is empty? (value returned at this point should be a 0):  %d\n", isEmpty(test));

	printf("\nPopping value off the stack... %d\n", peek(test));
	pop(test);
	printf("Value at top of stack:  %d\n", peek(test));	
	


	printf("\nPopping value off the stack... %d\n", peek(test));
	pop(test);
	printf("Value at top of stack:  %d\n", peek(test));

	printf("\nPopping value off the stack... %d\n", peek(test));
	pop(test);

	printf("Is empty? (value returned at this point should be a 1):  %d\n", isEmpty(test));

	destroyStack(test);
	

	return 0;
}