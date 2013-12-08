.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 4 dup(0)
	v_b db 4 dup(0)
	format_str_int db "%d", 0
.code
main:
	push	dword ptr 5
	push	offset v_a
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	dword ptr [v_a]
	push	dword ptr 3
	pop	ebx
	pop	eax
	xor	edx, edx
	idiv	ebx
	push	edx
	push	offset v_b
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	dword ptr [v_a]
	push	dword ptr [v_b]
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main
