#include "ackerman.h"
#include "my_allocator.h"
#include <stdio.h>

int main(int argc, char ** argv) {

  // input parameters (basic block size, memory length)

  int memsize = 1024;

  init_allocator(8, memsize);
  
  void *a = my_malloc(100);
  printf("pointer for 100 bytes: %p\n", a);
  print_free_list();
  void *b = my_malloc(450);
  printf("pointer for 450 bytes: %p\n", b);
  print_free_list();
  //ackerman_main();


  // release_allocator()
}
