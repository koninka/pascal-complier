.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 16 dup(0)
	fmt_int db "%d", 0
	fmt_str3 db " ", 0
	fmt_str4 db " ", 0
	fmt_str5 db " ", 0
.code
@fill_0 proc
	push	ebp
	mov	ebp, esp
	push	10
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	1
	mov	ebx, 8
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	3
	mov	ebx, 4
	pop	eax
	sub	eax, 3
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	20
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	2
	mov	ebx, 8
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	3
	mov	ebx, 4
	pop	eax
	sub	eax, 3
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	30
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	1
	mov	ebx, 8
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	4
	mov	ebx, 4
	pop	eax
	sub	eax, 3
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	40
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	2
	mov	ebx, 8
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	4
	mov	ebx, 4
	pop	eax
	sub	eax, 3
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@fill_0 endp
main:
	mov	ebp, esp
	push	offset v_a
	push	ebp
	call	@fill_0
	add	esp, 4
	push	offset v_a
	push	1
	mov	ebx, 8
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	3
	mov	ebx, 4
	pop	eax
	sub	eax, 3
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str3
	call	crt_printf
	add	esp, 4
	push	offset v_a
	push	2
	mov	ebx, 8
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	3
	mov	ebx, 4
	pop	eax
	sub	eax, 3
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str4
	call	crt_printf
	add	esp, 4
	push	offset v_a
	push	1
	mov	ebx, 8
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	4
	mov	ebx, 4
	pop	eax
	sub	eax, 3
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str5
	call	crt_printf
	add	esp, 4
	push	offset v_a
	push	2
	mov	ebx, 8
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	4
	mov	ebx, 4
	pop	eax
	sub	eax, 3
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
@exit_2:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
