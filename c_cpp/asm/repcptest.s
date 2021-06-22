.section .data
str1:
	.ascii "This is a test of the conversion program!\n"
.section .bss
	.lcomm output, 43
.section .text
.globl _start
_start:
	leaq	str1, %rsi
	leaq	output, %rdi
	movq	$43, %rcx
	shrq	$2, %rcx
	
	cld
	rep	movsl
	movq	$43, %rcx
	andq	$3, %rcx
	rep	movsb
	
	movq	$1, %rax
	movq	$0, %rbx
	int	$0x80
