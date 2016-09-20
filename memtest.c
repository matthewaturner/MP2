#include "ackerman.h"
#include "my_allocator.h"
#include <stdio.h>

int main(int argc, char ** argv) {

  // input parameters (basic block size, memory length)

  int memsize = 1024;

  init_allocator(8, memsize);
  
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
  //ackerman_main();
  my_free(d);

  printf("\nReleasing Allocator\n");
  release_allocator();
  print_free_list();
}
