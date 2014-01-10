.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 24 dup(0)
	v_c db 12 dup(0)
	v_d db 4 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	mov	eax, offset v_a + 4
	mov	[eax], dword ptr 64
	mov	ebx, 6
	push	[eax + 8]
	push	[eax + 4]
	mov	eax, dword ptr [eax]
	add	eax, ebx
	lea	ebx, v_d
	mov	[ebx], eax
	lea	eax, v_d
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
