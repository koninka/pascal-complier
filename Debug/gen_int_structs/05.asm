.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 4 dup(0)
	v_b db 4 dup(0)
	format_str_int db "%d", 0
	fmt_str_new_line db 10
.code
main:
	push	dword ptr 5
	push	offset v_a
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	dword ptr [v_a]
	push	offset v_b
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	offset v_a
	pop	eax
	push	dword ptr [eax]
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_b
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
