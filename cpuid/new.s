//.section __DATA,__common
  //.comm vendor,12,0
  .comm vendor,12

.section __TEXT,__text
.globl _main
_main:
  xorl %eax, %eax
  cpuid
  leaq vendor(%rip), %rsi
  movl %ebx, (%rsi)
  movl %edx, 4(%rsi)
  movl %ecx, 8(%rsi)
  movb $2, %al
  shll $24, %eax
  orl $4, %eax
  // xorl %edi, %edi
  // movb $1, %dil
  movl $1, %edi
  // xorl %edx, %edx
  // movb $12, %dl
  movl $12, %edx
  syscall

  movb $2, %al
  shll $24, %eax
  orl $1, %eax
  xorl %edi, %edi
  syscall

