	.file	"pa2.c"
	.text
	.globl	fib
	.type	fib, @function
fib:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	-36(%rbp), %eax
	addl	$1, %eax
	cltq
	movl	$4, %esi
	movq	%rax, %rdi
	call	calloc
	movq	%rax, -16(%rbp)
	movl	-36(%rbp), %eax
	addl	$1, %eax
	cltq
	movl	$4, %esi
	movq	%rax, %rdi
	call	calloc
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movl	$0, (%rax)
	movq	-16(%rbp), %rax
	addq	$4, %rax
	movl	$1, (%rax)
	movq	-48(%rbp), %rax
	movl	$0, (%rax)
	cmpl	$1, -36(%rbp)
	jg	.L2
	movl	-36(%rbp), %eax
	jmp	.L3
.L2:
	movl	$2, -24(%rbp)
	jmp	.L4
.L5:
	movl	-24(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	leaq	-4(%rdx), %rcx
	movq	-16(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rdx), %ecx
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	leaq	-8(%rdx), %rsi
	movq	-16(%rbp), %rdx
	addq	%rsi, %rdx
	movl	(%rdx), %edx
	addl	%ecx, %edx
	movl	%edx, (%rax)
	movl	-24(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	leaq	-4(%rdx), %rcx
	movq	-8(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rdx), %ecx
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	leaq	-8(%rdx), %rsi
	movq	-8(%rbp), %rdx
	addq	%rsi, %rdx
	movl	(%rdx), %edx
	addl	%ecx, %edx
	addl	$2, %edx
	movl	%edx, (%rax)
	addl	$1, -24(%rbp)
.L4:
	movl	-24(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jle	.L5
	movl	-36(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movq	-48(%rbp), %rax
	movl	%edx, (%rax)
	movl	-36(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -20(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movl	-20(%rbp), %eax
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	fib, .-fib
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"fib(%d) = %d calls = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	$0, -4(%rbp)
	jmp	.L7
.L8:
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-12(%rbp), %eax
	leaq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fib
	movl	%eax, %ecx
	movl	-8(%rbp), %edx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -4(%rbp)
.L7:
	movl	-16(%rbp), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L8
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
