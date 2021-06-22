.section .data
output:
	.asciz "The section is %d\n"
.section .text
.globl _start
_start:
	movq	$1, %rsi
	movq	$output,  %rdi
	call	printf
	
	call	overhere	
	movq	$3, %rsi
	movq	$output, %rdi
	call	printf
	
	movq	$0, %rdi
	call	exit
overhere:
	pushq	%rbp
	movq	%rsp, %rbp
	pushq	$3
	pushq	$3
	popq	%rax
	popq	%rax
	movq	$2, %rsi
	movq	$output, %rdi
	call	printf
	movq	%rbp, %rsp
	popq	%rbp
	ret
	
