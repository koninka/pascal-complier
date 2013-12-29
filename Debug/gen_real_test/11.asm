.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fv1 real4 2.430000
	v_a db 160 dup(0)
	fmt_float db " %0.14E", 0
	fmt_str_new_line db 10, 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	0
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_3:
	mov	ebx, ebp
	push	[ebx - 4]
	push	40
	push	1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_4
	push	658943
	push	19
	pop	ebx
	pop	eax
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
	push	[ebx - 4]
	push	1
	pop	ebx
	pop	eax
	add	eax, ebx
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
	push	[ebx - 4]
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_5:
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_3
@lend_4:
	push	0
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_6:
	mov	ebx, ebp
	push	[ebx - 4]
	push	40
	push	1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_7
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
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_6
@lend_7:
@exit_2:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
	push	offset v_a
	pop	eax
	mov	ecx, 160
	add	eax, ecx
	mov	ebx, 0
@L_10:
	cmp	ebx, ecx
	jge	@L_11
	sub	eax, 4
	mov	edx, [eax]
	push	edx
	add	ebx, 4
	jmp	@L_10
@L_11:
	push	160
	push	ebp
	call	@foo_0
	add	esp, 164
@exit_9:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
