.section .data
output:
	.ascii  "The value is xxxx\n"
.section .text
.globl _star
_start:
	movl	$100, %ecx
	movl	$0 ,%eax
loop1:
	addl	%ecx, %eax
	loop	loop1
	movl	$output, %edi
	movl	%eax, 13(%edi)
	movl	$4, %eax
	movl	$1, %ebx
	movl	$output, %ecx
	movl	$19, %edx
	int	$0x80
	movl	$0, %ebx
	movl	$1, %eax
	int	$0x80 
