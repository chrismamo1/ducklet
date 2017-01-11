	.section .rodata.cst8,"a",@progbits
	.align	16
caml_negf_mask:	.quad   0x8000000000000000, 0
	.align	16
caml_absf_mask:	.quad   0x7FFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF
	.data
	.globl	camlIndex__data_begin
camlIndex__data_begin:
	.text
	.globl	camlIndex__code_begin
camlIndex__code_begin:
	.data
	.quad	8960
	.globl	camlIndex
camlIndex:
	.quad	1
	.quad	1
	.quad	1
	.quad	1
	.quad	1
	.quad	1
	.quad	1
	.quad	1
	.data
	.quad	3063
camlIndex__35:
	.quad	camlIndex__is_prime_1817
	.quad	3
	.data
	.quad	3063
camlIndex__36:
	.quad	camlIndex__matrix_print_1807
	.quad	3
	.data
	.quad	4087
camlIndex__37:
	.quad	caml_curry2
	.quad	5
	.quad	camlIndex__matrix_multiply_1640
	.data
	.quad	4087
camlIndex__38:
	.quad	caml_curry2
	.quad	5
	.quad	camlIndex__$2d$2d_1634
	.data
	.quad	4087
camlIndex__39:
	.quad	caml_curry2
	.quad	5
	.quad	camlIndex__testdiv_1819
	.data
	.quad	5116
camlIndex__1:
	.ascii	" <html> <head> <title>  "
	.space	7
	.byte	7
	.data
	.quad	2044
camlIndex__2:
	.ascii	", "
	.space	5
	.byte	5
	.data
	.quad	2827
camlIndex__3:
	.quad	camlIndex__2
	.quad	1
	.data
	.quad	4868
camlIndex__4:
	.quad	1
	.quad	1
	.quad	1
	.quad	camlIndex__3
	.data
	.quad	2044
camlIndex__5:
	.ascii	"%d, "
	.space	3
	.byte	3
	.data
	.quad	2816
camlIndex__6:
	.quad	camlIndex__4
	.quad	camlIndex__5
	.data
	.quad	2044
camlIndex__7:
	.ascii	"<br />"
	.space	1
	.byte	1
	.data
	.quad	2827
camlIndex__8:
	.quad	camlIndex__7
	.quad	1
	.data
	.quad	2044
camlIndex__9:
	.ascii	"<br />"
	.space	1
	.byte	1
	.data
	.quad	2816
camlIndex__10:
	.quad	camlIndex__8
	.quad	camlIndex__9
	.data
	.quad	2044
camlIndex__11:
	.ascii	"Is "
	.space	4
	.byte	4
	.data
	.quad	2044
camlIndex__12:
	.ascii	" prime?"
	.byte	0
	.data
	.quad	2827
camlIndex__13:
	.quad	camlIndex__12
	.quad	1
	.data
	.quad	4868
camlIndex__14:
	.quad	1
	.quad	1
	.quad	1
	.quad	camlIndex__13
	.data
	.quad	2827
camlIndex__15:
	.quad	camlIndex__11
	.quad	camlIndex__14
	.data
	.quad	3068
camlIndex__16:
	.ascii	"Is %d prime?"
	.space	3
	.byte	3
	.data
	.quad	2816
camlIndex__17:
	.quad	camlIndex__15
	.quad	camlIndex__16
	.data
	.quad	6140
camlIndex__18:
	.ascii	" </title> </head> <body> <h3>Is \42  "
	.space	4
	.byte	4
	.data
	.quad	4868
camlIndex__19:
	.quad	1
	.quad	1
	.quad	1
	.quad	1
	.data
	.quad	2044
camlIndex__20:
	.ascii	"%d"
	.space	5
	.byte	5
	.data
	.quad	2816
camlIndex__21:
	.quad	camlIndex__19
	.quad	camlIndex__20
	.data
	.quad	5116
