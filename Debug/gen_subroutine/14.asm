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
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	pop	eax
	mov	ebx, [eax + 12]
	push	ebx
	mov	ebx, [eax + 8]
	push	ebx
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	add	ebx, eax
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	pop	ebx
	mov	[eax + 4], ebx
	pop	ebx
	mov	[eax + 8], ebx
	pop	ebx
	mov	[eax + 12], ebx
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@copy_0 endp
main:
	mov	ebp, esp
	push	dword ptr 11
	push	offset v_a
	push	dword ptr 1
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 12
	push	offset v_a
	push	dword ptr 1
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 2
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 21
	push	offset v_a
	push	dword ptr 2
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 22
	push	offset v_a
	push	dword ptr 2
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 2
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	sub	esp, dword ptr 16
	push	offset v_a
	pop	eax
	mov	ebx, [eax + 12]
	push	ebx
	mov	ebx, [eax + 8]
	push	ebx
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	push	dword ptr 16
	push	ebp
	call	@copy_0
	add	esp, dword ptr 20
	push	offset v_b
	pop	eax
	pop	ebx
	mov	[eax], ebx
	pop	ebx
	mov	[eax + 4], ebx
	pop	ebx
	mov	[eax + 8], ebx
	pop	ebx
	mov	[eax + 12], ebx
	push	offset v_b
	push	dword ptr 1
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str3
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_b
	push	dword ptr 1
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 2
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str4
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_b
	push	dword ptr 2
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str5
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_b
	push	dword ptr 2
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 2
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
@exit_2:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
