/* 
    File: my_allocator.c

    Author: <your name>
            Department of Computer Science
            Texas A&M University
    Date  : <date>

    Modified: 

    This file contains the implementation of the module "MY_ALLOCATOR".

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "my_allocator.h"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

header **free_list;
int free_list_size;

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

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
	header *temp = (header *)malloc(M);
	// set header attributes for whole memory block
	temp->size = M;
	temp->next = NULL;
	// set largest block list pointer to the whole memory allocated
	free_list[block_index(M)] = temp;
	// store size of free_list
	free_list_size = (int)log2(M)-3;
}

extern Addr my_malloc(unsigned int _length) 
{
  /* This preliminary implementation simply hands the call over the 
     the C standard library! 
     Of course this needs to be replaced by your implementation.
  */
	// find min power of two to return
	int block_length = block_needed(_length);
	// index of the block we need in free_list
	int i = block_index(block_length);
	
	// ::::: need to error check for i=-1 (returned when block_length too big)
	
	// until we find a block of at least block_length size, increase the index
	while(i < free_list_size && free_list[i] == NULL)
		i++;

	// ::::: need to error check to make sure there is space at all in the free_list

	// split blocks starting with i until we have a block of size block_length
	split(i, block_length);
	
	// free_list[i] will now have a block of correct size
	i = block_index(block_length);
	// store pointer to block
	header *temp = free_list[i];
	// remove the block we are returning from the free_list of that size
	free_list[i] = temp->next;
	// add 8 to the pointer returned so data doesn't overwrite block header
	return (void *)(temp + 1);
}

void split(int i, int block_length)
{
	header *left, *right;
	int size;

	while( (free_list[i])->size != block_length) {
		size = free_list[i]->size;
		left = free_list[i];
		left->size = size/2;
		right = left+size/2;
		right->size = size/2;

		free_list[i] = left->next;
		left->next = right;
		right->next = NULL;

		free_list[i-1] = left;
		i--;
	}
}

unsigned int block_needed(unsigned int _length) 
{
  /* Size of the block needed (smallest power of two the length fits in) */

	// minimum useful block size is 16 bytes bc header is 8 bytes
	int i=4;
	// subtract 8 to accound for the header
	while(pow(2, i)-8 < _length)
		i++;
	return pow(2, i);
}

int block_index(unsigned int _length)
{
  /* Returns the index of the list of _length sized blocks in the free_list */
	// ::::: needs error checking, return -1 if _length is too big
	return (unsigned int)log2(_length)-4;
}

extern int my_free(Addr _a) 
{
  /* Remember to subtract 8 from the address given in order to get the address to the header */
  // Also, pointer arithmetic on a void* may not work, may to cast to a header and subract 1
  free(_a);
  return 0;
}

void print_free_list()
{
	printf("Free List:\n");
	for(int i=0; i<free_list_size; i++)
		printf("%5i: %p\n", (int)pow(2, i+4), free_list[i]);
}