camlIndex__22:
	.ascii	" \42 prime?</h3><br /> <h1>  "
	.space	4
	.byte	4
	.data
	.quad	2044
camlIndex__23:
	.ascii	"Yes"
	.space	4
	.byte	4
	.data
	.quad	2827
camlIndex__24:
	.quad	camlIndex__23
	.quad	1
	.data
	.quad	2044
camlIndex__25:
	.ascii	"Yes"
	.space	4
	.byte	4
	.data
	.quad	2816
camlIndex__26:
	.quad	camlIndex__24
	.quad	camlIndex__25
	.data
	.quad	2044
camlIndex__27:
	.ascii	"No"
	.space	5
	.byte	5
	.data
	.quad	2827
camlIndex__28:
	.quad	camlIndex__27
	.quad	1
	.data
	.quad	2044
camlIndex__29:
	.ascii	"No"
	.space	5
	.byte	5
	.data
	.quad	2816
camlIndex__30:
	.quad	camlIndex__28
	.quad	camlIndex__29
	.data
	.quad	3068
camlIndex__31:
	.ascii	" </h1> <h1>  "
	.space	2
	.byte	2
	.data
	.quad	4092
camlIndex__32:
	.ascii	" <br />TIMES<br />  "
	.space	3
	.byte	3
	.data
	.quad	4092
camlIndex__33:
	.ascii	" <br /> EQUALS<br />  "
	.space	1
	.byte	1
	.data
	.quad	5116
camlIndex__34:
	.ascii	" </h1> </body> </html>  "
	.space	7
	.byte	7
	.text
	.align	16
	.globl	camlIndex__aux_1637
camlIndex__aux_1637:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_adjust_cfa_offset	8
.L101:
	movq	%rax, %rsi
	movq	24(%rdi), %rax
	cmpq	%rax, %rsi
	jge	.L100
	movq	%rbx, %rax
	addq	$8, %rsp
	.cfi_adjust_cfa_offset	-8
	ret
	.cfi_adjust_cfa_offset	8
	.align	4
.L100:
.L102:	subq	$24, %r15
	movq	caml_young_limit@GOTPCREL(%rip), %rax
	cmpq	(%rax), %r15
	jb	.L103
	leaq	8(%r15), %rdx
	movq	$2048, -8(%rdx)
	movq	%rsi, (%rdx)
	movq	%rbx, 8(%rdx)
	movq	%rsi, %rax
	addq	$-2, %rax
	movq	%rdx, %rbx
	jmp	.L101
.L103:	call	caml_call_gc@PLT
.L104:	jmp	.L102
	.cfi_endproc
	.type	camlIndex__aux_1637,@function
	.size	camlIndex__aux_1637,.-camlIndex__aux_1637
	.text
	.align	16
	.globl	camlIndex__testdiv_1819
camlIndex__testdiv_1819:
	.cfi_startproc
.L109:
	movq	%rax, %rdi
	cmpq	$3, %rbx
	jle	.L105
	movq	%rbx, %rcx
	sarq	$1, %rcx
	testq	%rcx, %rcx
	je	.L108
	movq	%rdi, %rax
	sarq	$1, %rax
	cqto
	idivq	%rcx
	jmp	.L107
	.align	4
.L108:
	movq	caml_exn_Division_by_zero@GOTPCREL(%rip), %rax
	movq	%r14, %rsp
	popq	%r14
	ret
	.align	4
.L107:
	salq	$1, %rdx
	incq	%rdx
	cmpq	$1, %rdx
	jne	.L106
	movq	$3, %rax
	ret
	.align	4
.L106:
	addq	$-4, %rbx
	movq	%rdi, %rax
	jmp	.L109
	.align	4
.L105:
	movq	$1, %rax
	ret
	.cfi_endproc
	.type	camlIndex__testdiv_1819,@function
	.size	camlIndex__testdiv_1819,.-camlIndex__testdiv_1819
	.text
	.align	16
	.globl	camlIndex__$2d$2d_1634
