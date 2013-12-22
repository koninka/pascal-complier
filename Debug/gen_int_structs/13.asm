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
	push	dword ptr 25
	pop	eax
	neg	eax
	push	eax
	push	offset v_r
	pop	eax
	add	eax, dword ptr 0
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_r
	pop	eax
	add	eax, dword ptr 0
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
