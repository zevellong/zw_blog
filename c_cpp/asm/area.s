	.file	"area.c"
	.text
	.globl	area
	.type	area, @function
area:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	cvtsi2sd	-4(%rbp), %xmm1
	movsd	.LC0(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	cvtsi2sd	-4(%rbp), %xmm0
	mulsd	%xmm1, %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	area, .-area
	.section	.rodata
.LC1:
	.string	"ii=%lf,jj=%lf,kk=%lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	$3, -36(%rbp)
	movl	$4, -32(%rbp)
	movl	$5, -28(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, %edi
	call	area
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, %edi
	call	area
	movq	%xmm0, %rax
	movq	%rax, -16(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	area
	movq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	movsd	-8(%rbp), %xmm2
	movsd	-16(%rbp), %xmm1
	movsd	-24(%rbp), %xmm0
	leaq	.LC1(%rip), %rdi
	movl	$3, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	1293080650
	.long	1074340347
	.ident	"GCC: (GNU) 8.2.1 20181127"
	.section	.note.GNU-stack,"",@progbits