camlIndex__$2d$2d_1634:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_adjust_cfa_offset	8
.L110:
	movq	%rax, %rsi
.L111:	subq	$40, %r15
	movq	caml_young_limit@GOTPCREL(%rip), %rax
	cmpq	(%rax), %r15
	jb	.L112
	leaq	8(%r15), %rdi
	movq	$4343, -8(%rdi)
	movq	caml_curry2@GOTPCREL(%rip), %rax
	movq	%rax, (%rdi)
	movq	$5, 8(%rdi)
	movq	camlIndex__aux_1637@GOTPCREL(%rip), %rax
	movq	%rax, 16(%rdi)
	movq	%rsi, 24(%rdi)
	movq	$1, %rsi
	movq	%rbx, %rax
	movq	%rsi, %rbx
	addq	$8, %rsp
	.cfi_adjust_cfa_offset	-8
	jmp	camlIndex__aux_1637@PLT
	.cfi_adjust_cfa_offset	8
.L112:	call	caml_call_gc@PLT
.L113:	jmp	.L111
	.cfi_endproc
	.type	camlIndex__$2d$2d_1634,@function
	.size	camlIndex__$2d$2d_1634,.-camlIndex__$2d$2d_1634
	.text
	.align	16
	.globl	camlIndex__matrix_multiply_1640
camlIndex__matrix_multiply_1640:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_adjust_cfa_offset	40
.L122:
	movq	%rax, 32(%rsp)
	movq	%rbx, 24(%rsp)
	movq	-8(%rax), %rax
	shrq	$9, %rax
	orq	$1, %rax
	movq	%rax, 0(%rsp)
	movq	-8(%rbx), %rdi
	movq	%rdi, %rsi
	shrq	$9, %rsi
	orq	$1, %rsi
	movq	%rsi, 16(%rsp)
	cmpq	$1, %rsi
	jne	.L121
	movq	$1, %rbx
	movq	%rbx, 8(%rsp)
	jmp	.L120
	.align	4
.L121:
	cmpq	$1023, %rdi
	jbe	.L123
	movq	(%rbx), %rbx
	movq	-8(%rbx), %rbx
	shrq	$9, %rbx
	orq	$1, %rbx
	movq	%rbx, 8(%rsp)
.L120:
	movq	$1, %rdi
	call	camlArray__make_matrix_1025@PLT
.L124:
	movq	$1, %rcx
	movq	0(%rsp), %rbx
	addq	$-2, %rbx
	cmpq	%rbx, %rcx
	jg	.L114
	movq	%rbx, 0(%rsp)
.L115:
	movq	$1, %rdx
	movq	8(%rsp), %r9
	addq	$-2, %r9
	cmpq	%r9, %rdx
	jg	.L116
.L117:
	movq	$1, %rsi
	movq	16(%rsp), %r8
	addq	$-2, %r8
	cmpq	%r8, %rsi
	jg	.L118
.L119:
	movq	24(%rsp), %rdi
	movq	-8(%rdi), %rbx
	shrq	$9, %rbx
	cmpq	%rsi, %rbx
	jbe	.L123
	movq	-4(%rdi, %rsi, 4), %rbx
	movq	-8(%rbx), %rdi
	shrq	$9, %rdi
	cmpq	%rdx, %rdi
	jbe	.L123
	movq	-4(%rbx, %rdx, 4), %rdi
	sarq	$1, %rdi
	movq	32(%rsp), %r12
	movq	-8(%r12), %rbx
	shrq	$9, %rbx
	cmpq	%rcx, %rbx
	jbe	.L123
	movq	-4(%r12, %rcx, 4), %rbx
	movq	-8(%rbx), %r12
	shrq	$9, %r12
	cmpq	%rsi, %r12
	jbe	.L123
	movq	-4(%rbx, %rsi, 4), %rbx
	decq	%rbx
	imulq	%rdi, %rbx
	movq	-8(%rax), %rdi
	shrq	$9, %rdi
	cmpq	%rcx, %rdi
	jbe	.L123
	movq	-4(%rax, %rcx, 4), %rdi
	movq	-8(%rdi), %r12
	shrq	$9, %r12
	cmpq	%rdx, %r12
	jbe	.L123
	movq	-4(%rdi, %rdx, 4), %r12
	addq	%rbx, %r12
	movq	%r12, -4(%rdi, %rdx, 4)
	movq	%rsi, %rbx
	addq	$2, %rsi
	cmpq	%r8, %rbx
	jne	.L119
