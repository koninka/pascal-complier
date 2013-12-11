.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	format_str_int db "%d", 0
	fmt_str_new_line db 10
.code
main:
	push	dword ptr 25
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	dword ptr 3
	push	dword ptr 220
	push	dword ptr 17
	pop	ebx
	pop	eax
	xor	edx, edx
	idiv	ebx
	push	edx
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main
