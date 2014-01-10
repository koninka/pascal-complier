.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fv1 real4 2.430000
	v_a db 160 dup(0)
	fmt_float db "% 0.14E", 0
	fmt_str_new_line db 10, 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ebx, ebp
	add	ebx, -4
	xor	eax, eax
	mov	[ebx], eax
@forloop_3:
	mov	ebx, ebp
	mov	eax, dword ptr 39
	push	[ebx - 4]
	mov	ebx, eax
	pop	eax
	cmp	eax, ebx
	jg	@lend_4
	mov	ebx, 19
	mov	eax, 658943
	xor	edx, edx
	idiv	ebx
	push	edx
	fild	dword ptr [esp]
	fstp	dword ptr [esp]
	push	fv1
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fmulp	st(1), st
	fstp	dword ptr [esp]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	inc	eax
	push	eax
	fild	dword ptr [esp]
	fstp	dword ptr [esp]
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fdivp	st(1), st
	fstp	dword ptr [esp]
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
	pop	[eax]
@lcontinue_5:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_3
@lend_4:
	mov	ebx, ebp
	add	ebx, -4
	xor	eax, eax
	mov	[ebx], eax
@forloop_6:
	mov	ebx, ebp
	mov	eax, dword ptr 39
	push	[ebx - 4]
	mov	ebx, eax
	pop	eax
	cmp	eax, ebx
	jg	@lend_7
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
	fld	dword ptr [esp]
	sub	esp, 8
	fstp	qword ptr [esp]
	push	offset fmt_float
	call	crt_printf
	add	esp, 12
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
@lcontinue_8:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_6
@lend_7:
@exit_2:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
	mov	eax, offset v_a + 160
	xor	ebx, ebx
@L_10:
	cmp	ebx, 160
	jge	@L_11
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_10
@L_11:
	push	160
	push	ebp
	call	@foo_0
@exit_9:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
