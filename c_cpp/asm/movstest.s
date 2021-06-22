.section .data
value1:
	.ascii "This is a test string.\n"
.section .bss
	.lcomm output, 23
.section .text
.globl _start
_start:
	leaq	value1+22, %rsi
	leaq	22+output, %rdi
	std
	movsb
	movsw
	movsl

	movq	$1, %rax
	movq	$0, %rbx
	int	$0x80
