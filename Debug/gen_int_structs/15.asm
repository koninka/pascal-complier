.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 8 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	push	dword ptr 39
	push	offset v_a
	pop	eax
	add	eax, dword ptr 0
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 5
	push	offset v_a
	pop	eax
	add	eax, dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_a
	pop	eax
	add	eax, dword ptr 0
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_a
	pop	eax
	add	eax, dword ptr 4
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
