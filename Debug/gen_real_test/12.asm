.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fv2 real4 17.004300
	fv3 real4 432.504000
	fmt_float db " %0.14E", 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	push	fv3
	fld	dword ptr [esp]
	fchs
	fstp	dword ptr [esp]
	sub	esp, 4
	push	ebp
	call	@bar_1
	add	esp, 0
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	faddp	st(1), st
	fstp	dword ptr [esp]
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_4:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
@bar_1 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	add	ebx, 12
	push	[ebx]
	push	fv2
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fmulp	st(1), st
	fstp	dword ptr [esp]
	mov	ebx, ebp
	add	ebx, 12
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_5:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@bar_1 endp
main:
	mov	ebp, esp
	sub	esp, 4
	push	20
	fild	dword ptr [esp]
	fstp	dword ptr [esp]
	push	ebp
	call	@foo_0
	add	esp, 4
	fld	dword ptr [esp]
	sub	esp, 8
	fstp	qword ptr [esp]
	push	offset fmt_float
	call	crt_printf
	add	esp, 12
@exit_6:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
