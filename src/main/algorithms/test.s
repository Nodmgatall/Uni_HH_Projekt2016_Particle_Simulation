	.file	"test.cpp"
	.text
	.p2align 4,,15
	.globl	_Z6step_2RdS_S_S_S_S_PdS0_S0_S0_S0_S0_mm
	.type	_Z6step_2RdS_S_S_S_S_PdS0_S0_S0_S0_S0_mm, @function
_Z6step_2RdS_S_S_S_S_PdS0_S0_S0_S0_S0_mm:
.LFB788:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	64(%rbp), %rax
	movq	72(%rbp), %r10
	movq	%rcx, -88(%rbp)
	movq	%r8, -96(%rbp)
	movq	%r9, -144(%rbp)
	movq	40(%rbp), %rcx
	subq	%rax, %r10
	movq	48(%rbp), %r8
	movq	56(%rbp), %r9
	leaq	22(,%r10,8), %r11
	shrq	$4, %r11
	salq	$4, %r11
	subq	%r11, %rsp
	leaq	7(%rsp), %r13
	subq	%r11, %rsp
	leaq	7(%rsp), %r12
	subq	%r11, %rsp
	leaq	7(%rsp), %r15
	shrq	$3, %r13
	shrq	$3, %r12
	leaq	0(,%r13,8), %rbx
	shrq	$3, %r15
	leaq	0(,%r12,8), %r14
	testq	%r10, %r10
	leaq	0(,%r15,8), %r11
	movq	%rbx, -64(%rbp)
	movq	%r14, -72(%rbp)
	movq	%r11, -80(%rbp)
	je	.L1
	movsd	(%rdx), %xmm3
	leaq	0(,%rax,8), %rdx
	movsd	(%rdi), %xmm1
	movq	%rdx, %rdi
	addq	16(%rbp), %rdi
	movsd	(%rsi), %xmm2
	movq	%rdi, %rsi
	shrq	$3, %rsi
	andl	$1, %esi
	cmpq	$3, %r10
	ja	.L99
	movq	%r10, %rsi
.L3:
	movq	24(%rbp), %r14
	movq	32(%rbp), %rbx
	cmpq	$1, %rsi
	movsd	(%rdi), %xmm0
	movl	$1, %r11d
	movsd	(%r14,%rdx), %xmm4
	subsd	%xmm1, %xmm0
	movsd	(%rbx,%rdx), %xmm5
	leaq	1(%rax), %rdx
	subsd	%xmm2, %xmm4
	subsd	%xmm3, %xmm5
	movq	%rdx, %rdi
	mulsd	%xmm0, %xmm0
	mulsd	%xmm4, %xmm4
	mulsd	%xmm5, %xmm5
	movsd	%xmm0, 0(,%r13,8)
	movsd	%xmm4, 0(,%r12,8)
	movsd	%xmm5, 0(,%r15,8)
	je	.L5
	movq	16(%rbp), %r11
	cmpq	$2, %rsi
	movq	24(%rbp), %rdi
	movq	32(%rbp), %r14
	movsd	(%r11,%rdx,8), %xmm6
	movl	$2, %r11d
	movsd	(%rdi,%rdx,8), %xmm7
	leaq	2(%rax), %rdi
	movsd	(%r14,%rdx,8), %xmm8
	subsd	%xmm1, %xmm6
	subsd	%xmm2, %xmm7
	subsd	%xmm3, %xmm8
	mulsd	%xmm6, %xmm6
	mulsd	%xmm7, %xmm7
	mulsd	%xmm8, %xmm8
	movsd	%xmm6, 8(,%r13,8)
	movsd	%xmm7, 8(,%r12,8)
	movsd	%xmm8, 8(,%r15,8)
	je	.L5
	movq	16(%rbp), %rbx
	movl	$3, %r11d
	movsd	(%rbx,%rdi,8), %xmm9
	subsd	%xmm1, %xmm9
	mulsd	%xmm9, %xmm9
	movsd	%xmm9, 16(,%r13,8)
	movq	24(%rbp), %r13
	movsd	0(%r13,%rdi,8), %xmm10
	subsd	%xmm2, %xmm10
	mulsd	%xmm10, %xmm10
	movsd	%xmm10, 16(,%r12,8)
	movq	32(%rbp), %r12
	movsd	(%r12,%rdi,8), %xmm11
	leaq	3(%rax), %rdi
	subsd	%xmm3, %xmm11
	mulsd	%xmm11, %xmm11
	movsd	%xmm11, 16(,%r15,8)
