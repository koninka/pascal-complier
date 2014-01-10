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
	lea	eax, v_i
	xor	ebx, ebx
	mov	[eax], ebx
@lcontinue_2:
	mov	eax, dword ptr [v_i]
	cmp	eax, 20
	setle	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@lend_1
	mov	eax, dword ptr [v_i]
	inc	eax
	lea	ebx, v_i
	mov	[ebx], eax
	mov	ebx, 2
	mov	eax, dword ptr [v_i]
	xor	edx, edx
	idiv	ebx
	mov	eax, edx
	cmp	eax, 1
	sete	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_3
	jmp	@lcontinue_2
@endif_3:
	lea	eax, v_i
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@lcontinue_2
@lend_1:
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
