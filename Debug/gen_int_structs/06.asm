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
	lea	eax, v_a
	mov	[eax], dword ptr 5
	mov	ebx, 3
	mov	eax, dword ptr [v_a]
	xor	edx, edx
	idiv	ebx
	lea	eax, v_b
	mov	[eax], edx
	mov	eax, dword ptr [v_a]
	add	eax, dword ptr [v_b]
	push	eax
	push	offset fmt_int
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