.L118:
	movq	%rdx, %rbx
	addq	$2, %rdx
	cmpq	%r9, %rbx
	jne	.L117
.L116:
	movq	%rcx, %rbx
	addq	$2, %rcx
	movq	0(%rsp), %rdi
	cmpq	%rdi, %rbx
	jne	.L115
.L114:
	addq	$40, %rsp
	.cfi_adjust_cfa_offset	-40
	ret
	.cfi_adjust_cfa_offset	40
.L123:	call	caml_ml_array_bound_error@PLT
	.cfi_endproc
	.type	camlIndex__matrix_multiply_1640,@function
	.size	camlIndex__matrix_multiply_1640,.-camlIndex__matrix_multiply_1640
	.text
	.align	16
	.globl	camlIndex__matrix_print_1807
camlIndex__matrix_print_1807:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_adjust_cfa_offset	40
.L129:
	movq	-8(%rax), %rbx
	shrq	$9, %rbx
	orq	$1, %rbx
	movq	$1, %rdi
	addq	$-2, %rbx
	cmpq	%rbx, %rdi
	jg	.L125
	movq	%rbx, 0(%rsp)
	movq	%rdi, 16(%rsp)
	movq	%rax, 8(%rsp)
.L126:
	movq	8(%rsp), %rbx
	movq	-8(%rbx), %rax
	shrq	$9, %rax
	cmpq	%rdi, %rax
	jbe	.L130
	movq	-4(%rbx, %rdi, 4), %rax
	movq	-8(%rax), %rax
	shrq	$9, %rax
	orq	$1, %rax
	movq	$1, %rbx
	movq	%rbx, 24(%rsp)
	addq	$-2, %rax
	movq	%rax, 32(%rsp)
	cmpq	%rax, %rbx
	jg	.L127
.L128:
	movq	camlIndex__6@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPrintf__fprintf_1025@PLT
.L131:
	movq	%rax, %rbx
	movq	8(%rsp), %rdi
	movq	-8(%rdi), %rax
	shrq	$9, %rax
	movq	16(%rsp), %rsi
	cmpq	%rsi, %rax
	jbe	.L130
	movq	-4(%rdi, %rsi, 4), %rax
	movq	-8(%rax), %rdi
	shrq	$9, %rdi
	movq	24(%rsp), %rsi
	cmpq	%rsi, %rdi
	jbe	.L130
	movq	-4(%rax, %rsi, 4), %rax
	movq	(%rbx), %rdi
	call	*%rdi
.L132:
	movq	24(%rsp), %rbx
	movq	%rbx, %rax
	addq	$2, %rbx
	movq	%rbx, 24(%rsp)
	movq	32(%rsp), %rbx
	cmpq	%rbx, %rax
	jne	.L128
.L127:
	movq	camlIndex__10@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPrintf__fprintf_1025@PLT
.L133:
	movq	16(%rsp), %rdi
	movq	%rdi, %rax
	addq	$2, %rdi
	movq	%rdi, 16(%rsp)
	movq	0(%rsp), %rbx
	cmpq	%rbx, %rax
	jne	.L126
.L125:
	movq	$1, %rax
	addq	$40, %rsp
	.cfi_adjust_cfa_offset	-40
	ret
	.cfi_adjust_cfa_offset	40
