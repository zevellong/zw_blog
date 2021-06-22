.section .data
data:
	.int	-45
.section .text
.globl	_start
_start:
	movl	$-345, %ecx
	movw	$0xffb1, %dx
	movl	data, %ebx
	movq	$1, %rax

testmovzx:
	movl	$279, %ecx
	movsx	%cl, %rbx	
	
call_exit:
	movq	$1, %rax	
	movq	$0, %rbx
	int	$0x80
