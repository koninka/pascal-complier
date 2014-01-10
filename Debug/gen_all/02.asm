.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_m1 db 400 dup(0)
	v_m2 db 400 dup(0)
	fmt_int db "%d", 0
	fmt_str29 db " ", 0
	fmt_str_new_line db 10, 0
	fmt_str46 db "initial:", 0
	fmt_str53 db "m2 := m1:", 0
	fmt_str56 db "copy(m1):", 0
	fmt_str59 db "transpose(m1):", 0
	fmt_str62 db "Print1:", 0
	fmt_str65 db "Print2:", 0
.code
@init_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 12
	mov	eax, ebp
	mov	[eax - 12], dword ptr 1
	mov	ebx, ebp
	mov	[ebx - 4], dword ptr 1
@forloop_7:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	cmp	eax, 10
	jg	@lend_8
	mov	ebx, ebp
	mov	[ebx - 8], dword ptr 1
@forloop_10:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 8]
	cmp	eax, 10
	jg	@lend_11
	mov	ebx, ebp
	push	[ebx - 12]
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 40
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	ebx, ebp
	push	eax
	mov	eax, dword ptr [ebx - 8]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	pop	[eax]
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 12]
	inc	eax
	mov	ebx, ebp
	add	ebx, -12
	push	eax
	mov	eax, ebx
	pop	[eax]
@lcontinue_12:
	mov	eax, ebp
	add	eax, -8
	inc	dword ptr [eax]
	jmp	@forloop_10
@lend_11:
@lcontinue_9:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_7
@lend_8:
@exit_6:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@init_0 endp
@transpose_1 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 12
	mov	ebx, ebp
	mov	[ebx - 4], dword ptr 1
@forloop_14:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	cmp	eax, 10
	jg	@lend_15
	mov	ebx, ebp
	mov	[ebx - 8], dword ptr 1
@forloop_17:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 8]
	cmp	eax, 10
	jg	@lend_18
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	push	ebx
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 8]
	mov	ebx, 40
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	ebx, ebp
	push	eax
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	add	eax, 40
	xor	ebx, ebx
@L_20:
	cmp	ebx, 40
	jge	@L_21
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_20
@L_21:
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	add	ebx, eax
	push	ebx
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 40
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	ebx, ebp
	push	eax
	mov	eax, dword ptr [ebx - 8]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	pop	[eax]
@lcontinue_19:
	mov	eax, ebp
	add	eax, -8
	inc	dword ptr [eax]
	jmp	@forloop_17
@lend_18:
@lcontinue_16:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_14
@lend_15:
@exit_13:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@transpose_1 endp
@print_2 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	ebx, ebp
	mov	[ebx - 4], dword ptr 1
@forloop_23:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	cmp	eax, 10
	jg	@lend_24
	mov	ebx, ebp
	mov	[ebx - 8], dword ptr 1
@forloop_26:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 8]
	cmp	eax, 10
	jg	@lend_27
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	push	ebx
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 40
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	ebx, ebp
	push	eax
	mov	eax, dword ptr [ebx - 8]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str29
	call	crt_printf
	add	esp, 12
@lcontinue_28:
	mov	eax, ebp
	add	eax, -8
	inc	dword ptr [eax]
	jmp	@forloop_26
@lend_27:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
@lcontinue_25:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_23
@lend_24:
@exit_22:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print_2 endp
@print1_3 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	mov	eax, ebx
	add	eax, 400
	xor	ebx, ebx
@L_31:
	cmp	ebx, 400
	jge	@L_32
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_31
@L_32:
	push	400
	push	ebp
	call	@print_2
@exit_30:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print1_3 endp
@print2_4 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	mov	eax, ebx
	add	eax, 400
	xor	ebx, ebx
@L_34:
	cmp	ebx, 400
	jge	@L_35
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_34
@L_35:
	push	400
	push	ebp
	call	@print1_3
@exit_33:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print2_4 endp
@copy_5 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	ebx, ebp
	mov	[ebx - 4], dword ptr 1
@forloop_37:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	cmp	eax, 10
	jg	@lend_38
	mov	ebx, ebp
	mov	[ebx - 8], dword ptr 1
@forloop_40:
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 8]
	cmp	eax, 10
	jg	@lend_41
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	push	ebx
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 40
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	ebx, ebp
	push	eax
	mov	eax, dword ptr [ebx - 8]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	add	eax, 40
	xor	ebx, ebx
@L_43:
	cmp	ebx, 40
	jge	@L_44
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_43
@L_44:
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	add	ebx, eax
	push	ebx
	mov	ebx, ebp
	mov	eax, dword ptr [ebx - 4]
	mov	ebx, 40
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	mov	ebx, ebp
	push	eax
	mov	eax, dword ptr [ebx - 8]
	mov	ebx, 4
	dec	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	pop	[eax]
@lcontinue_42:
	mov	eax, ebp
	add	eax, -8
	inc	dword ptr [eax]
	jmp	@forloop_40
@lend_41:
@lcontinue_39:
	mov	eax, ebp
	add	eax, -4
	inc	dword ptr [eax]
	jmp	@forloop_37
@lend_38:
@exit_36:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@copy_5 endp
main:
	mov	ebp, esp
	push	offset v_m1
	push	ebp
	call	@init_0
	add	esp, 4
	push	offset fmt_str46
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	mov	eax, offset v_m1 + 400
	xor	ebx, ebx
@L_47:
	cmp	ebx, 400
	jge	@L_48
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_47
@L_48:
	push	400
	push	ebp
	call	@print_2
	add	esp, 404
	mov	eax, offset v_m1 + 400
	xor	ebx, ebx
@L_49:
	cmp	ebx, 400
	jge	@L_50
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_49
@L_50:
	mov	eax, offset v_m2 - 4
	xor	ebx, ebx
@assignBegin_51:
	cmp	ebx, 400
	jge	@assignEnd_52
	push	eax
	add	[esp], dword ptr 4
	pop	eax
	pop	[eax]
	add	ebx, 4
	jmp	@assignBegin_51
@assignEnd_52:
	push	offset fmt_str53
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	mov	eax, offset v_m2 + 400
	xor	ebx, ebx
@L_54:
	cmp	ebx, 400
	jge	@L_55
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_54
@L_55:
	push	400
	push	ebp
	call	@print_2
	add	esp, 404
	push	offset fmt_str56
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	sub	esp, 400
	mov	eax, offset v_m1 + 400
	xor	ebx, ebx
@L_57:
	cmp	ebx, 400
	jge	@L_58
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_57
@L_58:
	push	400
	push	ebp
	call	@copy_5
	add	esp, 404
	push	400
	push	ebp
	call	@print_2
	add	esp, 404
	push	offset fmt_str59
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	sub	esp, 400
	mov	eax, offset v_m1 + 400
	xor	ebx, ebx
@L_60:
	cmp	ebx, 400
	jge	@L_61
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_60
@L_61:
	push	400
	push	ebp
	call	@transpose_1
	add	esp, 404
	push	400
	push	ebp
	call	@print_2
	add	esp, 404
	push	offset fmt_str62
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	mov	eax, offset v_m1 + 400
	xor	ebx, ebx
@L_63:
	cmp	ebx, 400
	jge	@L_64
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_63
@L_64:
	push	400
	push	ebp
	call	@print1_3
	add	esp, 404
	push	offset fmt_str65
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 8
	mov	eax, offset v_m1 + 400
	xor	ebx, ebx
@L_66:
	cmp	ebx, 400
	jge	@L_67
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_66
@L_67:
	push	400
	push	ebp
	call	@print2_4
@exit_45:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
