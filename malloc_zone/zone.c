#include <stdlib.h>
#include <stdio.h>
#include <malloc/malloc.h>

int main(void) {
  void *pheap = malloc(0x100);
  char arrstack[0x100];

  printf("pheap @ %p\n", pheap);
  printf("arrstack @ %p\n", arrstack);

  malloc_zone_print_ptr_info(pheap);
  malloc_zone_print_ptr_info(arrstack);

  getchar();
  return 0;
}

