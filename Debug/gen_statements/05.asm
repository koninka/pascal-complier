.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_i db 4 dup(0)
	v_a db 44 dup(0)
	fmt_int db "%d", 0
	fmt_str6 db " ", 0
.code
main:
	mov	ebp, esp
	push	dword ptr 9
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_1:
	push	dword ptr [v_i]
	push	dword ptr 1
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jl	@lend_2
	push	dword ptr 10
	push	dword ptr [v_i]
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	push	dword ptr 2
	pop	ebx
	pop	eax
	imul	ebx
	push	eax
	push	offset v_a
	push	dword ptr [v_i]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_3:
	push	offset v_i
	pop	eax
	sub	[eax], dword ptr 1
	jmp	@forloop_1
@lend_2:
	push	dword ptr 10
	push	offset v_i
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_5:
	push	dword ptr [v_i]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	push	offset v_i
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_a
	push	dword ptr [v_i]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str6
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_a
	push	dword ptr [v_i]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	[eax]
	push	dword ptr 0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	sete	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@lcontinue_5
	jmp	@lend_4
@lend_4:
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
