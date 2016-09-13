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
#include "my_allocator.h"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

char **free_list;

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

void init_allocator(int M)
{
	free_list = (char **)calloc((int)log2(M), sizeof(char *));
	header *temp = (header *)malloc(M);
	temp->size = M;
	temp->next = NULL;
	free_list[(int)log2(M)-1] = (char *)temp;
}

extern Addr my_malloc(unsigned int _length) 
{
  /* This preliminary implementation simply hands the call over the 
     the C standard library! 
     Of course this needs to be replaced by your implementation.
  */
	unsigned int block_length = block_needed(_length);
	
	int block_index = (int)log2(block_length);
	int i = block_index;
	while(free_list[i] == NULL) {
		i++;
	}
	while(i > block_index) {
		split(i);
		i--;
	}
	//return malloc((size_t)_length);
}

void split(int i) {
	if(i < 1)
		return;
	header *temp = (header *)free_list[i];
	int size = temp->size;
	
}

unsigned int block_needed(unsigned int _length) 
{
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

