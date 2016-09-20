/* 
    File: my_allocator.h

    Author: R.Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 08/02/08

    Modified:

*/

#ifndef _my_allocator_h_                   // include file only once
#define _my_allocator_h_

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <math.h>

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

struct header {
	header *next;
	int size;
};

//char *free_list; // = calloc((int)log2(memsize), sizeof(*char));

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

typedef void * Addr; 

/*--------------------------------------------------------------------------*/
/* MODULE   MY_ALLOCATOR */
/*--------------------------------------------------------------------------*/

unsigned int init_allocator(unsigned int bbs, 
			    unsigned int M); 
/* This function initializes the memory allocator and makes a portion of 
   ’_length’ bytes available. The allocator uses a ’_basic_block_size’ as 
   its minimal unit of allocation. The function returns the amount of 
   memory made available to the allocator. If an error occurred, 
   it returns 0. 
*/ 

unsigned int block_needed(unsigned int _size);

int block_index(unsigned int _size);

void split(int i, int block_size);

void merge(header *temp, int i);

bool can_merge(header *a, header *b);

int release_allocator(); 
/* This function returns any allocated memory to the operating system. 
   After this function is called, any allocation fails.
*/ 

Addr my_malloc(unsigned int _size); 
/* Allocate _length number of bytes of free memory and returns the 
   address of the allocated portion. Returns 0 when out of memory. */ 

int my_free(Addr _a); 
/* Frees the section of physical memory previously allocated 
   using ’my_malloc’. Returns 0 if everything ok. */ 

void bin(unsigned n);

void print_free_list();
#endif 