.L5:
	cmpq	%rsi, %r10
	je	.L6
	movq	%r10, %r14
	subq	%rsi, %r14
	movq	%r14, %rbx
	movq	%r14, -168(%rbp)
	subq	$2, %r14
	shrq	%r14
	addq	$1, %r14
	movq	%r14, -112(%rbp)
	addq	%r14, %r14
	cmpq	$1, %rbx
	movq	%r14, -160(%rbp)
	jne	.L12
.L7:
	movq	16(%rbp), %r14
	movq	24(%rbp), %r12
	movq	32(%rbp), %r15
	movq	-64(%rbp), %rsi
	movq	-72(%rbp), %r13
	movsd	(%r14,%rdi,8), %xmm12
	movsd	(%r12,%rdi,8), %xmm13
	movsd	(%r15,%rdi,8), %xmm14
	subsd	%xmm1, %xmm12
	movq	-80(%rbp), %rdi
	subsd	%xmm2, %xmm13
	subsd	%xmm3, %xmm14
	mulsd	%xmm12, %xmm12
	mulsd	%xmm13, %xmm13
	mulsd	%xmm14, %xmm14
	movsd	%xmm12, (%rsi,%r11,8)
	movsd	%xmm13, 0(%r13,%r11,8)
	movsd	%xmm14, (%rdi,%r11,8)
.L6:
	leaq	-1(%r10), %r11
	xorl	%ebx, %ebx
	movsd	A_ij(%rip), %xmm1
	andl	$7, %r11d
	movsd	B_ij(%rip), %xmm3
	je	.L10
	cmpq	$1, %r11
	movl	$1, %ebx
	je	.L10
	cmpq	$2, %r11
	je	.L65
	cmpq	$3, %r11
	je	.L66
	cmpq	$4, %r11
	je	.L67
	cmpq	$5, %r11
	je	.L68
	cmpq	$6, %r11
	movl	$2, %r14d
	cmovne	%r14, %rbx
	addq	$1, %rbx
.L68:
	addq	$1, %rbx
.L67:
	addq	$1, %rbx
.L66:
	addq	$1, %rbx
.L65:
	addq	$1, %rbx
	leaq	1(%rbx), %rsi
	cmpq	%rsi, %r10
	je	.L100
.L16:
	addq	$8, %rbx
.L10:
	leaq	1(%rbx), %rsi
	cmpq	%rsi, %r10
	jne	.L16
.L100:
	movq	-64(%rbp), %r12
	movq	-72(%rbp), %r13
	movq	-80(%rbp), %r15
	movsd	m_i(%rip), %xmm5
	movq	-88(%rbp), %rdi
	movq	-96(%rbp), %r11
	movsd	(%r12,%rbx,8), %xmm6
	movsd	0(%r13,%rbx,8), %xmm2
	movapd	%xmm6, %xmm4
	movsd	(%r15,%rbx,8), %xmm10
	movapd	%xmm6, %xmm15
	movq	72(%rbp), %rbx
	addsd	%xmm2, %xmm4
	movsd	m_j(%rip), %xmm14
	movsd	(%rdi), %xmm0
	subq	%rdx, %rbx
	movsd	(%r11), %xmm13
	andl	$3, %ebx
	movapd	%xmm4, %xmm7
	addsd	%xmm10, %xmm7
	movapd	%xmm7, %xmm8
	mulsd	%xmm7, %xmm8
	mulsd	%xmm7, %xmm8
	mulsd	%xmm8, %xmm3
	mulsd	%xmm8, %xmm8
	subsd	%xmm3, %xmm1
	mulsd	%xmm7, %xmm8
	movapd	%xmm1, %xmm11
	divsd	%xmm8, %xmm11
	mulsd	%xmm11, %xmm2
	mulsd	%xmm11, %xmm15
	mulsd	%xmm10, %xmm11
	movapd	%xmm2, %xmm6
	divsd	%xmm14, %xmm2
	movapd	%xmm15, %xmm12
	divsd	%xmm5, %xmm6
	divsd	%xmm5, %xmm12
	movapd	%xmm6, %xmm9
	divsd	%xmm14, %xmm15
	divsd	%xmm14, %xmm11
	je	.L93
	subsd	%xmm12, %xmm0
	subsd	%xmm6, %xmm13
	movsd	(%rcx,%rax,8), %xmm1
	movsd	(%r8,%rax,8), %xmm3
	movsd	(%r9,%rax,8), %xmm10
	addsd	%xmm15, %xmm1
	addsd	%xmm2, %xmm3
	addsd	%xmm11, %xmm10
	movsd	%xmm1, (%rcx,%rax,8)
	movsd	%xmm3, (%r8,%rax,8)
	movsd	%xmm10, (%r9,%rax,8)
	movq	%rdx, %rax
	addq	$1, %rdx
	cmpq	$1, %rbx
	je	.L93
	cmpq	$2, %rbx
	je	.L64
	movsd	(%rcx,%rax,8), %xmm4
	subsd	%xmm12, %xmm0
	movsd	(%r8,%rax,8), %xmm7
	subsd	%xmm6, %xmm13
	movsd	(%r9,%rax,8), %xmm8
	addsd	%xmm15, %xmm4
	addsd	%xmm2, %xmm7
	addsd	%xmm11, %xmm8
	movsd	%xmm4, (%rcx,%rax,8)
	movsd	%xmm7, (%r8,%rax,8)
	movsd	%xmm8, (%r9,%rax,8)
	movq	%rdx, %rax
	addq	$1, %rdx
