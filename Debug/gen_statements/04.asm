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
	mov	[eax], dword ptr 10
@lcontinue_2:
	xor	ebx, ebx
	cmp	dword ptr [v_i], ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@lend_1
	mov	eax, dword ptr [v_i]
	dec	eax
	lea	ebx, v_i
	mov	[ebx], eax
	lea	eax, v_i
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 12
	jmp	@lcontinue_2
@lend_1:
	lea	eax, v_i
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
