.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 24 dup(0)
	v_d db 4 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	push	37
	push	offset v_d
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr [v_d]
	push	offset v_a
	push	1
	mov	ebx, 12
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	2
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_a
	push	1
	mov	ebx, 12
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	2
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
@exit_0:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