.L64:
	movsd	(%rcx,%rax,8), %xmm5
	subsd	%xmm12, %xmm0
	movsd	(%r8,%rax,8), %xmm6
	subsd	%xmm9, %xmm13
	movsd	(%r9,%rax,8), %xmm14
	addsd	%xmm15, %xmm5
	addsd	%xmm2, %xmm6
	movq	72(%rbp), %r14
	addsd	%xmm11, %xmm14
	movsd	%xmm5, (%rcx,%rax,8)
	movsd	%xmm6, (%r8,%rax,8)
	movsd	%xmm14, (%r9,%rax,8)
	movq	%rdx, %rax
	addq	$1, %rdx
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L101:
	movsd	(%rcx,%rdx,8), %xmm4
	leaq	1(%rdx), %rsi
	movsd	(%r8,%rdx,8), %xmm7
	subsd	%xmm12, %xmm0
	movsd	(%r9,%rdx,8), %xmm8
	addsd	%xmm15, %xmm4
	addsd	%xmm2, %xmm7
	leaq	2(%rdx), %r10
	leaq	3(%rdx), %rax
	addsd	%xmm11, %xmm8
	subsd	%xmm9, %xmm13
	movsd	%xmm4, (%rcx,%rdx,8)
	subsd	%xmm12, %xmm0
	movsd	%xmm7, (%r8,%rdx,8)
	movsd	%xmm8, (%r9,%rdx,8)
	addq	$4, %rdx
	movsd	(%rcx,%rsi,8), %xmm5
	subsd	%xmm9, %xmm13
	movsd	(%r8,%rsi,8), %xmm6
	subsd	%xmm12, %xmm0
	movsd	(%r9,%rsi,8), %xmm14
	addsd	%xmm15, %xmm5
	addsd	%xmm2, %xmm6
	addsd	%xmm11, %xmm14
	subsd	%xmm9, %xmm13
	movsd	%xmm5, (%rcx,%rsi,8)
	movsd	%xmm6, (%r8,%rsi,8)
	movsd	%xmm14, (%r9,%rsi,8)
	movsd	(%rcx,%r10,8), %xmm1
	movsd	(%r8,%r10,8), %xmm3
	movsd	(%r9,%r10,8), %xmm10
	addsd	%xmm15, %xmm1
	addsd	%xmm2, %xmm3
	addsd	%xmm11, %xmm10
	movsd	%xmm1, (%rcx,%r10,8)
	movsd	%xmm3, (%r8,%r10,8)
	movsd	%xmm10, (%r9,%r10,8)
.L11:
	movsd	(%rcx,%rax,8), %xmm1
	cmpq	%rdx, %r14
	subsd	%xmm12, %xmm0
	movsd	(%r8,%rax,8), %xmm3
	subsd	%xmm9, %xmm13
	movsd	(%r9,%rax,8), %xmm10
	addsd	%xmm15, %xmm1
	addsd	%xmm2, %xmm3
	addsd	%xmm11, %xmm10
	movsd	%xmm1, (%rcx,%rax,8)
	movsd	%xmm3, (%r8,%rax,8)
	movsd	%xmm10, (%r9,%rax,8)
	jne	.L101
	movq	-88(%rbp), %rdx
	movq	-96(%rbp), %rcx
	movq	-144(%rbp), %r8
	movsd	%xmm0, (%rdx)
	movsd	%xmm13, (%rcx)
	movsd	%xmm0, (%r8)
.L1:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4,,10
	.p2align 3
