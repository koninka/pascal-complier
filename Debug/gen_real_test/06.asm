.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fv0 real4 5.000000
	fv1 real4 4.000000
	fv2 real4 3.000000
	fv3 real4 4.000000
	fv4 real4 4.000000
	fv5 real4 4.000000
	fv6 real4 3.000000
	fv7 real4 4.000000
	fv8 real4 5.000000
	fv9 real4 4.000000
	fv10 real4 4.000000
	fv11 real4 4.000000
	fv12 real4 4.000000
	fv13 real4 4.000000
	fv14 real4 4.000000
	fv15 real4 5.000000
	fv16 real4 5.000000
	fv17 real4 4.000000
	fv18 real4 4.000000
	fv19 real4 4.000000
	fv20 real4 6.000000
	fv21 real4 5.000000
	fv22 real4 3.000000
	fv23 real4 4.000000
	fv24 real4 4.000000
	fv25 real4 4.000000
	fv26 real4 4.000000
	fv27 real4 5.000000
	fv28 real4 4.000000
	fv29 real4 5.000000
	fv30 real4 4.000000
	fv31 real4 4.000000
	fmt_str35 db "good", 0
	fmt_str_new_line db 10, 0
	fmt_str36 db "bad", 0
	fmt_str39 db "bad", 0
	fmt_str40 db "good", 0
	fmt_str43 db "bad", 0
	fmt_str44 db "good", 0
	fmt_str47 db "good", 0
	fmt_str48 db "bad", 0
	fmt_str51 db "bad", 0
	fmt_str52 db "good", 0
	fmt_str55 db "bad", 0
	fmt_str56 db "good", 0
	fmt_str59 db "good", 0
	fmt_str60 db "bad", 0
	fmt_str63 db "good", 0
	fmt_str64 db "bad", 0
	fmt_str67 db "bad", 0
	fmt_str68 db "good", 0
	fmt_str71 db "good", 0
	fmt_str72 db "bad", 0
	fmt_str75 db "good", 0
	fmt_str76 db "bad", 0
	fmt_str79 db "bad", 0
	fmt_str80 db "good", 0
	fmt_str83 db "good", 0
	fmt_str84 db "bad", 0
	fmt_str87 db "bad", 0
	fmt_str88 db "good", 0
	fmt_str91 db "good", 0
	fmt_str92 db "bad", 0
	fmt_str95 db "bad", 0
	fmt_str96 db "good", 0
.code
main:
	mov	ebp, esp
	push	fv0
	push	fv1
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setb	al
	movzx	eax, al
	mov	[esp], eax
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
	push	fv2
	push	fv3
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setb	al
	movzx	eax, al
	mov	[esp], eax
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
	push	fv4
	push	fv5
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setb	al
	movzx	eax, al
	mov	[esp], eax
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
	push	fv6
	push	fv7
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	seta	al
	movzx	eax, al
	mov	[esp], eax
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
	push	fv8
	push	fv9
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	seta	al
	movzx	eax, al
	mov	[esp], eax
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
	push	fv10
	push	fv11
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	seta	al
	movzx	eax, al
	mov	[esp], eax
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
	push	fv12
	push	fv13
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setae	al
	movzx	eax, al
	mov	[esp], eax
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
	push	fv14
	push	fv15
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setae	al
	movzx	eax, al
	mov	[esp], eax
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
	push	fv16
	push	fv17
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setae	al
	movzx	eax, al
	mov	[esp], eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_66
	push	offset fmt_str67
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_65
@else_66:
	push	offset fmt_str68
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_65
@endif_65:
	push	fv18
	push	fv19
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setbe	al
	movzx	eax, al
	mov	[esp], eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_70
	push	offset fmt_str71
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_69
@else_70:
	push	offset fmt_str72
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_69
@endif_69:
	push	fv20
	push	fv21
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setbe	al
	movzx	eax, al
	mov	[esp], eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_74
	push	offset fmt_str75
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_73
@else_74:
	push	offset fmt_str76
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_73
@endif_73:
	push	fv22
	push	fv23
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setbe	al
	movzx	eax, al
	mov	[esp], eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_78
	push	offset fmt_str79
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_77
@else_78:
	push	offset fmt_str80
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_77
@endif_77:
	push	fv24
	push	fv25
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	sete	al
	movzx	eax, al
	mov	[esp], eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_82
	push	offset fmt_str83
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_81
@else_82:
	push	offset fmt_str84
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_81
@endif_81:
	push	fv26
	push	fv27
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	sete	al
	movzx	eax, al
	mov	[esp], eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_86
	push	offset fmt_str87
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_85
@else_86:
	push	offset fmt_str88
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_85
@endif_85:
	push	fv28
	push	fv29
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setne	al
	movzx	eax, al
	mov	[esp], eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_90
	push	offset fmt_str91
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_89
@else_90:
	push	offset fmt_str92
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_89
@endif_89:
	push	fv30
	push	fv31
	fld	dword ptr [esp + 4]
	fld	dword ptr [esp]
	add	esp, 4
	fcompp
	fnstsw	ax
	sahf
	setne	al
	movzx	eax, al
	mov	[esp], eax
	pop	eax
	mov	ebx, 0
	cmp	eax, ebx
	je	@else_94
	push	offset fmt_str95
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_93
@else_94:
	push	offset fmt_str96
	call	crt_printf
	add	esp, 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	jmp	@endif_93
@endif_93:
@exit_32:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
