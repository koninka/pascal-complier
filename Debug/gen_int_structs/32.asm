.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	format_str_int db "%d", 0
	format_str_new_line db "\n", 0
.code
main:
	push	dword ptr 1
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	push	dword ptr 2
	push	dword ptr 5
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	push	dword ptr 10
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset format_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	dword ptr 40
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main
