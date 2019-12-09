.section __TEXT,__text
.globl _main
_main:
  xorl %eax, %eax
  cpuid
  leaq output(%rip), %rsi
  movl %ebx, 12(%rsi)   // 0x756e6547 == "Genu"
  movl %edx, 16(%rsi)   // 0x49656e69 == "ineI"
  movl %ecx, 20(%rsi)   // 0x6c65746e == "ntel"
  movb $2, %al          // SYSCALL_CLASS_UNIX
  shll $24, %eax        // SYSCALL_CLASS_SHIFT
  orl $4, %eax          // SYS_write
  xorl %edi, %edi
  movb $1, %dil         // STDOUT_FILENO
  xorl %edx, %edx
  movb $26, %dl         // buffer size to write
  syscall

  movb $2, %al          // SYSCALL_CLASS_UNIX
  shll $24, %eax        // SYSCALL_CLASS_SHIFT
  orl $1, %eax          // SYS_exit
  xorl %edi, %edi       // EXIT_SUCCESS
  syscall

.section __DATA,__data
output:
  .ascii "Vendor ID: 'xxxxxxxxxxxx'\n"

