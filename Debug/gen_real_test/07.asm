.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fv0 real4 5.500000
	fmt_float db " %0.14E", 0
.code
main:
	mov	ebp, esp
	push	fv0
	fld	dword ptr [esp]
	fchs
	fstp	dword ptr [esp]
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
