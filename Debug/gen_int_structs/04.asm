.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_i db 4 dup(0)
	format_str_int db "%d", 0
.code
main:
	push	dword ptr 20
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	dword ptr 5
	push	dword ptr [v_i]
	push	dword ptr 20
	pop	ebx
	pop	eax
	imul	ebx
	push	eax
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	dword ptr 25
	push	dword ptr [v_i]
	pop	ebx
	pop	eax
	xor	edx, edx
	idiv	ebx
	push	edx
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main