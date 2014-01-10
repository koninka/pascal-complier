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
@lcontinue_2:
	mov	eax, dword ptr [v_i]
	cmp	eax, 20
	setl	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@lend_1
	jmp	@lend_1
	lea	eax, v_i
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	jmp	@lcontinue_2
@lend_1:
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
