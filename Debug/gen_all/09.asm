.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 4 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	push	20
	push	28
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	push	3
	pop	ebx
	pop	eax
	imul	ebx
	push	eax
	pop	eax
	neg	eax
	push	eax
	push	offset v_a
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_a
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
