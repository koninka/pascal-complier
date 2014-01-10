.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	mov	eax, 3
	cmp	eax, 3
	setg	al
	movzx	eax, al
	push	eax
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, 3
	cmp	eax, 3
	setge	al
	movzx	eax, al
	push	eax
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, 3
	cmp	eax, 3
	setl	al
	movzx	eax, al
	push	eax
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, 3
	cmp	eax, 3
	setle	al
	movzx	eax, al
	push	eax
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, 3
	cmp	eax, 3
	sete	al
	movzx	eax, al
	push	eax
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, 3
	cmp	eax, 3
	setne	al
	movzx	eax, al
	push	eax
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
