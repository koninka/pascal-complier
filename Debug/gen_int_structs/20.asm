.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 24 dup(0)
	v_c db 12 dup(0)
.code
main:
	push	offset v_c
	pop	ebx
	mov	eax, [ebx + 8]
	push	eax
	mov	eax, [ebx + 4]
	push	eax
	mov	eax, [ebx]
	push	eax
	push	offset v_a
	push	dword ptr 2
	mov	ebx, dword ptr 12
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
	pop	eax
	mov	[ebx + 4], eax
	pop	eax
	mov	[ebx + 8], eax
	ret
end main