.L130:	call	caml_ml_array_bound_error@PLT
	.cfi_endproc
	.type	camlIndex__matrix_print_1807,@function
	.size	camlIndex__matrix_print_1807,.-camlIndex__matrix_print_1807
	.text
	.align	16
	.globl	camlIndex__is_prime_1817
camlIndex__is_prime_1817:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_adjust_cfa_offset	8
.L135:
	movq	%rax, %rbx
	addq	$-2, %rbx
	call	camlIndex__testdiv_1819@PLT
.L136:
	cmpq	$3, %rax
	jne	.L134
	movq	$1, %rax
	addq	$8, %rsp
	.cfi_adjust_cfa_offset	-8
	ret
	.cfi_adjust_cfa_offset	8
	.align	4
.L134:
	movq	$3, %rax
	addq	$8, %rsp
	.cfi_adjust_cfa_offset	-8
	ret
	.cfi_adjust_cfa_offset	8
	.cfi_endproc
	.type	camlIndex__is_prime_1817,@function
	.size	camlIndex__is_prime_1817,.-camlIndex__is_prime_1817
	.text
	.align	16
	.globl	camlIndex__entry
camlIndex__entry:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_adjust_cfa_offset	8
.L139:
	movq	camlIndex__1@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPervasives__output_string_1198@PLT
.L140:
	movq	camlIndex__38@GOTPCREL(%rip), %rax
	movq	camlIndex@GOTPCREL(%rip), %rbx
	movq	%rax, (%rbx)
	movq	camlIndex__37@GOTPCREL(%rip), %rax
	movq	%rax, 8(%rbx)
	movq	camlIndex__36@GOTPCREL(%rip), %rax
	movq	%rax, 16(%rbx)
	movq	$5, %rdi
	movq	$21, %rbx
	movq	$21, %rax
	call	camlArray__make_matrix_1025@PLT
.L141:
	movq	camlIndex@GOTPCREL(%rip), %rbx
	movq	%rax, 24(%rbx)
	movq	$5, %rdi
	movq	$21, %rbx
	movq	$21, %rax
	call	camlArray__make_matrix_1025@PLT
.L142:
	movq	camlIndex@GOTPCREL(%rip), %rbx
	movq	%rax, 32(%rbx)
	movq	32(%rbx), %rdi
	movq	24(%rbx), %rax
	movq	%rdi, %rbx
	call	camlIndex__matrix_multiply_1640@PLT
.L143:
	movq	camlIndex@GOTPCREL(%rip), %rbx
	movq	%rax, 40(%rbx)
	movq	$83979, 48(%rbx)
	movq	camlIndex__35@GOTPCREL(%rip), %rax
	movq	%rax, 56(%rbx)
	movq	camlIndex__17@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPrintf__fprintf_1025@PLT
.L144:
	movq	%rax, %rbx
	movq	$83979, %rax
	movq	(%rbx), %rdi
	call	*%rdi
.L145:
	movq	camlIndex__18@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPervasives__output_string_1198@PLT
.L146:
	movq	camlIndex__21@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPrintf__fprintf_1025@PLT
.L147:
	movq	%rax, %rbx
	movq	$83979, %rax
	movq	(%rbx), %rdi
	call	*%rdi
.L148:
	movq	camlIndex__22@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPervasives__output_string_1198@PLT
.L149:
	movq	$83979, %rax
	call	camlIndex__is_prime_1817@PLT
.L150:
	cmpq	$1, %rax
	je	.L138
	movq	camlIndex__26@GOTPCREL(%rip), %rbx
	jmp	.L137
.L138:
	movq	camlIndex__30@GOTPCREL(%rip), %rbx
.L137:
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPrintf__fprintf_1025@PLT
.L151:
	movq	camlIndex__31@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPervasives__output_string_1198@PLT
