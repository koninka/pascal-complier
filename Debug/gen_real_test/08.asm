.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fv0 real4 43.430000
	v_a db 40 dup(0)
	fmt_float db " %0.14E", 0
.code
main:
	mov	ebp, esp
	push	fv0
	fld	dword ptr [esp]
	fchs
	fstp	dword ptr [esp]
	push	offset v_a
	push	5
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_a
	push	5
	mov	ebx, 4
	pop	eax
	sub	eax, 1
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
@exit_1:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
