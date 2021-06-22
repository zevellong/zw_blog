.section .data
data1:
	.quad 7252051615
data2:
	.quad 5732348928
data3:
	.quad 35
.section .text
.global _start
_start:
	movl	data1, %ebx
	movl	data1+4, %eax
	movl	data2, %edx
	movl	data2+4, %ecx
	addl	%ebx, %edx
	adcl	%ecx, %eax

	movq	$1, %rax
	movq	$0, %rbx
	int	$0x80
	
