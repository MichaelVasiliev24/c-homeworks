	.file	"mergeSort.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"\320\236\321\210\320\270\320\261\320\272\320\260: \320\275\320\265 \321\203\320\264\320\260\320\273\320\276\321\201\321\214 \320\262\321\213\320\264\320\265\320\273\320\270\321\202\321\214 \320\277\320\260\320\274\321\217\321\202\321\214 \320\264\320\273\321\217 tempLeft\n"
	.align 8
.LC1:
	.string	"\320\236\321\210\320\270\320\261\320\272\320\260: \320\275\320\265 \321\203\320\264\320\260\320\273\320\276\321\201\321\214 \320\262\321\213\320\264\320\265\320\273\320\270\321\202\321\214 \320\277\320\260\320\274\321\217\321\202\321\214 \320\264\320\273\321\217 tempRight\n"
	.text
	.globl	merge
	.type	merge, @function
merge:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movl	%edx, -64(%rbp)
	movl	%ecx, -68(%rbp)
	movl	-64(%rbp), %eax
	subl	-60(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	movl	-68(%rbp), %eax
	subl	-64(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	-24(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L2
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$80, %edx
	movl	$1, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L1
.L2:
	movl	-20(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L4
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$81, %edx
	movl	$1, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L1
.L4:
	movl	$0, -36(%rbp)
	jmp	.L5
.L6:
	movl	-60(%rbp), %edx
	movl	-36(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	-36(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-16(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -36(%rbp)
.L5:
	movl	-36(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L6
	movl	$0, -32(%rbp)
	jmp	.L7
.L8:
	movl	-64(%rbp), %eax
	leal	1(%rax), %edx
	movl	-32(%rbp), %eax
	addl	%edx, %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-8(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -32(%rbp)
.L7:
	movl	-32(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L8
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
	movl	-60(%rbp), %eax
	movl	%eax, -28(%rbp)
	jmp	.L9
.L13:
	movl	-36(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-32(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-8(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jg	.L10
	movl	-36(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-56(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -36(%rbp)
	jmp	.L11
.L10:
	movl	-32(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-56(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -32(%rbp)
.L11:
	addl	$1, -28(%rbp)
.L9:
	movl	-36(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jge	.L14
	movl	-32(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L13
	jmp	.L14
.L15:
	movl	-36(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-56(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -36(%rbp)
	addl	$1, -28(%rbp)
.L14:
	movl	-36(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L15
	jmp	.L16
.L17:
	movl	-32(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	-56(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, -32(%rbp)
	addl	$1, -28(%rbp)
.L16:
	movl	-32(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L17
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	merge, .-merge
	.section	.rodata
	.align 8
.LC2:
	.string	"\320\236\321\210\320\270\320\261\320\272\320\260: \320\277\320\265\321\200\320\265\320\264\320\260\320\275 \320\275\321\203\320\273\320\265\320\262\320\276\320\271 \321\203\320\272\320\260\320\267\320\260\321\202\320\265\320\273\321\214 \320\275\320\260 \320\274\320\260\321\201\321\201\320\270\320\262\n"
	.align 8
.LC3:
	.string	"\320\236\321\210\320\270\320\261\320\272\320\260: \320\275\320\265\320\272\320\276\321\200\321\200\320\265\320\272\321\202\320\275\321\213\320\265 \320\263\321\200\320\260\320\275\320\270\321\206\321\213 \320\274\320\260\321\201\321\201\320\270\320\262\320\260\n"
	.text
	.globl	mergeSort
	.type	mergeSort, @function
mergeSort:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L19
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$81, %edx
	movl	$1, %esi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L18
.L19:
	cmpl	$0, -28(%rbp)
	js	.L21
	cmpl	$0, -32(%rbp)
	js	.L21
	movl	-28(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jle	.L22
.L21:
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$69, %edx
	movl	$1, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	fwrite@PLT
	jmp	.L18
.L22:
	movl	-28(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jge	.L24
	movl	-32(%rbp), %eax
	subl	-28(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	movl	%eax, %edx
	movl	-28(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %edx
	movl	-28(%rbp), %ecx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	mergeSort
	movl	-4(%rbp), %eax
	leal	1(%rax), %ecx
	movl	-32(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	mergeSort
	movl	-32(%rbp), %ecx
	movl	-4(%rbp), %edx
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	merge
	jmp	.L18
.L24:
	nop
.L18:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	mergeSort, .-mergeSort
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
