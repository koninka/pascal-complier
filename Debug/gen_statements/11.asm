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
	fmt_str15 db "good", 0
	fmt_str16 db "bad", 0
	fmt_str19 db "bad", 0
	fmt_str20 db "good", 0
	fmt_str23 db "bad", 0
	fmt_str24 db "good", 0
	fmt_str27 db "good", 0
	fmt_str28 db "bad", 0
	fmt_str31 db "good", 0
	fmt_str32 db "bad", 0
	fmt_str35 db "bad", 0
	fmt_str36 db "good", 0
	fmt_str39 db "good", 0
	fmt_str40 db "bad", 0
	fmt_str43 db "good", 0
	fmt_str44 db "bad", 0
	fmt_str47 db "bad", 0
	fmt_str48 db "good", 0
	fmt_str51 db "good", 0
	fmt_str52 db "bad", 0
	fmt_str55 db "bad", 0
	fmt_str56 db "good", 0
	fmt_str59 db "good", 0
	fmt_str60 db "bad", 0
	fmt_str63 db "bad", 0
	fmt_str64 db "good", 0
.code
main:
	mov	ebp, esp
	push	5
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_2
	push	offset fmt_str3
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_1
@else_2:
	push	offset fmt_str4
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_1
@endif_1:
	push	3
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_6
	push	offset fmt_str7
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_5
@else_6:
	push	offset fmt_str8
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_5
@endif_5:
	push	4
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_10
	push	offset fmt_str11
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_9
@else_10:
	push	offset fmt_str12
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_9
@endif_9:
	push	3
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_14
	push	offset fmt_str15
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_13
@else_14:
	push	offset fmt_str16
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_13
@endif_13:
	push	5
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_18
	push	offset fmt_str19
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_17
@else_18:
	push	offset fmt_str20
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_17
@endif_17:
	push	4
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setl	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_22
	push	offset fmt_str23
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_21
@else_22:
	push	offset fmt_str24
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_21
@endif_21:
	push	4
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setle	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_26
	push	offset fmt_str27
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_25
@else_26:
	push	offset fmt_str28
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_25
@endif_25:
	push	4
	push	5
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setle	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_30
	push	offset fmt_str31
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_29
@else_30:
	push	offset fmt_str32
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_29
@endif_29:
	push	5
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setle	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_34
	push	offset fmt_str35
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_33
@else_34:
	push	offset fmt_str36
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_33
@endif_33:
	push	4
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setge	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_38
	push	offset fmt_str39
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_37
@else_38:
	push	offset fmt_str40
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_37
@endif_37:
	push	6
	push	5
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setge	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_42
	push	offset fmt_str43
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_41
@else_42:
	push	offset fmt_str44
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_41
@endif_41:
	push	3
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setge	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_46
	push	offset fmt_str47
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_45
@else_46:
	push	offset fmt_str48
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_45
@endif_45:
	push	4
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	sete	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_50
	push	offset fmt_str51
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_49
@else_50:
	push	offset fmt_str52
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_49
@endif_49:
	push	4
	push	5
	pop	ebx
	pop	eax
	cmp	eax, ebx
	sete	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_54
	push	offset fmt_str55
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_53
@else_54:
	push	offset fmt_str56
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_53
@endif_53:
	push	4
	push	5
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setne	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_58
	push	offset fmt_str59
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_57
@else_58:
	push	offset fmt_str60
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_57
@endif_57:
	push	4
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setne	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_62
	push	offset fmt_str63
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_61
@else_62:
	push	offset fmt_str64
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_61
@endif_61:
@exit_0:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
