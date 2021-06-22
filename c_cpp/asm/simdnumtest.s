.section .data
data:
value1:
	.int 1, -1, 0, 135246
value2:
	.quad 1, -1
.section .text
.globl	_start
_start:
	movdqu	value1, %xmm0
	movdqu	value2, %xmm1
	movl	$1, %eax
	movl	$0, %ebx
	int	$0x80
