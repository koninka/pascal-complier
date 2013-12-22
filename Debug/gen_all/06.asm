.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 40 dup(0)
	v_i db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str9 db " ", 0
	fmt_str_new_line db 10, 0
.code
@swap_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 4
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_4:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@swap_0 endp
@print_1 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 4
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_6:
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_7
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str9
	call	crt_printf
	add	esp, dword ptr 4
@lcontinue_8:
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_6
@lend_7:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
@exit_5:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print_1 endp
@partition_2 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 8
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	add	ebx, dword ptr 4
	push	[ebx]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_12:
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
	push	dword ptr 0
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
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	add	ebx, dword ptr 4
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
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@lend_11
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	[eax]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	add	ebx, dword ptr 4
	push	[ebx]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	[eax]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@else_14
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 1
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@endif_13
@else_14:
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 8]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	ebp
	call	@swap_0
	add	esp, dword ptr 8
	mov	ebx, ebp
	push	[ebx - 8]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@endif_13
@endif_13:
	jmp	@lcontinue_12
@lend_11:
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	add	ebx, dword ptr 4
	push	[ebx]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	ebp
	call	@swap_0
	add	esp, dword ptr 8
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	add	ebx, dword ptr 4
	add	ebx, dword ptr 4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_10:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@partition_2 endp
@qsort_3 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 4
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	add	ebx, dword ptr 4
	push	[ebx]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@endif_16
	sub	esp, dword ptr 4
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	add	ebx, dword ptr 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	ebp
	call	@partition_2
	add	esp, dword ptr 12
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	ebp
	call	@qsort_3
	add	esp, dword ptr 12
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	add	ebx, dword ptr 4
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 1
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	ebp
	call	@qsort_3
	add	esp, dword ptr 12
@endif_16:
@exit_15:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@qsort_3 endp
main:
	mov	ebp, esp
	push	dword ptr 1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_18:
	push	dword ptr [v_i]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_19
	push	dword ptr [v_i]
	push	dword ptr 6180
	pop	ebx
	pop	eax
	imul	ebx
	push	eax
	push	dword ptr 19
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	dword ptr 21
	pop	ebx
	pop	eax
	xor	edx, edx
	idiv	ebx
	push	edx
	push	offset v_a
	push	dword ptr [v_i]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_20:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_18
@lend_19:
	push	offset v_a
	pop	eax
	mov	ecx, dword ptr 40
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_21:
	cmp	ebx, ecx
	jge	@L_22
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_21
@L_22:
	push	dword ptr 40
	push	ebp
	call	@print_1
	add	esp, dword ptr 44
	push	dword ptr 10
	push	dword ptr 1
	push	offset v_a
	push	ebp
	call	@qsort_3
	add	esp, dword ptr 12
	push	offset v_a
	pop	eax
	mov	ecx, dword ptr 40
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_23:
	cmp	ebx, ecx
	jge	@L_24
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_23
@L_24:
	push	dword ptr 40
	push	ebp
	call	@print_1
	add	esp, dword ptr 44
@exit_17:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
