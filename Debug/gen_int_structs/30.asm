.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 32 dup(0)
	v_c db 4 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	lea	ebx, v_c
	mov	[ebx], dword ptr -89
	mov	eax, offset v_a + 12
	mov	ebx, dword ptr [v_c]
	mov	[eax], ebx
	mov	eax, offset v_a + 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
