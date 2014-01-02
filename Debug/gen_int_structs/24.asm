.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_c db 12 dup(0)
	v_d db 4 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	push	20
	push	offset v_c
	push	1
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
	push	offset v_c
	push	1
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ebx, [eax]
	push	ebx
	push	offset v_d
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_d
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
