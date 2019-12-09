#include <stdlib.h>
#include <stdio.h>
#include <malloc/malloc.h>

int main(void) {
  malloc_zone_t *defzone = malloc_default_zone();
  // malloc_zone_t *czone = malloc_create_zone(0x1000 * 16, 0);
  malloc_zone_t *czone = malloc_create_zone(512, 0);

  printf("[+] Default zone: %p\n", defzone);
  printf("defzone->version = %u\n", defzone->version);
  printf("defzone->malloc @ %p\n", defzone->malloc);
  printf("[+] Custom zone:  %p\n", czone);
  printf("czone->version = %u\n", czone->version);
  printf("czone->malloc @ %p\n", czone->malloc);

  __asm__("int3");

  void *pmalloc = malloc(0x100);
  void *pcustom = malloc_zone_malloc(czone, 0x100);
  void *pdefault = malloc_zone_malloc(defzone, 0x100);

  printf("pmalloc  @ %p\n", pmalloc);
  printf("pcustom  @ %p\n", pcustom);
  printf("pdefault @ %p\n", pdefault);

  malloc_zone_free(defzone, pdefault);
  malloc_zone_free(czone, pcustom);
  free(pmalloc);

  malloc_destroy_zone(czone);
  return 0;
}

