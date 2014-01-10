.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 80 dup(0)
	v_i db 4 dup(0)
	v_j db 4 dup(0)
	v_td db 8 dup(0)
	fmt_int db "%d", 0
	fmt_str9 db " => ", 0
	fmt_str_new_line db 10, 0
	fmt_str14 db "before sort:", 0
	fmt_str24 db "after sort:", 0
.code
@less_0 proc
	push	ebp
	mov	ebp, esp
	mov	eax, ebp
	add	eax, dword ptr 12
	mov	ebx, ebp
	add	ebx, dword ptr 20
	push	[eax]
	mov	eax, ebx
	mov	ebx, dword ptr [eax]
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_4
	mov	eax, ebp
	mov	[eax + 28], dword ptr 1
	jmp	@endif_3
@else_4:
	mov	eax, ebp
	add	eax, dword ptr 28
	xor	ebx, ebx
	mov	[eax], ebx
	jmp	@endif_3
@endif_3:
@exit_2:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@less_0 endp
@print_1 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ebx, ebp
	mov	[ebx - 4], dword ptr 1
@forloop_6:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	cmp	eax, 10
	jg	@lend_7
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	push	ebx
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 8
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str9
	call	crt_printf
	add	esp, 12
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	push	ebx
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 8
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	add	eax, 4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 12
@lcontinue_8:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_6
@lend_7:
@exit_5:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print_1 endp
main:
	mov	ebp, esp
	lea	ebx, v_i
	mov	[ebx], dword ptr 1
@forloop_11:
	mov	eax, dword ptr [v_i]
	cmp	eax, 10
	jg	@lend_12
	mov	ebx, 8
	mov	eax, dword ptr [v_i]
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a + 4
	mov	ebx, dword ptr [v_i]
	mov	[eax], ebx
	mov	eax, 11
	sub	eax, dword ptr [v_i]
	mov	ebx, 8
	push	eax
	mov	eax, dword ptr [v_i]
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, offset v_a
	mov	[eax], ebx
@lcontinue_13:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_11
@lend_12:
	push	offset fmt_str14
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	mov	eax, offset v_a + 80
	xor	ebx, ebx
@L_15:
	cmp	ebx, 80
	jge	@L_16
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_15
@L_16:
	push	80
	push	ebp
	call	@print_1
	add	esp, 84
	lea	ebx, v_i
	mov	[ebx], dword ptr 2
@forloop_17:
	mov	eax, dword ptr [v_i]
	cmp	eax, 10
	jg	@lend_18
	lea	ebx, v_j
	mov	eax, dword ptr [v_i]
	mov	[ebx], eax
@forloop_20:
	mov	eax, dword ptr [v_j]
	cmp	eax, 2
	jl	@lend_21
	sub	esp, 4
	mov	ebx, 8
	mov	eax, dword ptr [v_j]
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a
	mov	ebx, 1
	push	[eax + 4]
	push	[eax]
	mov	eax, dword ptr [v_j]
	sub	eax, ebx
	mov	ebx, 8
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a
	push	[eax + 4]
	push	[eax]
	push	ebp
	call	@less_0
	add	esp, 16
	pop	eax
	xor	ebx, ebx
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_23
	mov	ebx, 8
	mov	eax, dword ptr [v_j]
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a
	mov	ebx, dword ptr [eax]
	push	[eax + 4]
	lea	eax, v_td
	pop	[eax + 4]
	mov	[eax], ebx
	mov	eax, dword ptr [v_j]
	dec	eax
	mov	ebx, 8
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a
	mov	ebx, 8
	push	[eax + 4]
	push	[eax]
	mov	eax, dword ptr [v_j]
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, offset v_a
	pop	[eax + 4]
	mov	[eax], ebx
	lea	eax, v_td
	mov	ebx, 1
	push	[eax + 4]
	push	[eax]
	mov	eax, dword ptr [v_j]
	sub	eax, ebx
	mov	ebx, 8
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, offset v_a
	pop	[eax + 4]
	mov	[eax], ebx
@endif_23:
@lcontinue_22:
	lea	eax, v_j
	dec	dword ptr [eax]
	jmp	@forloop_20
@lend_21:
@lcontinue_19:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_17
@lend_18:
	push	offset fmt_str24
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	mov	eax, offset v_a + 80
	xor	ebx, ebx
@L_25:
	cmp	ebx, 80
	jge	@L_26
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_25
@L_26:
	push	80
	push	ebp
	call	@print_1
@exit_10:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
