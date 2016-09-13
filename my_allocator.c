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
	free_list = (char **)calloc((int)log2(M), sizeof(char *));
	header *temp = (header *)malloc(M);
	temp->size = M;
	temp->next = NULL;
	free_list[(int)log2(M)-1] = (char *)temp;
	free_list_size = (int)log2(M);
}

extern Addr my_malloc(unsigned int _length) 
{
  /* This preliminary implementation simply hands the call over the 
     the C standard library! 
     Of course this needs to be replaced by your implementation.
  */
	int block_length = block_needed(_length);
	int i = (int)log2(block_length)-1;
	
	while(i < free_list_size && free_list[i] == NULL) 
		i++;
	split(i, block_length);

	return free_list[(int)log2(block_length)-1];

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
	while(pow(2, i) < _length)
		i++;
	return pow(2, i);
}

extern int my_free(Addr _a) 
{
  /* Same here! */
  free(_a);
  return 0;
}

