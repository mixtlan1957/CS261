/*********************************************************************
** Program Filename: dynamicArray.c
** Author: Mario Franco-Munoz
** Date: 01/20/2018
** Description: this program implements the "Stack" and "Bag" ADT (abstract data types)
** using a dynamic array. Typical interface functions for these two ADTs are implemented
** using a struct containing a dynamic array, size of the ADT, and capacacity of the
** dynamic array.
** Input: pointer to DynArr struct, array indices, and values to add remove elements to/from array.  
** Output: Modified data structure. 
*********************************************************************/


/*	dynamicArray.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include "dynArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;	
}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.		
*/
DynArr* newDynArr(int cap)
{
	assert(cap > 0);
	DynArr *r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/* Deallocate data array in dynamic array. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/* Resizes the underlying array to be the size cap 

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{	
	TYPE *temp = malloc(sizeof(TYPE) * newCap);

	for (int i = 0; i < v->capacity; i++) {
		temp[i] = v->data[i];
	}

	assert(v->data != NULL && v != NULL);
		free(v->data);
		v->capacity = newCap;
		v->data = temp;
}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	assert(v != NULL);
	return v->size;
}

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
	assert(v->data != NULL);
	if (v->size >= v->capacity) {
		_dynArrSetCapacity(v, v->capacity * 2);
	}
	
	v->data[v->size] = val;
	v->size++;
}

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/*	Get an element from the dynamic array from a specified position
	
	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{
	assert(v != NULL);
	assert(v->size > 0);
	assert(pos >= 0 && pos <= v->size - 1);

	return v->data[pos]; 
}

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert 
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	assert(v != NULL);
	assert(v->size > 0);
	assert(pos >= 0 && pos <= v->size - 1);

	v->data[pos] = val;

}

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{
	assert(v != NULL && v->size > 0);
	assert(i >= 0 && i <= v->size - 1 && j >= 0 && j <= v->size - 1);

	TYPE temp = v->data[i];
	v->data[i] = v->data[j];
	v->data[j] = temp;

}

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	assert(v != NULL && v->size > 0);
	assert(idx <= v->size - 1 && idx >= 0);
	
	if (idx < v->size-1) {

		//shift other elements back one to fill the gap
		for (int j = idx; j < v->size - 1; j++) {
			v->data[j] = v->data[j + 1];
		}
		//v->data[v->size - 1] = 0;
	}

	else {
		//v->data[idx] = 0;
	}

	v->size--;

}


/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/*	Returns boolean (encoded in an int) demonstrating whether or not the 
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{
	assert(v != NULL);
	int tempBool = 1;

	if (v->size > 0) {
		tempBool = 0;
	}
	
	return tempBool;
}

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
	assert(v != NULL);

	if (v->size >= v->capacity) {
		_dynArrSetCapacity(v, 2 * v->capacity);
	}

	v->size++;
	v->data[v->size-1] = val;

	
}

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/*	Returns the element at the top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
	
	assert(v != NULL && v->size > 0);

	return v->data[v->size-1];
}

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/* Removes the element on top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArr(DynArr *v)
{
	assert(v != NULL && v->size > 0);

	//v->data[v->size - 1] = 0;

	v->size--;
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
	assert(v != NULL && v->size > 0);
	
	int found = 0;
	int index = 0;

	while (found == 0 && index < v->size) {
		if (EQ(val, v->data[index])) {
			found = 1;
		}
		index++;
	}

	return found;
}

/*****************************************************
*FUNCTION TO BE EDITED/COMPLETED AS PART OF ASSIGNMENT
******************************************************/
/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{
	assert(v != NULL && v->size > 0);
	
	int found = 0;
	int index = 0;

	while (found == 0 && index < v->size) {

		if (EQ(val, v->data[index])) {

			for (int i = index; i < v->size - 1; i++) {
				v->data[i] = v->data[i + 1];
			}
			//v->data[v->size - 1] = 0;
			found = 1;
			v->size--;
		}
		index++;
	}
	
}
