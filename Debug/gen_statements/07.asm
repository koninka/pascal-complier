.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fmt_str2 db "true", 0
.code
main:
	mov	ebp, esp
	xor	ebx, ebx
	mov	eax, 5
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@endif_1
	push	offset fmt_str2
	call	crt_printf
	add	esp, 4
@endif_1:
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
