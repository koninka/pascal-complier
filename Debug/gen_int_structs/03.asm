.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_i db 4 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	lea	eax, v_i
	mov	[eax], dword ptr 20
	mov	eax, dword ptr [v_i]
	neg	eax
	lea	ebx, v_i
	mov	[ebx], eax
	lea	eax, v_i
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
