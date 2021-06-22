.section .data
output:
	.ascii  "The processer Vender ID is 'xxxxxxxxxxxx'\n"
.section .text
.globl _start
_start:
	mov	$1,%eax
	cpuid
movl	$output, %edi
movl	%ebx, 28(%edi)
movl	%ecx, 32(%edi)
movl	%edx, 36(%edi)
movl	$4  , %eax
movl	$1  , %ebx
movl	$output, %ecx
movl	$42 , %edx
int	$0x80
movl	$1  , %eax
movl	$0  , %ebx
int	$0x80


		
