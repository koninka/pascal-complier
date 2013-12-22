.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 24 dup(0)
	v_c db 12 dup(0)
.code
main:
	mov	ebp, esp
	push	offset v_c
	pop	eax
	mov	ebx, [eax + 8]
	push	ebx
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	push	offset v_a
	push	dword ptr 2
	mov	ebx, dword ptr 12
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	pop	ebx
	mov	[eax + 4], ebx
	pop	ebx
	mov	[eax + 8], ebx
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
