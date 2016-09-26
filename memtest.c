#include "ackerman.h"
#include "my_allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void print_usage()
{
	printf("Two arguments expected.\nUsage is [-b <desired blocksize>] [-s <desired memsize>]\n");
}

int main(int argc, char ** argv) {

  // input parameters (basic block size, memory length)

  //printf("Two arguments expected.\nUsage is [-b <desired blocksize>] [-s <desired memsize>]\n");
	
	int option = 0;
	int blocksize = -1;
	int memsize = -1;
	
	while ((option = getopt(argc, argv,"b:s:")) != -1)
	{
		switch (option)
		{
			case 'b' : blocksize = atoi(optarg);
				break;
			case 's' : memsize = atoi(optarg);
				break;
			default: print_usage();
				exit(EXIT_FAILURE);
		}
	}
	
	if (blocksize == -1 || memsize == -1)
	{
		print_usage();
		exit(EXIT_FAILURE);
	}

  // memsize = 524288; // Default: ~512KB or 2^19 bytes
  // blocksize = 128; // Default: 128B

  printf("Given arguments are: %d and %d\n", blocksize, memsize);
  init_allocator(blocksize, memsize);
  
  /*// Testing functionality
  print_free_list();  
  void *a = my_malloc(100);
  printf("Obtained 100 bytes: %p\n", a);
  print_free_list();
  void *b = my_malloc(110);
  printf("Obtained 110 bytes: %p\n", b);
  print_free_list();
  void *c = my_malloc(120);
  printf("Obtained 120 bytes: %p\n", c);
  print_free_list();
  void *d = my_malloc(40);
  printf("Obtained 40 bytes: %p\n", d);
  print_free_list();
  my_free(d);
  printf("Freed 40 byte pointer: %p\n", d);
  print_free_list();
  my_free(a);
  printf("Freed 100 byte pointer: %p\n", a);
  print_free_list();
  my_free(b);
  printf("Freed 110 byte pointer: %p\n", b);
  print_free_list();
  my_free(c);
  printf("Freed 120 byte pointer: %p\n", c);
  print_free_list();
  //*/

  ackerman_main();


  printf("\nReleasing Allocator\n");
  release_allocator();
  //print_free_list();
}
