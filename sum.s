# float sum_avx(const float *x, size_t n)   System V: x in %rdi, n in %rsi, result in %xmm0
	.text
	.globl	sum_avx
	.type	sum_avx, @function
sum_avx:
	vxorps	%ymm0, %ymm0, %ymm0
	xorl	%eax, %eax
	movq	%rsi, %rcx
	andq	$-8, %rcx
.Lvec:
	cmpq	%rcx, %rax
	jae	.Lreduce
	vaddps	(%rdi,%rax,4), %ymm0, %ymm0
	addq	$8, %rax
	jmp	.Lvec
.Lreduce:
	vextractf128	$1, %ymm0, %xmm1
	vaddps	%xmm1, %xmm0, %xmm0
	vmovhlps	%xmm0, %xmm0, %xmm1
	vaddps	%xmm1, %xmm0, %xmm0
	vshufps	$0x55, %xmm0, %xmm0, %xmm1
	vaddss	%xmm1, %xmm0, %xmm0
.Ltail:
	cmpq	%rsi, %rax
	jae	.Ldone
	vaddss	(%rdi,%rax,4), %xmm0, %xmm0
	incq	%rax
	jmp	.Ltail
.Ldone:
	vzeroupper
	ret
	.size	sum_avx, .-sum_avx
	.section	.note.GNU-stack,"",@progbits
