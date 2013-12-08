.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_r db 4 dup(0)
	format_str_int db "%d", 0
.code
main:
	push	dword ptr 25
	pop	eax
	neg	eax
	push	eax
	push	offset v_r
	pop	eax
	lea	eax, [eax]
	push	eax
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	offset v_r
	pop	eax
	lea	eax, [eax]
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main
