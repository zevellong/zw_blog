.section .data
str1:
	.ascii "This is a test string.\n"
.section .bss
	.lcomm output, 23
.section .text
.globl _start
_start:
	leaq	str1, %rsi
	leaq	output, %rdi
	movq	$23, %rcx
loop1:
	movsb	
	loop loop1
	movq	$1, %rax
	movq	$0, %rbx
	int	$0x80
