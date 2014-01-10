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
	lea	eax, v_a
	mov	[eax], dword ptr 10
@lcontinue_2:
	lea	eax, v_a
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str3
	call	crt_printf
	add	esp, 12
	lea	eax, v_b
	mov	[eax], dword ptr 10
@lcontinue_5:
	lea	eax, v_b
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str6
	call	crt_printf
	add	esp, 12
	mov	eax, dword ptr [v_b]
	dec	eax
	lea	ebx, v_b
	mov	[ebx], eax
	mov	eax, dword ptr [v_b]
	cmp	eax, 1
	setl	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_7
	jmp	@lend_4
@endif_7:
	xor	ebx, ebx
	xor	eax, eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@lcontinue_5
	jmp	@lend_4
@lend_4:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, dword ptr [v_a]
	dec	eax
	lea	ebx, v_a
	mov	[ebx], eax
	mov	eax, dword ptr [v_a]
	cmp	eax, 1
	setl	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_8
	jmp	@lend_1
@endif_8:
	xor	ebx, ebx
	xor	eax, eax
	cmp	eax, ebx
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
