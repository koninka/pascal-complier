.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 4 dup(0)
	v_b db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str3 db ": ", 0
	fmt_str6 db " ", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	push	dword ptr 10
	push	offset v_a
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_2:
	push	offset v_a
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str3
	call	crt_printf
	add	esp, dword ptr 4
	push	dword ptr 10
	push	offset v_b
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_5:
	push	offset v_b
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str6
	call	crt_printf
	add	esp, dword ptr 4
	push	dword ptr [v_b]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	push	offset v_b
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr [v_b]
	push	dword ptr 1
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@endif_7
	jmp	@lend_4
@endif_7:
	push	dword ptr 0
	push	dword ptr 0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@lcontinue_5
	jmp	@lend_4
@lend_4:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	dword ptr [v_a]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	push	offset v_a
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr [v_a]
	push	dword ptr 1
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@endif_8
	jmp	@lend_1
@endif_8:
	push	dword ptr 0
	push	dword ptr 0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@lcontinue_2
	jmp	@lend_1
@lend_1:
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
