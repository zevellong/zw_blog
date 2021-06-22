.code32
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
	
	pushl	$10
	call	area
	addl	$4, %esp
	movl	%eax, value
	
	pushl	$2
	call	area
	addl	$4, %esp
	movl	%eax, value

	pushl	$120
	call	area
	addl	$4, %esp
	movl	%eax, value

	movl	$0, %ebx	
	movl	$1, %eax
	int	$0x80
.type	area, @function
area:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	fldpi
	filds	8(%ebp)
	fmul	%st(0), %st(0)
	fmulp	%st(0), %st(1)
	fstps	-4(%ebp)
	movl	-4(%ebp), %eax

	movl	%ebp, %esp
	popl	%ebp
	ret
