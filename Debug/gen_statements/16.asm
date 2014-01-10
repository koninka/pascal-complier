.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 400 dup(0)
	v_i db 4 dup(0)
	v_j db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str5 db " ", 0
	fmt_str_new_line db 10, 0
.code
@p_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ebx, ebp
	mov	[ebx - 4], dword ptr 1
@forloop_2:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	cmp	eax, 10
	jg	@lend_3
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	push	ebx
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str5
	call	crt_printf
	add	esp, 12
@lcontinue_4:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_2
@lend_3:
	push	offset fmt_str_new_line
	call	crt_printf
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@p_0 endp
main:
	mov	ebp, esp
	lea	ebx, v_i
	mov	[ebx], dword ptr 1
@forloop_7:
	mov	eax, dword ptr [v_i]
	cmp	eax, 10
	jg	@lend_8
	lea	ebx, v_j
	mov	[ebx], dword ptr 1
@forloop_10:
	mov	eax, dword ptr [v_j]
	cmp	eax, 10
	jg	@lend_11
	mov	eax, 2
	imul	eax, dword ptr [v_j]
	mov	ebx, eax
	mov	eax, dword ptr [v_i]
	add	eax, ebx
	mov	ebx, 40
	push	eax
	mov	eax, dword ptr [v_i]
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a
	mov	ebx, 4
	push	eax
	mov	eax, dword ptr [v_j]
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	pop	[eax]
@lcontinue_12:
	lea	eax, v_j
	inc	dword ptr [eax]
	jmp	@forloop_10
@lend_11:
@lcontinue_9:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_7
@lend_8:
	lea	ebx, v_i
	mov	[ebx], dword ptr 1
@forloop_13:
	mov	eax, dword ptr [v_i]
	cmp	eax, 10
	jg	@lend_14
	mov	ebx, 40
	mov	eax, dword ptr [v_i]
	dec	eax
	imul	eax, ebx
	add	eax, offset v_a + 40
	xor	ebx, ebx
@L_16:
	cmp	ebx, 40
	jge	@L_17
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_16
@L_17:
	push	40
	push	ebp
	call	@p_0
	add	esp, 44
@lcontinue_15:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_13
@lend_14:
@exit_6:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
