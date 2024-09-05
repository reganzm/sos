.globl main
main:
	movq $60, %rax
	movq $100, %rdi
	syscall
