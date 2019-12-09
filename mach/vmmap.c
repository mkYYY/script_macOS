#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <mach/vm_region.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *unparse_inheritance(vm_inherit_t); 
char *protection_bits_to_rwx (vm_prot_t);
char *behavior_to_text (vm_behavior_t);
void show_regions(task_t, mach_vm_address_t);

int main(int argc, char *argv[]) {
  struct vm_region_basic_info vmr;
  kern_return_t rc;
  mach_port_t task;
  mach_vm_size_t size = 8;
  vm_region_info_t info = (vm_region_info_t)malloc(10000);
  mach_msg_type_number_t info_count;
  mach_port_t object_name;
  mach_vm_address_t addr = 1;
  int pid;

  if (argc < 2) {
    printf("Usage: %s <PID>\n", argv[0]); 
    exit(1);
  }
  pid = atoi(argv[1]);
  
  rc = task_for_pid(mach_task_self(), pid, &task);

  if (rc) {
    fprintf(stderr, "task_for_pid() failed with error %d - %s (Am I entitled?)\n", rc, mach_error_string(rc));
    exit(1);
  }

  printf("Task: %d\n", task);
  show_regions(task, addr);
  printf("Done\n");
}

const char *unparse_inheritance (vm_inherit_t i) {
  switch (i) {
    case VM_INHERIT_SHARE:
      return "share";
    case VM_INHERIT_COPY:
      return "copy";
    case VM_INHERIT_NONE:
      return "none";
    default:
      return "???";
  }
}

char *protection_bits_to_rwx (vm_prot_t p) {
  // previous version of this somehow lost the "p&", always returning rwx..
  static char returned[4];

  returned[0] = (p &VM_PROT_READ    ? 'r' : '-');
  returned[1] = (p &VM_PROT_WRITE   ? 'w' : '-');
  returned[2] = (p & VM_PROT_EXECUTE ? 'x' : '-');
  returned[3] = '\0';

 // memory leak here. No biggy
  return (strdup(returned));
}

char *behavior_to_text (vm_behavior_t  b) {
  switch (b) {
    case VM_BEHAVIOR_DEFAULT: return("default");
    case VM_BEHAVIOR_RANDOM:  return("random");
    case VM_BEHAVIOR_SEQUENTIAL: return("fwd-seq");
    case VM_BEHAVIOR_RSEQNTL: return("rev-seq");
    case VM_BEHAVIOR_WILLNEED: return("will-need");
    case VM_BEHAVIOR_DONTNEED: return("will-need");
    case VM_BEHAVIOR_FREE: return("free-nowb");
    case VM_BEHAVIOR_ZERO_WIRED_PAGES: return("zero-wire");
    case VM_BEHAVIOR_REUSABLE: return("reusable");
    case VM_BEHAVIOR_REUSE: return("reuse");
    case VM_BEHAVIOR_CAN_REUSE: return("canreuse");
    default: return ("?");
  }
}

void show_regions(task_t task, mach_vm_address_t address) {
  kern_return_t kr;
  vm_region_basic_info_data_t info, prev_info;
  mach_vm_address_t prev_address;
  mach_vm_size_t size, prev_size;

  mach_port_t object_name;
  mach_msg_type_number_t count;

  int nsubregions = 0;
  int num_printed = 0;
  int done = 0;

  count = VM_REGION_BASIC_INFO_COUNT_64;

  kr = mach_vm_region(task, &address, &size, VM_REGION_BASIC_INFO, 
                      (vm_region_info_t)&info, &count, &object_name);
  if (kr != KERN_SUCCESS) {
    fprintf(stderr, "Error %d - %s\n", kr, mach_error_string(kr));
    return;
  }

  memcpy(&prev_info, &info, sizeof(vm_region_basic_info_data_t));
  prev_address = address;
  prev_size = size;
  nsubregions = 1;

  while (!done) {
    int print = 0;
    address = prev_address + prev_size;

    if (address == 0) {
      print = done = 1;
    }

    if (!done) {
      count = VM_REGION_BASIC_INFO_COUNT_64;

      kr = mach_vm_region(task, &address, &size, VM_REGION_BASIC_INFO, 
                          (vm_region_info_t)&info, &count, &object_name);

      if (kr != KERN_SUCCESS) {
        fprintf(stderr, "mach_vm_region failed for address %p - error %d\n", (void *)address, kr);
        size = 0;
        print = done = 1;
      }
    }

    if (address != prev_address + prev_size)
      print = 1;

    if ((info.protection != prev_info.protection) 
        || (info.max_protection != prev_info.max_protection) 
        || (info.inheritance != prev_info.inheritance) 
        || (info.shared != prev_info.shared) 
        || (info.reserved != prev_info.reserved))
      print = 1;

    if (print) {
      int print_size;
      char *print_size_unit;
      if (num_printed == 0)
        printf("Region ");
      else 
        printf("   ... ");

      print_size = prev_size;
      if (print_size > 1024) { print_size /= 1024; print_size_unit = "K"; }
      if (print_size > 1024) { print_size /= 1024; print_size_unit = "M"; }
      if (print_size > 1024) { print_size /= 1024; print_size_unit = "G"; }

      printf(" %p-%p [%d%s] (%s/%s; %s, %s, %s) %s", 
                (void *)(prev_address), 
                (void *)(prev_address + prev_size), 
                print_size, 
                print_size_unit, 
                protection_bits_to_rwx(prev_info.protection), 
                protection_bits_to_rwx(prev_info.max_protection), 
                unparse_inheritance(prev_info.inheritance), 
                prev_info.shared ? "shared" : "private", 
                prev_info.reserved ? "reserved" : "not-reserved", 
                behavior_to_text(prev_info.behavior));

      if (nsubregions > 1)
        printf(" (%d sub-regions)", nsubregions);
      printf("\n");

      prev_address = address;
      prev_size = size;
      memcpy(&prev_info, &info, sizeof(vm_region_basic_info_data_t));
      nsubregions = 1;

      num_printed++;
    } else {
      prev_size += size;
      nsubregions++;
    }

    if (done) 
      break;
  }
}

