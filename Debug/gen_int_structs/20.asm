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
	lea	eax, v_c
	mov	ebx, 12
	push	[eax + 8]
	push	[eax + 4]
	push	[eax]
	mov	eax, ebx
	pop	ebx
	add	eax, offset v_a
	pop	[eax + 4]
	pop	[eax + 8]
	mov	[eax], ebx
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
