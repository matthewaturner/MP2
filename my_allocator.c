/* 
    File: my_allocator.c

    Author: Matthew Turner, Ryan Meyers
            Department of Computer Science
            Texas A&M University
    Date  : <date>

    Modified: 

    This file contains the implementation of the module "MY_ALLOCATOR".

*/

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "my_allocator.h"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

header **free_list;
header *head;
int free_list_size;

/*--------------------------------------------------------------------------*/
/* FUNCTIONS FOR MODULE MY_ALLOCATOR */
/*--------------------------------------------------------------------------*/

/* Don't forget to implement "init_allocator" and "release_allocator"! */

unsigned int init_allocator(unsigned int bbs, unsigned int M)
{
  /* Initialize total mem size and free_list */
	
	// allocate free_list space, don't need space for 2, 4, 8 byte lists
	free_list = (header **)calloc((int)log2(M)-3, sizeof(header *));
	// allocate actual memory
	head = (header *)malloc(M);
	// set header attributes for whole memory block
	head->size = M;
	head->next = NULL;
	// set largest block list pointer to the whole memory allocated
	free_list[block_index(M)] = head;
	// store size of free_list
	free_list_size = (int)log2(M)-3;
	
	printf("Head pointer: %p\n", head);
	return 0;
}

int release_allocator() 
{
	free(free_list);
	free_list_size = 0;
	free(head);
	return 0;
}

extern Addr my_malloc(unsigned int _size) 
{
  /* Returns the address of a block of memory guaranteed to be at least
     as large as _size
  */
	// find min power of two to return
	int block_size = block_needed(_size);
	// index of the block we need in free_list
	int i = block_index(block_size);
	
	// ::::: need to error check for i=-1 (returned when block_size too big)
	
	// until we find a block of at least block_size, increase the index
	while(i < free_list_size && free_list[i] == NULL)
		i++;

	// ::::: need to error check to make sure there is space at all in the free_list

	// split blocks starting with i until we have a block of size block_size
	split(i, block_size);
	
	// free_list[i] will now have a block of correct size
	i = block_index(block_size);
	// store pointer to block
	header *temp = free_list[i];
	// remove the block we are returning from the free_list of that size
	free_list[i] = temp->next;
	// add 8 to the pointer returned so data doesn't overwrite block header
	return (void *)(temp + 1);
}

void split(int i, int block_size)
{
	header *left, *right;
	int size;

	while( (free_list[i])->size != block_size) {
		size = free_list[i]->size;
		left = free_list[i];
		left->size = size/2;
		// cast to a char before doing arithmetic
		right = (header*)((char *)left+size/2);
		right->size = size/2;

		free_list[i] = left->next;
		left->next = right;
		right->next = NULL;

		free_list[i-1] = left;
		i--;
	}
}

unsigned int block_needed(unsigned int _size) 
{
  /* Size of the block needed (smallest power of two the size fits in) */

	// minimum useful block size is 16 bytes bc header is 8 bytes
	int i=4;
	// subtract 8 to account for the header
	while(pow(2, i)-8 < _size)
		i++;
	return pow(2, i);
}

int block_index(unsigned int _size)
{
  /* Returns the index of the list of given size blocks in the free_list */
	// ::::: needs error checking, return -1 if _size is too big
	return (unsigned int)log2(_size)-4;
}

extern int my_free(Addr _a) 
{
  /* Remember to subtract 8 from the address given in order to get the address to the header */
  // Also, pointer arithmetic on a void* may not work
	header *temp = ((header *)_a) - 1; // only -1 because it moves back the size of a header
	int i = block_index(temp->size);
	
	merge(temp, i);	

	return 0;
}

void merge(header *temp, int i)
{
	if(i >= free_list_size-1)
		return;
	header *iter = free_list[i];
	
	while(iter != NULL) {
		if(can_merge(temp, iter)) {
			// merge
		}
		iter = iter->next;
	}
	return;
}

bool can_merge(header *a, header *b)
{

	//printf("Pointers: %p, %p\n", a, b);
	//printf("Distance from head: %d, %d\n", ((char *)a - (char *)head), ((char *)b - (char *)head));
	//printf("XOR of (a-Head) and (b-Head): %d\n", ((char *)a - (char *)head) ^ ((char *)b - (char *)head));

	if ( ( ( (char *)a - (char *)head) ^ ( (char *)b - (char *)head) == a->size) && (a->size == b->size))
	{
		//printf("Blocks are mergeable.\n");
		return true;
	}
	else
	{
		//printf("Blocks are NOT mergeable.\n");
		return false;
	}
}

void print_free_list()
{
	printf("Free List:\n");
	for(int i=0; i<free_list_size; i++) {
		printf("%5i: ", (int)pow(2, i+4));
		header *iter = free_list[i];
		while(iter != NULL) {
			printf("%p->", iter);
			iter = iter->next;
		}
		printf("null\n");
	}
}

