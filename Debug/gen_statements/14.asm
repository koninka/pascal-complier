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
	lea	ebx, v_i
	xor	eax, eax
	mov	[ebx], eax
@forloop_1:
	mov	eax, dword ptr [v_i]
	cmp	eax, 100
	jg	@lend_2
	mov	eax, dword ptr [v_i]
	cmp	eax, 6
	sete	al
	movzx	eax, al
	mov	ebx, 7
	cmp	dword ptr [v_i], ebx
	push	eax
	sete	al
	movzx	eax, al
	mov	ebx, eax
	pop	eax
	or	eax, ebx
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_4
	jmp	@lcontinue_3
@endif_4:
	mov	eax, dword ptr [v_i]
	cmp	eax, 10
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_5
	jmp	@lend_2
@endif_5:
	lea	eax, v_i
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
@lcontinue_3:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_1
@lend_2:
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
