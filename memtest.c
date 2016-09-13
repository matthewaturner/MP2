#include "ackerman.h"
#include "my_allocator.h"
#include <stdio.h>

int main(int argc, char ** argv) {

  // input parameters (basic block size, memory length)

  int memsize = 1024;

  init_allocator(8, memsize);
  
  printf("pointer for 100 bytes: %s", my_malloc(100));

  //ackerman_main();


  // release_allocator()
}
