.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 32 dup(0)
	v_b db 32 dup(0)
	v_i db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str5 db " ", 0
	fmt_str_new_line db 10, 0
.code
@print_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ebx, ebp
	mov	[ebx - 4], dword ptr 1
@forloop_2:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	cmp	eax, 4
	jg	@lend_3
	mov	eax, ebp
	add	eax, dword ptr 12
	mov	ebx, ebp
	push	eax
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str5
	call	crt_printf
	add	esp, 4
	mov	eax, ebp
	add	eax, dword ptr 28
	mov	ebx, ebp
	push	eax
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
@lcontinue_4:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_2
@lend_3:
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print_0 endp
main:
	mov	ebp, esp
	lea	ebx, v_i
	mov	[ebx], dword ptr 1
@forloop_7:
	mov	eax, dword ptr [v_i]
	cmp	eax, 4
	jg	@lend_8
	lea	eax, v_a
	mov	ebx, 4
	push	1
	push	eax
	mov	eax, dword ptr [v_i]
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	pop	[eax]
	mov	eax, offset v_a + 16
	mov	ebx, 4
	push	2
	push	eax
	mov	eax, dword ptr [v_i]
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	pop	[eax]
@lcontinue_9:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_7
@lend_8:
	mov	eax, offset v_a + 32
	xor	ebx, ebx
@L_10:
	cmp	ebx, 32
	jge	@L_11
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_10
@L_11:
	push	ebp
	call	@print_0
	add	esp, 32
	mov	eax, offset v_a + 32
	xor	ebx, ebx
@L_12:
	cmp	ebx, 32
	jge	@L_13
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_12
@L_13:
	mov	eax, offset v_b - 4
	xor	ebx, ebx
@assignBegin_14:
	cmp	ebx, 32
	jge	@assignEnd_15
	push	eax
	add	[esp], dword ptr 4
	pop	eax
	pop	[eax]
	add	ebx, 4
	jmp	@assignBegin_14
@assignEnd_15:
	mov	eax, offset v_a + 16
	mov	ebx, dword ptr [eax]
	push	[eax + 12]
	push	[eax + 8]
	push	[eax + 4]
	lea	eax, v_b
	pop	[eax + 4]
	pop	[eax + 8]
	pop	[eax + 12]
	mov	[eax], ebx
	mov	eax, offset v_b + 32
	xor	ebx, ebx
@L_16:
	cmp	ebx, 32
	jge	@L_17
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_16
@L_17:
	push	ebp
	call	@print_0
@exit_6:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
