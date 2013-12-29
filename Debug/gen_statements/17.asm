.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_i db 4 dup(0)
	v_j db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str8 db " ", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	push	1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_1:
	push	dword ptr [v_i]
	push	20
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_2
	push	dword ptr [v_i]
	push	10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@endif_4
	jmp	@lend_2
@endif_4:
	push	1
	push	offset v_j
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_5:
	push	dword ptr [v_j]
	push	20
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_6
	push	offset v_j
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str8
	call	crt_printf
	add	esp, 4
	push	dword ptr [v_j]
	push	dword ptr [v_i]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	sete	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@endif_9
	jmp	@lend_6
@endif_9:
@lcontinue_7:
	push	offset v_j
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_5
@lend_6:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
@lcontinue_3:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_1
@lend_2:
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
