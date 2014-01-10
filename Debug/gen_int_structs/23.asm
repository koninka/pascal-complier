.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 16 dup(0)
	v_tmp db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	mov	eax, offset v_a + 4
	mov	[eax], dword ptr 3
	lea	eax, v_a
	mov	[eax], dword ptr 4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_a + 4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	lea	eax, v_a
	mov	ebx, dword ptr [eax]
	push	[eax + 4]
	lea	eax, v_tmp
	mov	[eax], ebx
	mov	eax, offset v_a + 4
	mov	ebx, dword ptr [eax]
	push	[eax + 4]
	lea	eax, v_a
	mov	[eax], ebx
	add	eax, 4
	mov	ebx, dword ptr [v_tmp]
	mov	[eax], ebx
	lea	eax, v_a
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_a + 4
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
