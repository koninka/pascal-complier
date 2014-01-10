.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fv0 real4 5.500000
	fv1 real4 4.500000
	fv2 real4 10.000000
	fv3 real4 10.000000
	fv4 real4 2.750000
	v_t db 8 dup(0)
	fmt_float db "% 0.14E", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	push	fv0
	push	fv1
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	faddp	st(1), st
	fstp	dword ptr [esp]
	fld	dword ptr [esp]
	sub	esp, 8
	fstp	qword ptr [esp]
	push	offset fmt_float
	call	crt_printf
	add	esp, 12
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	fv2
	push	20
	fild	dword ptr [esp]
	fstp	dword ptr [esp]
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fmulp	st(1), st
	fstp	dword ptr [esp]
	fld	dword ptr [esp]
	sub	esp, 8
	fstp	qword ptr [esp]
	push	offset fmt_float
	call	crt_printf
	add	esp, 12
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	fv3
	push	fv4
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fsubp	st(1), st
	fstp	dword ptr [esp]
	fld	dword ptr [esp]
	sub	esp, 8
	fstp	qword ptr [esp]
	push	offset fmt_float
	call	crt_printf
	add	esp, 12
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	30
	fild	dword ptr [esp]
	fstp	dword ptr [esp]
	pop	ebx
	lea	eax, v_t
	mov	[eax], ebx
	push	10
	fild	dword ptr [esp]
	fstp	dword ptr [esp]
	pop	ebx
	mov	eax, offset v_t + 4
	mov	[eax], ebx
	lea	eax, v_t
	push	[eax]
	mov	eax, offset v_t + 4
	push	[eax]
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fdivp	st(1), st
	fstp	dword ptr [esp]
	fld	dword ptr [esp]
	sub	esp, 8
	fstp	qword ptr [esp]
	push	offset fmt_float
	call	crt_printf
	add	esp, 12
	push	offset fmt_str_new_line
	call	crt_printf
@exit_5:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
