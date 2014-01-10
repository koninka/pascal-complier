.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 60 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	mov	eax, offset v_a + 28
	mov	[eax], dword ptr 77
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
