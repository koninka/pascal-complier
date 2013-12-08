.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 60 dup(0)
	format_str_int db "%d", 0
.code
main:
	push	dword ptr 77
	push	offset v_a
	push	dword ptr 2
	mov	ebx, dword ptr 12
	pop	eax
	sub	eax, dword ptr 0
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	lea	eax, [eax + 4]
	push	eax
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	offset v_a
	push	dword ptr 2
	mov	ebx, dword ptr 12
	pop	eax
	sub	eax, dword ptr 0
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	lea	eax, [eax + 4]
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main
