.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	format_str_int db "%d", 0
.code
main:
	push	dword ptr 20
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main
