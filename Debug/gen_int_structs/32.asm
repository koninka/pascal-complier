.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	push	dword ptr 1
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	dword ptr 2
	push	dword ptr 5
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	dword ptr 10
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	dword ptr 40
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
