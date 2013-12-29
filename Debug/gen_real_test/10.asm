.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fv1 real4 32.540000
	fv2 real4 3.590000
	fv3 real4 2.890000
	v_a db 4 dup(0)
	fmt_float db " %0.14E", 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	fv1
	push	fv2
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fmulp	st(1), st
	fstp	dword ptr [esp]
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	faddp	st(1), st
	fstp	dword ptr [esp]
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 4]
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	faddp	st(1), st
	fstp	dword ptr [esp]
	push	offset v_a
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_4:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
	push	fv3
	fld	dword ptr [esp]
	fchs
	fstp	dword ptr [esp]
	push	ebp
	call	@foo_0
	add	esp, 4
	push	offset v_a
	pop	eax
	push	dword ptr [eax]
	fld	dword ptr [esp]
	sub	esp, 8
	fstp	qword ptr [esp]
	push	offset fmt_float
	call	crt_printf
	add	esp, 12
@exit_5:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
