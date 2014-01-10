.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 4 dup(0)
	v_b db 4 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	lea	eax, v_b
	mov	[eax], dword ptr 29
	lea	eax, v_a
	mov	ebx, dword ptr [v_b]
	mov	[eax], ebx
	lea	eax, v_a
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
