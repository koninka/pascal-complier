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
	lea	ebx, v_i
	mov	[ebx], dword ptr 9
@forloop_1:
	mov	eax, dword ptr [v_i]
	cmp	eax, 1
	jl	@lend_2
	mov	eax, 10
	sub	eax, dword ptr [v_i]
	mov	ebx, 2
	imul	ebx
	mov	ebx, 4
	push	eax
	mov	eax, dword ptr [v_i]
	imul	eax, ebx
	pop	ebx
	add	eax, offset v_a
	mov	[eax], ebx
@lcontinue_3:
	lea	eax, v_i
	dec	dword ptr [eax]
	jmp	@forloop_1
@lend_2:
	lea	eax, v_i
	mov	[eax], dword ptr 10
@lcontinue_5:
	mov	eax, dword ptr [v_i]
	dec	eax
	lea	ebx, v_i
	mov	[ebx], eax
	mov	eax, dword ptr [v_i]
	imul	eax, 4
	add	eax, offset v_a
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str6
	call	crt_printf
	add	esp, 4
	mov	eax, dword ptr [v_i]
	imul	eax, 4
	add	eax, offset v_a
	xor	ebx, ebx
	cmp	dword ptr [eax], ebx
	sete	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@lcontinue_5
	jmp	@lend_4
@lend_4:
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
