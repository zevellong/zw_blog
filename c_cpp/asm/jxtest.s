.section .text
.global _start
_start:
	movl	$1, %eax
	movl	$4, %ebx
	subl	$1, %ebx
	jge	greater
	movl	$1, %eax
	int	$0x80
greater:
	mov	$20, %ebx
	mov	$1, %eax
	int	$0x80
