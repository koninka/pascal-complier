.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_i db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	push	dword ptr 0
	push	offset v_i
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_2:
	push	dword ptr [v_i]
	push	dword ptr 20
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setle	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@lend_1
	push	dword ptr [v_i]
	push	dword ptr 1
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset v_i
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr [v_i]
	push	dword ptr 2
	pop	ebx
	pop	eax
	xor	edx, edx
	idiv	ebx
	push	edx
	push	dword ptr 1
	pop	ebx
	pop	eax
	cmp	eax, ebx
	sete	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@endif_3
	jmp	@lcontinue_2
@endif_3:
	push	offset v_i
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	jmp	@lcontinue_2
@lend_1:
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
