.section .data
output:
	.asciz "The Largest Number is %d\n"
values:
	.int	105, 235, 61, 315, 134, 221, 53, 145, 117, 5
.section .text
.globl _start
_start:
	xor	%rax,%rax
	xor	%rbx,%rbx
	movq	values, %rbx
	movq	$1, %rdi
loop:
	movl	values(, %rdi, 4), %eax
	cmp	%ebx, %eax
	cmova	%eax, %ebx
	inc	%edi
	cmp	$10, %edi
	jne	loop
	movl	%ebx, %esi
	movq	$output, %rdi
	call	printf
	pushq	$0
	call	exit
