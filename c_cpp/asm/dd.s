.section .data
output:
 .asciz "The Processor Vendor ID is '%s'\n"
.section .bss
 .lcomm buffer, 12
.section .text
.globl main
main:
 movq $0, %rax
 cpuid
 movq $buffer, %rdi
 movq %rbx, (%rdi)
 movq %rdx, 4(%rdi)
 movq %rcx, 8(%rdi)
 movq $buffer, %rsi #1st parameter
 movq $output, %rdi #2nd parameter
 movq $0, %rax
 call printf
 addq $8, %rsp
 pushq $0
 call exit 
