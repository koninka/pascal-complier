.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 8 dup(0)
	v_b db 8 dup(0)
	fmt_int db "%d", 0
	fmt_str3 db " ", 0
.code
@swap_0 proc
	push	ebp
	mov	ebp, esp
	mov	eax, ebp
	add	eax, dword ptr 16
	mov	ebx, ebp
	add	ebx, dword ptr 20
	mov	eax, dword ptr [eax]
	imul	eax, dword ptr [ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 24
	push	eax
	mov	eax, ebx
	pop	[eax]
	mov	eax, ebp
	add	eax, dword ptr 12
	mov	ebx, ebp
	add	ebx, dword ptr 20
	mov	eax, dword ptr [eax]
	add	eax, dword ptr [ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 24
	push	eax
	mov	eax, ebx
	pop	ebx
	add	eax, 4
	mov	[eax], ebx
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@swap_0 endp
main:
	mov	ebp, esp
	lea	eax, v_a
	mov	[eax], dword ptr 4
	mov	[eax + 4], dword ptr 11
	sub	esp, 8
	lea	eax, v_a
	push	3
	push	[eax + 4]
	push	[eax]
	push	ebp
	call	@swap_0
	add	esp, 12
	pop	ebx
	lea	eax, v_b
	pop	[eax + 4]
	mov	[eax], ebx
	lea	eax, v_b
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str3
	call	crt_printf
	add	esp, 12
	mov	eax, offset v_b + 4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
