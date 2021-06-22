.section .data
str1:
	.ascii "This is a test string.\n"
.section .bss
	.lcomm output, 23
.section .text
.globl _start
_start:
	leaq	str1, %rsi
	movq	%rsi, %rdi
	movq	$23, %rcx
	cld
loop1:
	lodsb
	cmpb	$'a', %al
	jl	skip
	cmpb	$'z', %al
	jg	skip
	subb	$0x20, %al
skip:
	stosb
	loop 	loop1
end:
	movq	$str1, %rdi
	call	printf
	movq	$1, %rax
	movq	$0, %rbx
	int	$0x80
