.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 40 dup(0)
	v_i db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str10 db " ", 0
	fmt_str_new_line db 10, 0
.code
@swap_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	push	[ebx]
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	push	[ebx]
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_5:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@swap_0 endp
@print_1 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	1
	push	1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_7:
	mov	ebx, ebp
	push	[ebx - 4]
	push	10
	push	1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_8
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	push	ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str10
	call	crt_printf
	add	esp, 4
@lcontinue_9:
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_7
@lend_8:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
@exit_6:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print_1 endp
@partition_2 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	add	ebx, 4
	push	[ebx]
	push	1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, -8
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_13:
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, ebp
	push	[ebx - 8]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setle	al
	movzx	eax, al
	push	eax
	mov	ebx, ebp
	push	[ebx - 8]
	push	0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	ebx
	pop	eax
	and	eax, ebx
	push	eax
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	add	ebx, 4
	push	[ebx]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	push	eax
	pop	ebx
	pop	eax
	and	eax, ebx
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@lend_12
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	add	ebx, 4
	push	[ebx]
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ebx, [eax]
	push	ebx
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_15
	mov	ebx, ebp
	push	[ebx - 4]
	push	1
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@endif_14
@else_15:
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 8]
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	ebp
	call	@swap_0
	add	esp, 8
	mov	ebx, ebp
	push	[ebx - 8]
	push	1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, -8
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@endif_14
@endif_14:
	jmp	@lcontinue_13
@lend_12:
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	add	ebx, 4
	push	[ebx]
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	ebp
	call	@swap_0
	add	esp, 8
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	add	ebx, 4
	add	ebx, 4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_11:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@partition_2 endp
@qsort_3 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	add	ebx, 4
	push	[ebx]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@endif_17
	sub	esp, 4
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	add	ebx, 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	push	ebp
	call	@partition_2
	add	esp, 12
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	push	[ebx - 4]
	push	1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	push	ebp
	call	@qsort_3
	add	esp, 12
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	add	ebx, 4
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 4]
	push	1
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	push	ebp
	call	@qsort_3
	add	esp, 12
@endif_17:
@exit_16:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@qsort_3 endp
@quicksort_4 proc
	push	ebp
	mov	ebp, esp
	push	10
	push	1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	push	1
	push	1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	push	ebp
	call	@qsort_3
	add	esp, 12
@exit_18:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@quicksort_4 endp
main:
	mov	ebp, esp
	push	1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_20:
	push	dword ptr [v_i]
	push	10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_21
	push	dword ptr [v_i]
	push	6180
	pop	ebx
	pop	eax
	imul	ebx
	push	eax
	push	19
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	21
	pop	ebx
	pop	eax
	xor	edx, edx
	idiv	ebx
	push	edx
	push	offset v_a
	push	dword ptr [v_i]
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_22:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_20
@lend_21:
	push	offset v_a
	pop	eax
	mov	ecx, 40
	add	eax, ecx
	mov	ebx, 0
@L_23:
	cmp	ebx, ecx
	jge	@L_24
	sub	eax, 4
	mov	edx, [eax]
	push	edx
	add	ebx, 4
	jmp	@L_23
@L_24:
	push	40
	push	ebp
	call	@print_1
	add	esp, 44
	push	offset v_a
	push	ebp
	call	@quicksort_4
	add	esp, 4
	push	offset v_a
	pop	eax
	mov	ecx, 40
	add	eax, ecx
	mov	ebx, 0
@L_25:
	cmp	ebx, ecx
	jge	@L_26
	sub	eax, 4
	mov	edx, [eax]
	push	edx
	add	ebx, 4
	jmp	@L_25
@L_26:
	push	40
	push	ebp
	call	@print_1
	add	esp, 44
@exit_19:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
