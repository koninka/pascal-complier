.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_c db 4 dup(0)
	fmt_int db "%d", 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	push	[ebx]
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, 12
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, 12
	push	ebx
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
	push	5
	push	4
	push	ebp
	call	@foo_0
	add	esp, 8
@exit_2:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
