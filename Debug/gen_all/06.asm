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
	mov	eax, dword ptr [ebx]
	mov	ebx, ebp
	add	ebx, -4
	push	[eax]
	mov	eax, ebx
	pop	[eax]
	mov	ebx, ebp
	add	ebx, dword ptr 16
	mov	eax, dword ptr [ebx]
	mov	ebx, ebp
	add	ebx, 12
	push	[eax]
	mov	eax, dword ptr [ebx]
	pop	[eax]
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, ebp
	add	ebx, dword ptr 16
	mov	eax, dword ptr [ebx]
	pop	[eax]
@exit_5:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@swap_0 endp
@print_1 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	xor	eax, eax
	mov	ebx, ebp
	add	ebx, -4
	mov	[ebx], eax
@forloop_7:
	mov	ebx, ebp
	mov	eax, dword ptr 9
	push	[ebx - 4]
	mov	ebx, eax
	pop	eax
	cmp	eax, ebx
	jg	@lend_8
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	push	ebx
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str10
	call	crt_printf
	add	esp, 12
@lcontinue_9:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_7
@lend_8:
	push	offset fmt_str_new_line
	call	crt_printf
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
	add	ebx, dword ptr 16
	mov	eax, ebp
	add	eax, -4
	mov	ebx, dword ptr [ebx]
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, dword ptr 20
	mov	eax, dword ptr [ebx]
	dec	eax
	mov	ebx, ebp
	add	ebx, -8
	push	eax
	mov	eax, ebx
	pop	[eax]
@lcontinue_13:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, ebp
	cmp	eax, dword ptr [ebx - 8]
	setle	al
	movzx	eax, al
	mov	ebx, ebp
	push	eax
	mov	eax, dword ptr [ebx - 8]
	xor	ebx, ebx
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	mov	ebx, eax
	pop	eax
	and	eax, ebx
	mov	ebx, ebp
	push	eax
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, ebp
	add	ebx, dword ptr 20
	cmp	eax, dword ptr [ebx]
	setl	al
	movzx	eax, al
	mov	ebx, eax
	pop	eax
	and	eax, ebx
	xor	ebx, ebx
	cmp	eax, ebx
	je	@lend_12
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	ebx, ebp
	add	ebx, 12
	push	[eax]
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 20
	mov	eax, dword ptr [ebx]
	mov	ebx, 4
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	ebx, dword ptr [eax]
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_15
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	inc	eax
	mov	ebx, ebp
	add	ebx, -4
	push	eax
	mov	eax, ebx
	pop	[eax]
	jmp	@endif_14
@else_15:
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 8]
	mov	ebx, 4
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	ebx, ebp
	add	ebx, 12
	push	eax
	push	[ebx]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	ebp
	call	@swap_0
	add	esp, 8
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 8]
	dec	eax
	mov	ebx, ebp
	add	ebx, -8
	push	eax
	mov	eax, ebx
	pop	[eax]
	jmp	@endif_14
@endif_14:
	jmp	@lcontinue_13
@lend_12:
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 20
	mov	eax, dword ptr [ebx]
	mov	ebx, 4
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	ebx, ebp
	add	ebx, 12
	push	eax
	push	[ebx]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	ebp
	call	@swap_0
	add	esp, 8
	mov	ebx, ebp
	mov	eax, ebp
	add	eax, dword ptr 24
	mov	ebx, dword ptr [ebx - 4]
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
	add	ebx, dword ptr 16
	mov	eax, dword ptr [ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 20
	cmp	eax, dword ptr [ebx]
	setl	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_17
	sub	esp, 4
	mov	ebx, ebp
	add	ebx, dword ptr 20
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 16
	push	[ebx]
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	push	ebp
	call	@partition_2
	add	esp, 12
	pop	ebx
	mov	eax, ebp
	add	eax, -4
	mov	[eax], ebx
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	dec	eax
	mov	ebx, ebp
	add	ebx, dword ptr 16
	push	eax
	push	[ebx]
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	push	ebp
	call	@qsort_3
	add	esp, 12
	mov	ebx, ebp
	add	ebx, dword ptr 20
	push	[ebx]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	inc	eax
	mov	ebx, ebp
	add	ebx, 12
	push	eax
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
	mov	eax, dword ptr 9
	mov	ebx, 1
	push	eax
	mov	eax, 1
	sub	eax, ebx
	mov	ebx, ebp
	add	ebx, 12
	push	eax
	push	[ebx]
	push	ebp
	call	@qsort_3
@exit_18:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@quicksort_4 endp
main:
	mov	ebp, esp
	lea	ebx, v_i
	mov	[ebx], dword ptr 1
@forloop_20:
	mov	eax, dword ptr [v_i]
	cmp	eax, 10
	jg	@lend_21
	mov	eax, dword ptr [v_i]
	imul	eax, 6180
	add	eax, 19
	mov	ebx, 21
	xor	edx, edx
	idiv	ebx
	mov	ebx, 4
	mov	eax, dword ptr [v_i]
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a
	mov	[eax], edx
@lcontinue_22:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_20
@lend_21:
	mov	eax, offset v_a + 40
	xor	ebx, ebx
@L_23:
	cmp	ebx, 40
	jge	@L_24
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
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
	mov	eax, offset v_a + 40
	xor	ebx, ebx
@L_25:
	cmp	ebx, 40
	jge	@L_26
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_25
@L_26:
	push	40
	push	ebp
	call	@print_1
@exit_19:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
