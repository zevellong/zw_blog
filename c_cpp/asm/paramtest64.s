.section .data
output:
	.asciz "argv is: %s\n"
argcsize:
	.asciz "argc num is: %d\n"
.section .text
.globl _start
_start:
	#print argc
	movq	$argcsize, %rdi
	movq	(%rsp), %rsi
	call	printf

#	#print argv
	movl	(%rsp), %ecx	
	movq	%rsp, %rbp
	addq	$8, %rbp
	subq	$8, %rsp

loop1:
	pushq	%rcx
#	subq	$8, %rsp
	movq	$output, %rdi
	movq	(%rbp), %rsi		
	call	printf
	addq	$8, %rbp
#	addq	$8, %rsp
	popq	%rcx
	loop	loop1
end:
	movq	$0, %rdi
	call	exit
#
#
