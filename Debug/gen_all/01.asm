.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_i db 4 dup(0)
	v_j db 4 dup(0)
	v_a db 80 dup(0)
	fmt_int db "%d", 0
	fmt_str8 db " ", 0
	fmt_str_new_line db 10, 0
.code
@init_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	mov	[eax], dword ptr 1
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 40
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 2
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 20
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 3
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 60
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 4
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 4
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 5
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 44
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 6
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 24
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 7
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 64
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 8
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 8
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 9
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 48
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 10
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 28
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 11
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 68
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 12
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 12
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 13
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 52
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 14
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 32
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 15
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 72
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 16
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 16
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 17
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 56
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 18
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 36
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 19
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 76
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 20
@exit_3:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@init_0 endp
@writearr_1 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ebx, ebp
	add	ebx, -4
	xor	eax, eax
	mov	[ebx], eax
@forloop_5:
	mov	ebx, ebp
	mov	eax, dword ptr 19
	push	[ebx - 4]
	mov	ebx, eax
	pop	eax
	cmp	eax, ebx
	jg	@lend_6
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
	add	esp, 8
	push	offset fmt_str8
	call	crt_printf
	add	esp, 4
@lcontinue_7:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_5
@lend_6:
	push	offset fmt_str_new_line
	call	crt_printf
@exit_4:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@writearr_1 endp
@swap_2 proc
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
@exit_9:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@swap_2 endp
main:
	mov	ebp, esp
	push	offset v_a
	push	ebp
	call	@init_0
	add	esp, 4
	mov	eax, offset v_a + 80
	xor	ebx, ebx
@L_11:
	cmp	ebx, 80
	jge	@L_12
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_11
@L_12:
	push	80
	push	ebp
	call	@writearr_1
	add	esp, 84
	lea	ebx, v_i
	mov	[ebx], dword ptr 2
@forloop_13:
	mov	eax, dword ptr [v_i]
	cmp	eax, 20
	jg	@lend_14
	lea	ebx, v_j
	mov	eax, dword ptr [v_i]
	mov	[ebx], eax
@forloop_16:
	mov	eax, dword ptr [v_j]
	cmp	eax, 2
	jl	@lend_17
	mov	ebx, 4
	mov	eax, dword ptr [v_j]
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a
	mov	ebx, 1
	push	[eax]
	mov	eax, dword ptr [v_j]
	sub	eax, ebx
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a
	mov	ebx, dword ptr [eax]
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_19
	mov	eax, dword ptr [v_j]
	dec	eax
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a
	mov	ebx, 4
	push	eax
	mov	eax, dword ptr [v_j]
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a
	push	eax
	push	ebp
	call	@swap_2
	add	esp, 8
@endif_19:
@lcontinue_18:
	lea	eax, v_j
	dec	dword ptr [eax]
	jmp	@forloop_16
@lend_17:
@lcontinue_15:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_13
@lend_14:
	mov	eax, offset v_a + 80
	xor	ebx, ebx
@L_20:
	cmp	ebx, 80
	jge	@L_21
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_20
@L_21:
	push	80
	push	ebp
	call	@writearr_1
@exit_10:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