.L93:
	.cfi_restore_state
	movq	72(%rbp), %r14
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L99:
	testq	%rsi, %rsi
	jne	.L3
	leaq	-2(%r10), %r13
	leaq	1(%rax), %rdx
	xorl	%r11d, %r11d
	movq	%rax, %rdi
	movq	%r10, -168(%rbp)
	shrq	%r13
	leaq	1(%r13), %rbx
	movq	%rbx, -112(%rbp)
	addq	%rbx, %rbx
	movq	%rbx, -160(%rbp)
.L12:
	movq	-64(%rbp), %r13
	leaq	(%rax,%rsi), %rbx
	salq	$3, %rsi
	movapd	%xmm2, %xmm13
	movq	-72(%rbp), %r12
	salq	$3, %rbx
	movapd	%xmm1, %xmm12
	addq	%rsi, %r13
	unpcklpd	%xmm13, %xmm13
	movq	%r13, -104(%rbp)
	movq	%rbx, %r13
	addq	24(%rbp), %r13
	movq	%rbx, %r14
	addq	32(%rbp), %rbx
	addq	16(%rbp), %r14
	movapd	%xmm3, %xmm14
	movq	-112(%rbp), %r15
	unpcklpd	%xmm12, %xmm12
	addq	%rsi, %r12
	movupd	0(%r13), %xmm0
	unpcklpd	%xmm14, %xmm14
	subq	$1, %r15
	addq	-80(%rbp), %rsi
	subpd	%xmm13, %xmm0
	andl	$3, %r15d
	movapd	(%r14), %xmm15
	movq	%r12, -120(%rbp)
	movq	%r15, -152(%rbp)
	movupd	(%rbx), %xmm4
	subpd	%xmm12, %xmm15
	movq	-104(%rbp), %r15
	movq	%r13, -128(%rbp)
	movl	$1, %r13d
	subpd	%xmm14, %xmm4
	movq	%rsi, -136(%rbp)
	mulpd	%xmm0, %xmm0
	movq	%r13, -56(%rbp)
	mulpd	%xmm15, %xmm15
	mulpd	%xmm4, %xmm4
	movups	%xmm0, (%r12)
	movq	-112(%rbp), %r12
	movups	%xmm15, (%r15)
	cmpq	%r12, %r13
	movups	%xmm4, (%rsi)
	movl	$16, %esi
	jnb	.L89
	cmpq	$0, -152(%rbp)
	je	.L95
	cmpq	$1, -152(%rbp)
	je	.L70
	cmpq	$2, -152(%rbp)
	je	.L71
	movq	-128(%rbp), %rsi
	movq	-120(%rbp), %r13
	movapd	16(%r14), %xmm5
	movq	-136(%rbp), %r12
	movq	$2, -56(%rbp)
	movupd	16(%rsi), %xmm6
	subpd	%xmm12, %xmm5
	movl	$32, %esi
	movupd	16(%rbx), %xmm7
	subpd	%xmm13, %xmm6
	subpd	%xmm14, %xmm7
	mulpd	%xmm5, %xmm5
	mulpd	%xmm6, %xmm6
	mulpd	%xmm7, %xmm7
	movups	%xmm5, 16(%r15)
	movq	-104(%rbp), %r15
	movups	%xmm6, 16(%r13)
	movups	%xmm7, 16(%r12)
.L71:
	movapd	(%r14,%rsi), %xmm8
	movq	-120(%rbp), %r13
	movq	-136(%rbp), %r12
	subpd	%xmm12, %xmm8
	movupd	(%rbx,%rsi), %xmm10
	addq	$1, -56(%rbp)
	subpd	%xmm14, %xmm10
	mulpd	%xmm8, %xmm8
	mulpd	%xmm10, %xmm10
	movups	%xmm8, (%r15,%rsi)
	movq	-128(%rbp), %r15
	movups	%xmm10, (%r12,%rsi)
	movupd	(%r15,%rsi), %xmm9
	movq	-104(%rbp), %r15
	subpd	%xmm13, %xmm9
	mulpd	%xmm9, %xmm9
	movups	%xmm9, 0(%r13,%rsi)
	addq	$16, %rsi
.L70:
	movapd	(%r14,%rsi), %xmm11
	movq	-128(%rbp), %r13
	movq	-120(%rbp), %r12
	subpd	%xmm12, %xmm11
	movupd	(%rbx,%rsi), %xmm0
	addq	$1, -56(%rbp)
	movupd	0(%r13,%rsi), %xmm15
	subpd	%xmm14, %xmm0
	movq	-56(%rbp), %r13
	subpd	%xmm13, %xmm15
	mulpd	%xmm11, %xmm11
	mulpd	%xmm0, %xmm0
	mulpd	%xmm15, %xmm15
	movups	%xmm11, (%r15,%rsi)
	movq	-136(%rbp), %r15
	movups	%xmm15, (%r12,%rsi)
	movups	%xmm0, (%r15,%rsi)
	addq	$16, %rsi
	cmpq	-112(%rbp), %r13
	jnb	.L89
	movq	-104(%rbp), %r13
	movq	%rax, 64(%rbp)
	movq	%rdx, -104(%rbp)
	movq	-128(%rbp), %r12
	movq	-120(%rbp), %rax
	movq	-136(%rbp), %rdx
