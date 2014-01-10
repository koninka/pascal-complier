.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 16 dup(0)
	v_b db 16 dup(0)
	fmt_int db "%d", 0
	fmt_str3 db " ", 0
	fmt_str4 db " ", 0
	fmt_str5 db " ", 0
.code
@copy_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	mov	eax, ebx
	mov	ebx, ebp
	add	ebx, 12
	push	[eax + 12]
	push	[eax + 8]
	push	[eax + 4]
	push	[eax]
	mov	eax, [ebx]
	add	ebx, 4
	add	ebx, eax
	mov	eax, ebx
	pop	[eax]
	pop	[eax + 4]
	pop	[eax + 8]
	pop	[eax + 12]
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@copy_0 endp
main:
	mov	ebp, esp
	lea	eax, v_a
	mov	[eax], dword ptr 11
	mov	[eax + 4], dword ptr 12
	mov	eax, offset v_a + 8
	mov	[eax], dword ptr 21
	mov	[eax + 4], dword ptr 22
	sub	esp, 16
	lea	eax, v_a
	push	[eax + 12]
	push	[eax + 8]
	push	[eax + 4]
	push	[eax]
	push	16
	push	ebp
	call	@copy_0
	add	esp, 20
	pop	ebx
	lea	eax, v_b
	pop	[eax + 4]
	pop	[eax + 8]
	pop	[eax + 12]
	mov	[eax], ebx
	lea	eax, v_b
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str3
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_b + 4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str4
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_b + 8
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str5
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_b + 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
