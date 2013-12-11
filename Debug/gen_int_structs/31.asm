.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 32 dup(0)
	v_b db 8 dup(0)
	v_c db 4 dup(0)
	format_str_int db "%d", 0
	fmt_str_new_line db 10
.code
main:
	push	dword ptr 20
	push	offset v_b
	push	dword ptr 1
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
	push	dword ptr 29
	push	offset v_b
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
	pop	eax
	lea	eax, [eax + 8]
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 1
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_a
	pop	eax
	lea	eax, [eax + 8]
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 8
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_b
	pop	ebx
	mov	eax, [ebx + 4]
	push	eax
	mov	eax, [ebx]
	push	eax
	push	offset v_a
	pop	eax
	lea	eax, [eax + 8]
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 8
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
	push	offset v_a
	pop	eax
	lea	eax, [eax + 8]
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	xor	edx, edx
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 1
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_a
	pop	eax
	lea	eax, [eax + 8]
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 8
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	ret
end main
