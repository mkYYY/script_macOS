#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <mach-o/loader.h>

void read_mach_header(FILE *, struct mach_header_64 *);
void print_mach_header(struct mach_header_64 *);
void read_load_command(FILE *, struct load_command *, long);
int inspect_segment(FILE *, long, uint64_t);
void print_segment_details(FILE *, struct load_command *, long);

int main(int argc, char *argv[]) {
  if (argc < 2)
    return 1;

  char *numstr = "0xfffffff008888888";
  if (argc > 2) numstr = argv[2];
  uint64_t addr2find = strtoull(numstr, NULL, 0);
  printf("[*] xinfo @ 0x%016llx\n", addr2find);

  struct mach_header_64 mh64;
  printf("sizeof(struct mach_header_64) = %lu\n", sizeof(struct mach_header_64));
  FILE *fp = fopen(argv[1], "rb");
  read_mach_header(fp, &mh64);
  print_mach_header(&mh64); 

  // fp currently points at LC 0 (the first one)
  long offset = ftell(fp);
  struct load_command lc;
  for (int i = 0; i < mh64.ncmds; i++) {
    read_load_command(fp, &lc, offset);
    // rewind back sizeof(struct load_command)
    fseek(fp, -1 * ((long)(sizeof(struct load_command))), SEEK_CUR);
    printf("LC%02d: lc.cmd=0x%x lc.cmdsize=0x%x\n", i, lc.cmd, lc.cmdsize); 
    if ((lc.cmd == LC_SEGMENT_64) && (inspect_segment(fp, ftell(fp), addr2find))) {
      // print_segment_details(&lc, addr2find);
      printf("[+] Found 0x%16llx @ LC%02d\n", addr2find, i);
      exit(EXIT_SUCCESS);
    }

    offset += lc.cmdsize;
  }
  return 2;
}

void read_mach_header(FILE *obj, struct mach_header_64 *mhp) {
  rewind(obj);
  fread(mhp, sizeof(struct mach_header_64), 1UL, obj); 
  return;
}

void print_mach_header(struct mach_header_64 *mhp) {
  puts("struct mach_header_64 mhp {");
  char *smagic = "???";
  if (mhp->magic == MH_MAGIC_64) smagic = "MH_MAGIC_64";
  else if (mhp->magic == MH_CIGAM_64) smagic = "MH_CIGAM_64";
  printf("\t.magic = 0x%08x = %s\n", mhp->magic, smagic);
  // printf("\t.cputype = 0x
  printf("\t.ncmds = %u = 0x%08x\n", mhp->ncmds, mhp->ncmds);
  printf("\t.sizeofcmds = %u = 0x%08x\n", mhp->sizeofcmds, mhp->sizeofcmds);
  puts("}");
}

void read_load_command(FILE *obj, struct load_command *lcp, long offset) {
  fseek(obj, offset, SEEK_SET);
  fread(lcp, sizeof(struct load_command), 1, obj);
  return;
}

int inspect_segment(FILE *obj, long offset, uint64_t addr2find) {
  int ret = 0;
  long orig = ftell(obj);
  struct segment_command_64 segcmd64;
  fread(&segcmd64, sizeof(struct segment_command_64), 1, obj);
  uint64_t addr_begin = segcmd64.vmaddr;
  uint64_t addr_end = addr_begin + segcmd64.vmsize;
  if ((addr_begin < addr2find) && (addr2find < addr_end)) {
    // BINGO!
    ret = 1;
  }
  fseek(obj, orig, SEEK_SET);
  return ret;
}


