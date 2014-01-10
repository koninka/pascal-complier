.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_d db 4 dup(0)
	fmt_int db "%d", 0
.code
@proc_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	mov	[eax], dword ptr 20
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@proc_0 endp
main:
	mov	ebp, esp
	push	offset v_d
	push	ebp
	call	@proc_0
	add	esp, 4
	lea	eax, v_d
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
