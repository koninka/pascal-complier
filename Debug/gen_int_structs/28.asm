.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 24 dup(0)
	v_b db 24 dup(0)
	format_str_int db "%d", 0
.code
main:
	push	dword ptr 146
	push	offset v_b
	push	dword ptr 2
	mov	ebx, dword ptr 12
	pop	eax
	sub	eax, dword ptr 1
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 3
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	offset v_b
	push	dword ptr 2
	mov	ebx, dword ptr 12
	pop	eax
	sub	eax, dword ptr 1
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 3
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	[eax]
	push	offset v_a
	push	dword ptr 1
	mov	ebx, dword ptr 12
	pop	eax
	sub	eax, dword ptr 1
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 2
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	offset v_a
	push	dword ptr 1
	mov	ebx, dword ptr 12
	pop	eax
	sub	eax, dword ptr 1
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 2
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main