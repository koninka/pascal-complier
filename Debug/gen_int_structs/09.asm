.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 4 dup(0)
	format_str_int db "%d", 0
.code
main:
	push	dword ptr 20
	push	dword ptr 28
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	push	dword ptr 3
	pop	ebx
	pop	eax
	imul	ebx
	push	eax
	pop	eax
	neg	eax
	push	eax
	push	offset v_a
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	offset v_a
	pop	eax
	push	dword ptr [eax]
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main
