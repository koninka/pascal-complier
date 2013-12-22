.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 24 dup(0)
	v_c db 12 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	push	offset v_a
	push	dword ptr 2
	mov	ebx, dword ptr 12
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 3
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	dword ptr 5
	pop	eax
	neg	eax
	push	eax
	push	offset v_c
	push	dword ptr 3
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
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
	push	offset v_a
	push	dword ptr 2
	mov	ebx, dword ptr 12
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 3
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
