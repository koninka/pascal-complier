.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_m db 4 dup(0)
	v_n db 4 dup(0)
	v_i db 4 dup(0)
	v_x db 40 dup(0)
	v_yes db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
@next_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	eax, ebp
	add	eax, -4
	mov	ebx, dword ptr [v_n]
	mov	[eax], ebx
@lcontinue_3:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	xor	ebx, ebx
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	mov	ebx, ebp
	add	ebx, 12
	push	eax
	push	[ebx]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	eax, dword ptr [eax]
	cmp	eax, dword ptr [v_m]
	sete	al
	movzx	eax, al
	mov	ebx, eax
	pop	eax
	and	eax, ebx
	xor	ebx, ebx
	cmp	eax, ebx
	je	@lend_2
	mov	ebx, ebp
	add	ebx, 12
	push	1
	push	[ebx]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	pop	[eax]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	dec	eax
	mov	ebx, ebp
	add	ebx, -4
	push	eax
	mov	eax, ebx
	pop	[eax]
	jmp	@lcontinue_3
@lend_2:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	xor	ebx, ebx
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_5
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	eax, dword ptr [eax]
	inc	eax
	mov	ebx, ebp
	add	ebx, 12
	push	eax
	push	[ebx]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	pop	[eax]
	mov	ebx, ebp
	add	ebx, dword ptr 16
	mov	eax, dword ptr [ebx]
	mov	[eax], dword ptr 1
	jmp	@endif_4
@else_5:
	mov	ebx, ebp
	add	ebx, dword ptr 16
	mov	eax, dword ptr [ebx]
	xor	ebx, ebx
	mov	[eax], ebx
	jmp	@endif_4
@endif_4:
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@next_0 endp
main:
	mov	ebp, esp
	lea	eax, v_m
	mov	[eax], dword ptr 2
	lea	eax, v_n
	mov	[eax], dword ptr 3
	lea	ebx, v_i
	mov	[ebx], dword ptr 1
@forloop_7:
	mov	eax, dword ptr [v_i]
	cmp	eax, dword ptr [v_n]
	jg	@lend_8
	mov	ebx, 4
	mov	eax, dword ptr [v_i]
	dec	eax
	imul	eax, ebx
	add	eax, offset v_x
	mov	[eax], dword ptr 1
@lcontinue_9:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_7
@lend_8:
@lcontinue_11:
	lea	ebx, v_i
	mov	[ebx], dword ptr 1
@forloop_12:
	mov	eax, dword ptr [v_i]
	cmp	eax, dword ptr [v_n]
	jg	@lend_13
	mov	ebx, 4
	mov	eax, dword ptr [v_i]
	dec	eax
	imul	eax, ebx
	add	eax, offset v_x
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
@lcontinue_14:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_12
@lend_13:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	offset v_yes
	push	offset v_x
	push	ebp
	call	@next_0
	add	esp, 8
	xor	ebx, ebx
	cmp	dword ptr [v_yes], ebx
	setle	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@lcontinue_11
	jmp	@lend_10
@lend_10:
@exit_6:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
