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
	mov	eax, offset v_a + 12
	mov	ebx, 4
	push	eax
	mov	eax, dword ptr 2
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, dword ptr -5
	mov	ebx, 4
	push	eax
	mov	eax, dword ptr 2
	imul	eax, ebx
	pop	ebx
	add	eax, offset v_c
	mov	[eax], ebx
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
	mov	eax, offset v_a + 12
	mov	ebx, 4
	push	eax
	mov	eax, dword ptr 2
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
