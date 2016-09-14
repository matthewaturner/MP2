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

char **free_list;
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
  /* Initialize total mem size and free_list
  */
	free_list = (char **)calloc((int)log2(M), sizeof(char *)); // allocate space for the free list
	header *temp = (header *)malloc(M);                        // allocate actual memory
	temp->size = M;
	temp->next = NULL;
	free_list[(int)log2(M)-1] = (char *)temp; // index of the M-size block list in free_list
	free_list_size = (int)log2(M);            // store size of the free_list
}

extern Addr my_malloc(unsigned int _length) 
{
  /* This preliminary implementation simply hands the call over the 
     the C standard library! 
     Of course this needs to be replaced by your implementation.
  */
	int block_length = block_needed(_length); // find min power of two to return
	int i = (int)log2(block_length)-1;        // index of list of those blocks
	
	while(i < free_list_size && free_list[i] == NULL) // find a block with the mem we need 
		i++;
	split(i, block_length);        // split blocks until we have a block of size block_length
	
	i = (int)log2(block_length-1); // free_list[i] will now have a block of correct size
	header *temp = (header *)free_list[i];
	free_list[i] = temp->next;     // remove the block we are returning from free_list
	return temp + 8;               // add 8 to the pointer so data doesn't overwrite block header

	// return malloc((size_t)_length);
}

void split(int i, int block_length)
{
	header *left, *right;
	int size;

	while( ((header *)free_list[i])->size != block_length) {
		size = ((header *)free_list[i])->size;
		left = (header *)free_list[i];
		left->size = size/2;
		right = left+size/2;
		right->size = size/2;

		free_list[i] = left->next;
		left->next = (char *)right;
		right->next = NULL;

		free_list[i-1] = (char *)left;
		i--;
	}
}

unsigned int block_needed(unsigned int _length) 
{
  /* Size of the block needed (smallest power of two the length fits in)
  */
	int i=4; // Minimum block size that is useful, bc header is 8 bytes
	while(pow(2, i)-8 < _length) // subtract 8 bc header takes up 8 bytes
		i++;
	return pow(2, i);
}

extern int my_free(Addr _a) 
{
  /* Same here! */
  free(_a);
  return 0;
}

void print_free_list()
{
	printf("Free List:\n");
	for(int i=0; i<free_list_size; i++)
		printf("%i: %p\n", i, free_list[i]);
}