.L8:
	movapd	(%r14,%rsi), %xmm4
	addq	$4, -56(%rbp)
	movupd	(%r12,%rsi), %xmm5
	subpd	%xmm12, %xmm4
	movq	-56(%rbp), %r15
	subpd	%xmm13, %xmm5
	movupd	(%rbx,%rsi), %xmm6
	mulpd	%xmm4, %xmm4
	movapd	16(%r14,%rsi), %xmm7
	subpd	%xmm14, %xmm6
	mulpd	%xmm5, %xmm5
	movupd	16(%r12,%rsi), %xmm8
	subpd	%xmm12, %xmm7
	movups	%xmm4, 0(%r13,%rsi)
	subpd	%xmm13, %xmm8
	movups	%xmm5, (%rax,%rsi)
	mulpd	%xmm6, %xmm6
	mulpd	%xmm7, %xmm7
	movupd	16(%rbx,%rsi), %xmm9
	mulpd	%xmm8, %xmm8
	movapd	32(%r14,%rsi), %xmm10
	subpd	%xmm14, %xmm9
	movupd	32(%r12,%rsi), %xmm11
	subpd	%xmm12, %xmm10
	movupd	32(%rbx,%rsi), %xmm15
	subpd	%xmm13, %xmm11
	mulpd	%xmm9, %xmm9
	movapd	48(%r14,%rsi), %xmm0
	subpd	%xmm14, %xmm15
	movupd	48(%r12,%rsi), %xmm4
	mulpd	%xmm10, %xmm10
	subpd	%xmm12, %xmm0
	movupd	48(%rbx,%rsi), %xmm5
	mulpd	%xmm11, %xmm11
	subpd	%xmm13, %xmm4
	mulpd	%xmm15, %xmm15
	subpd	%xmm14, %xmm5
	mulpd	%xmm0, %xmm0
	movups	%xmm6, (%rdx,%rsi)
	mulpd	%xmm4, %xmm4
	movups	%xmm7, 16(%r13,%rsi)
	mulpd	%xmm5, %xmm5
	movups	%xmm8, 16(%rax,%rsi)
	movups	%xmm9, 16(%rdx,%rsi)
	movups	%xmm10, 32(%r13,%rsi)
	movups	%xmm11, 32(%rax,%rsi)
	movups	%xmm15, 32(%rdx,%rsi)
	movups	%xmm0, 48(%r13,%rsi)
	movups	%xmm4, 48(%rax,%rsi)
	movups	%xmm5, 48(%rdx,%rsi)
	addq	$64, %rsi
	cmpq	-112(%rbp), %r15
	jb	.L8
	movq	64(%rbp), %rax
	movq	-104(%rbp), %rdx
.L89:
	movq	-160(%rbp), %rbx
	addq	%rbx, %r11
	addq	%rbx, %rdi
	cmpq	-168(%rbp), %rbx
	jne	.L7
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L95:
	movq	%rax, 64(%rbp)
	movq	%rdx, -104(%rbp)
	movq	%r15, %r13
	movq	-128(%rbp), %r12
	movq	-120(%rbp), %rax
	movq	-136(%rbp), %rdx
	jmp	.L8
	.cfi_endproc
.LFE788:
	.size	_Z6step_2RdS_S_S_S_S_PdS0_S0_S0_S0_S0_mm, .-_Z6step_2RdS_S_S_S_S_PdS0_S0_S0_S0_S0_mm
	.globl	m_j
	.data
	.align 8
	.type	m_j, @object
	.size	m_j, 8
m_j:
	.long	0
	.long	1072693248
	.globl	m_i
	.align 8
	.type	m_i, @object
	.size	m_i, 8
m_i:
	.long	0
	.long	1072693248
	.globl	B_ij
	.align 8
	.type	B_ij, @object
	.size	B_ij, 8
B_ij:
	.long	0
	.long	1077673984
	.globl	A_ij
	.align 8
	.type	A_ij, @object
	.size	A_ij, 8
A_ij:
	.long	0
	.long	1079377920
	.ident	"GCC: (GNU) 6.3.1 20170109"
	.section	.note.GNU-stack,"",@progbits
