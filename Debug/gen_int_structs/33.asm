.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 16 dup(0)
	v_b db 16 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	push	23432
	push	offset v_a
	push	4
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
	push	20
	push	offset v_b
	push	4
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
	push	4
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	offset v_b
	push	4
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	offset v_b
	pop	eax
	mov	ebx, [eax + 12]
	push	ebx
	mov	ebx, [eax + 8]
	push	ebx
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	push	offset v_a
	pop	eax
	pop	ebx
	mov	[eax], ebx
	pop	ebx
	mov	[eax + 4], ebx
	pop	ebx
	mov	[eax + 8], ebx
	pop	ebx
	mov	[eax + 12], ebx
	push	offset v_a
	push	4
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	offset v_b
	push	4
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
@exit_0:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
