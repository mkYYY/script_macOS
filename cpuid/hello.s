	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	_g_uninitialized@GOTPCREL(%rip), %rax
	movq	_blank@GOTPCREL(%rip), %rcx
	movl	$0, -4(%rbp)
	leaq	L_.str(%rip), %rdx
	movq	%rdx, (%rax)
	movb	$65, (%rcx)
	movq	(%rax), %rdi
	callq	_puts
	xorl	%esi, %esi
	movl	%eax, -8(%rbp)          ## 4-byte Spill
	movl	%esi, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"HELLO"

	.comm	_g_uninitialized,8,3    ## @g_uninitialized
	.comm	_blank,8,0              ## @blank

.subsections_via_symbols
