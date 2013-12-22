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
	sub	esp, dword ptr 12
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -12
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_7:
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_8
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_10:
	mov	ebx, ebp
	push	[ebx - 8]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_11
	mov	ebx, ebp
	push	[ebx - 12]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 40
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	push	[ebx - 8]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	push	[ebx - 12]
	push	dword ptr 1
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr -12
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_12:
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_10
@lend_11:
@lcontinue_9:
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
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
	sub	esp, dword ptr 12
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_14:
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_15
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_17:
	mov	ebx, ebp
	push	[ebx - 8]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_18
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	mov	ebx, ebp
	push	[ebx - 8]
	mov	ebx, dword ptr 40
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ecx, dword ptr 40
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_20:
	cmp	ebx, ecx
	jge	@L_21
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_20
@L_21:
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	add	ebx, eax
	push	ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 40
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	push	[ebx - 8]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_19:
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_17
@lend_18:
@lcontinue_16:
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
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
	sub	esp, dword ptr 8
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_23:
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_24
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_26:
	mov	ebx, ebp
	push	[ebx - 8]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_27
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 40
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	push	[ebx - 8]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str29
	call	crt_printf
	add	esp, dword ptr 4
@lcontinue_28:
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_26
@lend_27:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
@lcontinue_25:
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
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
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	pop	eax
	mov	ecx, dword ptr 400
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_31:
	cmp	ebx, ecx
	jge	@L_32
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_31
@L_32:
	push	dword ptr 400
	push	ebp
	call	@print_2
	add	esp, dword ptr 404
@exit_30:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print1_3 endp
@print2_4 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	pop	eax
	mov	ecx, dword ptr 400
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_34:
	cmp	ebx, ecx
	jge	@L_35
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_34
@L_35:
	push	dword ptr 400
	push	ebp
	call	@print1_3
	add	esp, dword ptr 404
@exit_33:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print2_4 endp
@copy_5 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 8
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_37:
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_38
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_40:
	mov	ebx, ebp
	push	[ebx - 8]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_41
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 40
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	push	[ebx - 8]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ecx, dword ptr 40
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_43:
	cmp	ebx, ecx
	jge	@L_44
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_43
@L_44:
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	add	ebx, eax
	push	ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 40
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	push	[ebx - 8]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_42:
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_40
@lend_41:
@lcontinue_39:
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
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
	add	esp, dword ptr 4
	push	offset fmt_str46
	call	crt_printf
	add	esp, dword ptr 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_m1
	pop	eax
	mov	ecx, dword ptr 400
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_47:
	cmp	ebx, ecx
	jge	@L_48
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_47
@L_48:
	push	dword ptr 400
	push	ebp
	call	@print_2
	add	esp, dword ptr 404
	push	offset v_m1
	pop	eax
	mov	ecx, dword ptr 400
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_49:
	cmp	ebx, ecx
	jge	@L_50
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_49
@L_50:
	push	offset v_m2
	pop	eax
	sub	eax, dword ptr 4
	mov	ebx, dword ptr 0
	mov	ecx, dword ptr 400
@assignBegin_51:
	cmp	ebx, ecx
	jge	@assignEnd_52
	add	eax, dword ptr 4
	pop	edx
	mov	[eax], edx
	add	ebx, dword ptr 4
	jmp	@assignBegin_51
@assignEnd_52:
	push	offset fmt_str53
	call	crt_printf
	add	esp, dword ptr 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_m2
	pop	eax
	mov	ecx, dword ptr 400
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_54:
	cmp	ebx, ecx
	jge	@L_55
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_54
@L_55:
	push	dword ptr 400
	push	ebp
	call	@print_2
	add	esp, dword ptr 404
	push	offset fmt_str56
	call	crt_printf
	add	esp, dword ptr 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	sub	esp, dword ptr 400
	push	offset v_m1
	pop	eax
	mov	ecx, dword ptr 400
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_57:
	cmp	ebx, ecx
	jge	@L_58
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_57
@L_58:
	push	dword ptr 400
	push	ebp
	call	@copy_5
	add	esp, dword ptr 404
	push	dword ptr 400
	push	ebp
	call	@print_2
	add	esp, dword ptr 404
	push	offset fmt_str59
	call	crt_printf
	add	esp, dword ptr 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	sub	esp, dword ptr 400
	push	offset v_m1
	pop	eax
	mov	ecx, dword ptr 400
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_60:
	cmp	ebx, ecx
	jge	@L_61
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_60
@L_61:
	push	dword ptr 400
	push	ebp
	call	@transpose_1
	add	esp, dword ptr 404
	push	dword ptr 400
	push	ebp
	call	@print_2
	add	esp, dword ptr 404
	push	offset fmt_str62
	call	crt_printf
	add	esp, dword ptr 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_m1
	pop	eax
	mov	ecx, dword ptr 400
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_63:
	cmp	ebx, ecx
	jge	@L_64
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_63
@L_64:
	push	dword ptr 400
	push	ebp
	call	@print1_3
	add	esp, dword ptr 404
	push	offset fmt_str65
	call	crt_printf
	add	esp, dword ptr 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_m1
	pop	eax
	mov	ecx, dword ptr 400
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_66:
	cmp	ebx, ecx
	jge	@L_67
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_66
@L_67:
	push	dword ptr 400
	push	ebp
	call	@print2_4
	add	esp, dword ptr 404
@exit_45:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
