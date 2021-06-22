.section .data
data1:
	.byte 0x34, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
data2:
	.int 2
.section .text
.globl _start
_start:
	fbld	data1
	fimul	data2
	fbstp	data1
	
	movq	$1, %rax
	movq	$0, %rbx
	int	$0x80
		
