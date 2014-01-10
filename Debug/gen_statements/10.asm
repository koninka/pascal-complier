.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fmt_str4 db "true", 0
	fmt_str5 db "false", 0
.code
main:
	mov	ebp, esp
	mov	eax, 4
	cmp	eax, 5
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_1
	mov	ebx, 2
	mov	eax, 5
	xor	edx, edx
	idiv	ebx
	xor	ebx, ebx
	cmp	edx, ebx
	sete	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_3
	push	offset fmt_str4
	call	crt_printf
	add	esp, 4
	jmp	@endif_2
@else_3:
	push	offset fmt_str5
	call	crt_printf
	add	esp, 4
	jmp	@endif_2
@endif_2:
@endif_1:
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
