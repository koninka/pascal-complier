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
	push	20
	push	offset v_i
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr [v_i]
	pop	eax
	neg	eax
	push	eax
	push	offset v_i
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_i
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
@exit_0:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
