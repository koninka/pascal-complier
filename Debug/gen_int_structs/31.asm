.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 32 dup(0)
	v_b db 8 dup(0)
	v_c db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	lea	eax, v_b
	mov	[eax], dword ptr 20
	mov	eax, offset v_b + 4
	mov	[eax], dword ptr 29
	mov	eax, offset v_a + 8
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_a + 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	lea	eax, v_b
	mov	ebx, offset v_a + 8
	push	[eax + 4]
	push	[eax]
	mov	eax, ebx
	pop	[eax]
	pop	[eax + 4]
	mov	eax, offset v_a + 8
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_a + 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
