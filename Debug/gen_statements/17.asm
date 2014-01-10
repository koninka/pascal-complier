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
	lea	ebx, v_i
	mov	[ebx], dword ptr 1
@forloop_1:
	mov	eax, dword ptr [v_i]
	cmp	eax, 20
	jg	@lend_2
	mov	eax, dword ptr [v_i]
	cmp	eax, 10
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_4
	jmp	@lend_2
@endif_4:
	lea	ebx, v_j
	mov	[ebx], dword ptr 1
@forloop_5:
	mov	eax, dword ptr [v_j]
	cmp	eax, 20
	jg	@lend_6
	lea	eax, v_j
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str8
	call	crt_printf
	add	esp, 12
	mov	eax, dword ptr [v_j]
	cmp	eax, dword ptr [v_i]
	sete	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_9
	jmp	@lend_6
@endif_9:
@lcontinue_7:
	lea	eax, v_j
	inc	dword ptr [eax]
	jmp	@forloop_5
@lend_6:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
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
