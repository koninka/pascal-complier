.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_m db 4 dup(0)
	v_n db 4 dup(0)
	v_x db 40 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
@generate_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	cmp	eax, dword ptr [v_n]
	sete	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_3
	mov	ebx, ebp
	mov	[ebx - 4], dword ptr 1
@forloop_4:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	cmp	eax, dword ptr [v_n]
	jg	@lend_5
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	add	eax, offset v_x
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
@lcontinue_6:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_4
@lend_5:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_2
@else_3:
	mov	ebx, ebp
	mov	[ebx - 8], dword ptr 1
@forloop_7:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 8]
	cmp	eax, dword ptr [v_m]
	jg	@lend_8
	mov	ebx, ebp
	push	[ebx - 8]
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	inc	eax
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, offset v_x
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	inc	eax
	push	eax
	push	ebp
	call	@generate_0
	add	esp, 4
@lcontinue_9:
	mov	eax, ebp
	add	eax, -8
	inc	dword ptr [eax]
	jmp	@forloop_7
@lend_8:
	jmp	@endif_2
@endif_2:
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@generate_0 endp
main:
	mov	ebp, esp
	lea	eax, v_m
	mov	[eax], dword ptr 2
	lea	eax, v_n
	mov	[eax], dword ptr 3
	push	0
	push	ebp
	call	@generate_0
@exit_10:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
