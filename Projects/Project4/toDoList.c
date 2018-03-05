/*********************************************************************
** Program Filename: toDoList.c (Assignment #4)
** Author: Mario Franco-Munoz
** Due Date: 03/06/2018
** Description: this file implements the toDoList functions that allow
** for creating new tasks, saving to do lists, loading to do lists and
** printing to do lists to I/O. "To do lists" must be formatted as: %d\t%s\n
** (integer, tab character, string, newline)
** Output: to do list as heap pointer, I/O to cmd
*********************************************************************/




#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TYPE createTask (int priority, char *desc) 
{
	TYPE newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the 
			task priority, followed by a tab character (\t), and 
			the task description.
			
			The tasks are not necessarily stored in the file in 
			priority order. 
	
*/
void saveList(DynArr *heap, FILE *filePtr)
{
	assert(heap != NULL);
	assert(heap->size > 0);

	for (int i = 0; i < sizeDynArr(heap); i++) {

		TYPE newTask = getDynArr(heap, i);

		fprintf(filePtr, "%d\t%s\n", newTask.priority, newTask.description);
	}

}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
			Refer to the saveList() function for the format of tasks in the file				
*/
void loadList(DynArr *heap, FILE *filePtr)
{
	assert(heap != NULL);

	while (heap->size > 0) {
		removeMinHeap(heap);
	}



	TYPE temp;

	int *priorityIn;
	char *desc[TASK_DESC_SIZE];


	while (fscanf(filePtr, "%d\t%[^\n]s", &priorityIn, &desc)!=EOF) {
		
		
		temp = createTask(priorityIn, desc);
		
		addHeap(heap, temp);

	}

}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
			The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
	DynArr *temp = newDynArr(heap->size);

	copyDynArr(heap, temp);

	printf("\n");
	while(temp->size > 0) {
		
		TYPE output = getMinHeap(temp);

		printf("%d\t%s", output.priority, output.description);
		printf("\n");

		removeMinHeap(temp);
	}
	printf("\n");


	while (temp->size > 0) {
		removeMinHeap(temp);
	}


	free(temp);
	temp = NULL;
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
	ret: 	-1 if priority of left < priority of right
			1 if priority of left > priority of right
			0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
	if (left.priority < right.priority)
		return -1;
	else if (left.priority > right.priority)
		return 1;
	else
		return 0;
}
