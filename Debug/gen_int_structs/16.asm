.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_r db 4 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	lea	eax, v_r
	mov	[eax], dword ptr 193
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
