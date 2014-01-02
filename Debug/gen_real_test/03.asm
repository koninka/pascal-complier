.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_f db 4 dup(0)
	fmt_float db "% 0.14E", 0
.code
main:
	mov	ebp, esp
	push	5
	fild	dword ptr [esp]
	fstp	dword ptr [esp]
	push	offset v_f
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_f
	pop	eax
	push	dword ptr [eax]
	fld	dword ptr [esp]
	sub	esp, 8
	fstp	qword ptr [esp]
	push	offset fmt_float
	call	crt_printf
	add	esp, 12
@exit_0:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
