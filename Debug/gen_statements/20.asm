.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fmt_str3 db "good", 0
	fmt_str_new_line db 10, 0
	fmt_str4 db "bad", 0
	fmt_str7 db "bad", 0
	fmt_str8 db "good", 0
	fmt_str11 db "bad", 0
	fmt_str12 db "good", 0
	fmt_str15 db "bad", 0
	fmt_str16 db "good", 0
	fmt_str19 db "bad", 0
	fmt_str20 db "good", 0
	fmt_str23 db "good", 0
	fmt_str24 db "bad", 0
	fmt_str27 db "good", 0
	fmt_str28 db "bad", 0
.code
main:
	mov	ebp, esp
	xor	ebx, ebx
	mov	eax, 1
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	push	eax
	mov	eax, 1
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	mov	ebx, eax
	pop	eax
	and	eax, ebx
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_2
	push	offset fmt_str3
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_1
@else_2:
	push	offset fmt_str4
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_1
@endif_1:
	xor	ebx, ebx
	mov	eax, 1
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	push	eax
	xor	eax, eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	mov	ebx, eax
	pop	eax
	and	eax, ebx
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_6
	push	offset fmt_str7
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_5
@else_6:
	push	offset fmt_str8
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_5
@endif_5:
	xor	ebx, ebx
	xor	eax, eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	push	eax
	mov	eax, 1
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	mov	ebx, eax
	pop	eax
	and	eax, ebx
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_10
	push	offset fmt_str11
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_9
@else_10:
	push	offset fmt_str12
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_9
@endif_9:
	xor	ebx, ebx
	xor	eax, eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	push	eax
	xor	eax, eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	mov	ebx, eax
	pop	eax
	and	eax, ebx
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_14
	push	offset fmt_str15
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_13
@else_14:
	push	offset fmt_str16
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_13
@endif_13:
	mov	eax, 1
	test	eax, eax
	sete	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_18
	push	offset fmt_str19
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_17
@else_18:
	push	offset fmt_str20
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_17
@endif_17:
	mov	eax, dword ptr -1
	xor	ebx, ebx
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_22
	push	offset fmt_str23
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_21
@else_22:
	push	offset fmt_str24
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_21
@endif_21:
	xor	ebx, ebx
	xor	eax, eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	test	eax, eax
	sete	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_26
	push	offset fmt_str27
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_25
@else_26:
	push	offset fmt_str28
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	jmp	@endif_25
@endif_25:
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
