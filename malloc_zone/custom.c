#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>

void show_stats(malloc_zone_t *);
void dz_stat(void);
void cz_stat(void);

int main(void) {
  dz_stat();
  cz_stat();
  cz_stat();
  return 0;
}

void show_stats(malloc_zone_t *zone) {
  malloc_statistics_t mstat;
  malloc_zone_statistics(zone, &mstat);
  puts("=================================================");
  printf("blocks_in_use   = %u\n", mstat.blocks_in_use);
  printf("size_in_use     = %lu\n", mstat.size_in_use);
  printf("max_size_in_use = %lu\n", mstat.max_size_in_use);
  printf("size_allocated  = %lu\n", mstat.size_allocated);
  return;
}

void dz_stat(void) {
  malloc_zone_t *dz = malloc_default_zone();
  printf("\n[+] Default zone @ %p\n", dz);
  show_stats(dz);

  void *ptrs[100];
  int i;
  for (i = 0; i < 100; i++) {
    ptrs[i] = malloc((size_t)(i * 10));
  }
  show_stats(dz);

  for (i = 0; i < 100; i++) {
    free(ptrs[i]);
  }
  show_stats(dz);
  return;
}

void cz_stat(void) {
  malloc_zone_t *cz = malloc_create_zone(0x1000 * 16, 0);
  printf("\n[+] Custom zone @ %p\n", cz);
  show_stats(cz);

  void *ptrs[100];
  int i;
  for (i = 0; i < 100; i++) {
    ptrs[i] = malloc_zone_malloc(cz, (size_t)(i * 10));
  }
  show_stats(cz);

  for (i = 0; i < 100; i++) {
    malloc_zone_free(cz, ptrs[i]);
  }
  show_stats(cz);
  return;
}