.L152:
	movq	camlIndex@GOTPCREL(%rip), %rax
	movq	24(%rax), %rax
	call	camlIndex__matrix_print_1807@PLT
.L153:
	movq	camlIndex__32@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPervasives__output_string_1198@PLT
.L154:
	movq	camlIndex@GOTPCREL(%rip), %rax
	movq	32(%rax), %rax
	call	camlIndex__matrix_print_1807@PLT
.L155:
	movq	camlIndex__33@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPervasives__output_string_1198@PLT
.L156:
	movq	camlIndex@GOTPCREL(%rip), %rax
	movq	40(%rax), %rax
	call	camlIndex__matrix_print_1807@PLT
.L157:
	movq	camlIndex__34@GOTPCREL(%rip), %rbx
	movq	camlPervasives@GOTPCREL(%rip), %rax
	movq	184(%rax), %rax
	call	camlPervasives__output_string_1198@PLT
.L158:
	movq	$1, %rax
	addq	$8, %rsp
	.cfi_adjust_cfa_offset	-8
	ret
	.cfi_adjust_cfa_offset	8
	.cfi_endproc
	.type	camlIndex__entry,@function
	.size	camlIndex__entry,.-camlIndex__entry
	.data
	.text
	.globl	camlIndex__code_end
camlIndex__code_end:
	.data
	.globl	camlIndex__data_end
camlIndex__data_end:
	.long	0
	.globl	camlIndex__frametable
camlIndex__frametable:
	.quad	26
	.quad	.L158
	.word	16
	.word	0
	.align	8
	.quad	.L157
	.word	16
	.word	0
	.align	8
	.quad	.L156
	.word	16
	.word	0
	.align	8
	.quad	.L155
	.word	16
	.word	0
	.align	8
	.quad	.L154
	.word	16
	.word	0
	.align	8
	.quad	.L153
	.word	16
	.word	0
	.align	8
	.quad	.L152
	.word	16
	.word	0
	.align	8
	.quad	.L151
	.word	17
	.word	0
	.align	8
	.long	(.L159 - .) + 0x8c000000
	.long	0x1b110
	.quad	.L150
	.word	16
	.word	0
	.align	8
	.quad	.L149
	.word	16
	.word	0
	.align	8
	.quad	.L148
	.word	16
	.word	0
	.align	8
	.quad	.L147
	.word	17
	.word	0
	.align	8
	.long	(.L159 - .) + 0x8c000000
	.long	0x1b110
	.quad	.L146
	.word	16
	.word	0
	.align	8
	.quad	.L145
	.word	16
	.word	0
	.align	8
	.quad	.L144
	.word	17
	.word	0
	.align	8
	.long	(.L159 - .) + 0x8c000000
	.long	0x1b110
	.quad	.L143
	.word	16
	.word	0
	.align	8
	.quad	.L142
	.word	16
	.word	0
	.align	8
	.quad	.L141
	.word	16
	.word	0
	.align	8
	.quad	.L140
	.word	16
	.word	0
	.align	8
	.quad	.L136
	.word	16
	.word	0
	.align	8
	.quad	.L133
	.word	49
	.word	1
	.word	8
	.align	8
	.long	(.L159 - .) + 0x8c000000
	.long	0x1b110
	.quad	.L132
	.word	48
	.word	1
	.word	8
	.align	8
	.quad	.L131
	.word	49
	.word	1
	.word	8
	.align	8
	.long	(.L159 - .) + 0x8c000000
	.long	0x1b110
	.quad	.L124
	.word	48
	.word	2
	.word	24
	.word	32
	.align	8
	.quad	.L113
	.word	16
	.word	2
	.word	3
	.word	7
	.align	8
	.quad	.L104
	.word	16
	.word	3
	.word	5
	.word	3
	.word	7
	.align	8
.L159:
	.asciz	"printf.ml"
	.align	8
	.section .note.GNU-stack,"",%progbits
