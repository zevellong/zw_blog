.code32 
.section .data
output:
	.ascii "argv is: \n"
argcsize:
	.ascii "argc size is:"
linefeed:
	.ascii "\n"
buffer:
	.byte 0x00
.section .text
.globl _start
_start:
	movl	$argcsize, %ecx
	movl	$13, %edx
	movl	$4, %eax
	movl	$1, %ebx
	int	$0x80
	
	#print argc size
	leal	buffer, %edi		
	movl	(%esp), %eax
	addl	$'0', %eax
	stosb
	movl	$buffer, %ecx
	movl	$1, %edx
	call	printstr	
	
	#print argv
	movl	(%esp),%ecx
	movl	%esp, %ebp
	addl	$4, %ebp
loop1:
	pushl	%ecx
	movl	(%ebp), %ecx
	movl	$3, %edx
	call	printstr
	popl	%ecx
	addl	$4, %ebp
	loop	loop1

end:
	movl	$1, %eax
	movl	$0, %ebx
	int	$0x80

printstr:
	movl	$4, %eax
	movl	$1, %ebx
	int	$0x80
	movl	$4, %eax
	movl	$1, %ebx
	movl	$linefeed, %ecx
	movl	$1, %edx
	int	$0x80
	ret
	
