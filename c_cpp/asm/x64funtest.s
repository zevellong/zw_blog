.section .data
precision:
	.byte 0x7f, 0x00
.section .bss
	.lcomm value, 4
.section .text
.globl _start
_start:
	finit
	fldcw	precision
	
	movq	$10, %rdi
	call	area
	movq	%rax, value
	
	movq	$2, %rdi
	call	area
	movq	%rax, value

	movq	$120, %rdi
	call	area
	movq	%rax, value

	movq	$0, %rbx	
	movq	$1, %rax
	int	$0x80
.type	area, @function
area:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -20(%rbp)
	subq	$4, %rsp
	fldpi
	movq	-20(%rbp), %rax
	fildl	-20(%rbp)
	fmul	%st(0), %st(0)
	fmulp	%st(0), %st(1)
	fstps	-4(%rbp)
	movq	-4(%rbp), %rax

	movq	%rbp, %rsp
	popq	%rbp
	ret
