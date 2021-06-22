.section .data
data1:
	.float 12.34
data2:
	.double 2053.631
.section .bss
	.lcomm	data, 8
.section .text
.globl _start
_start:
	flds	data1
	fldl	data2
	fstl	data

	movq	$1, %rax
	movq	$0, %rbx			

