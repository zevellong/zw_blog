.section .data
output:
	.asciz "argv is: %s\n"
argcsize:
	.asciz "argc size is: %d\n"
.section .text
.globl _start
_start:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$8, %rsp
		
	movq	$argcsize, %rdi
	movq	(%rsp), %rsi
	call	printf

#	#print argv
	movl	(%rbp), %ecx
loop1:
	movq	%rcx, -8(%rbp)
	movq	$output, %rdi
	movq	(%rbp), %rsi		
	call	printf
	addq	$8, %rbp
	addq	$32, %rsp
	popq	%rcx
	loop	loop1
end:
	movq	$0, %rdi
	call	exit
#
#
