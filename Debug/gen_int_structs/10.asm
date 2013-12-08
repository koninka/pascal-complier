.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 4 dup(0)
	format_str_int db "%d", 0
.code
main:
	push	dword ptr [v_a]
	push	dword ptr 0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	sete	al
	movzx	eax, al
	push	eax
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main
