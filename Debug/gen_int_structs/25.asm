.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_c db 12 dup(0)
	v_d db 4 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	lea	eax, v_d
	mov	[eax], dword ptr 35
	lea	eax, v_c
	mov	ebx, dword ptr [v_d]
	mov	[eax], ebx
	mov	ebx, 4
	lea	eax, v_c
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
