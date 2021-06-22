.section .data
output:
	.asciz  "The processer Vender ID is %s\n"
.section .bss
	.lcomm buffer,12
.section .text
.globl _start
_start:
movq	$0,%rax
cpuid
movq	$buffer, %rdi
movq	%rbx, (%rdi)
movq	%rdx, 4(%rdi)
movq	%rcx, 8(%rdi)
movq	$buffer, %rsi
movq	$output, %rdi
call	printf
addq	$8, %rsp
pushq	$0
call	exit

		
