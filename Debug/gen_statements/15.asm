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
	push	0
	push	offset v_i
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_2:
	push	offset v_i
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	dword ptr [v_i]
	push	1
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset v_i
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr [v_i]
	push	5
	pop	ebx
	pop	eax
	cmp	eax, ebx
	sete	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_4
	jmp	@lcontinue_2
	jmp	@endif_3
@else_4:
	push	dword ptr [v_i]
	push	8
	pop	ebx
	pop	eax
	cmp	eax, ebx
	sete	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@endif_5
	jmp	@lend_1
@endif_5:
	jmp	@endif_3
@endif_3:
	push	dword ptr [v_i]
	push	100
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@lcontinue_2
	jmp	@lend_1
@lend_1:
@exit_0:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
