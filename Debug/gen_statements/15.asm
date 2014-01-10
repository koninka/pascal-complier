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
	lea	eax, v_i
	xor	ebx, ebx
	mov	[eax], ebx
@lcontinue_2:
	lea	eax, v_i
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	mov	eax, dword ptr [v_i]
	inc	eax
	lea	ebx, v_i
	mov	[ebx], eax
	mov	eax, dword ptr [v_i]
	cmp	eax, 5
	sete	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_4
	jmp	@lcontinue_2
	jmp	@endif_3
@else_4:
	mov	eax, dword ptr [v_i]
	cmp	eax, 8
	sete	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_5
	jmp	@lend_1
@endif_5:
	jmp	@endif_3
@endif_3:
	mov	eax, dword ptr [v_i]
	cmp	eax, 100
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@lcontinue_2
	jmp	@lend_1
@lend_1:
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
