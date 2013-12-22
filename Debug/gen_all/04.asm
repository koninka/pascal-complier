.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 80 dup(0)
	v_i db 4 dup(0)
	v_j db 4 dup(0)
	v_td db 8 dup(0)
	fmt_int db "%d", 0
	fmt_str9 db " => ", 0
	fmt_str_new_line db 10, 0
	fmt_str14 db "before sort:", 0
	fmt_str24 db "after sort:", 0
.code
@less_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	ebx
	pop	eax
	add	eax, dword ptr 0
	push	eax
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 8
	push	ebx
	pop	eax
	add	eax, dword ptr 0
	push	eax
	pop	eax
	mov	ebx, [eax]
	push	ebx
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@else_4
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 8
	add	ebx, dword ptr 8
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@endif_3
@else_4:
	push	dword ptr 0
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 8
	add	ebx, dword ptr 8
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@endif_3
@endif_3:
@exit_2:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@less_0 endp
@print_1 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 4
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_6:
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_7
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	add	eax, dword ptr 0
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str9
	call	crt_printf
	add	esp, dword ptr 4
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	add	eax, dword ptr 4
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
@lcontinue_8:
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_6
@lend_7:
@exit_5:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print_1 endp
main:
	mov	ebp, esp
	push	dword ptr 1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_11:
	push	dword ptr [v_i]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_12
	push	dword ptr [v_i]
	push	offset v_a
	push	dword ptr [v_i]
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	add	eax, dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 11
	push	dword ptr [v_i]
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	push	offset v_a
	push	dword ptr [v_i]
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	add	eax, dword ptr 0
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_13:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_11
@lend_12:
	push	offset fmt_str14
	call	crt_printf
	add	esp, dword ptr 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_a
	pop	eax
	mov	ecx, dword ptr 80
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_15:
	cmp	ebx, ecx
	jge	@L_16
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_15
@L_16:
	push	dword ptr 80
	push	ebp
	call	@print_1
	add	esp, dword ptr 84
	push	dword ptr 2
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_17:
	push	dword ptr [v_i]
	push	dword ptr 10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_18
	push	dword ptr [v_i]
	push	offset v_j
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_20:
	push	dword ptr [v_j]
	push	dword ptr 2
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jl	@lend_21
	sub	esp, dword ptr 4
	push	offset v_a
	push	dword ptr [v_j]
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	push	offset v_a
	push	dword ptr [v_j]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	push	ebp
	call	@less_0
	add	esp, dword ptr 16
	push	dword ptr 0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@endif_23
	push	offset v_a
	push	dword ptr [v_j]
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	push	offset v_td
	pop	eax
	pop	ebx
	mov	[eax], ebx
	pop	ebx
	mov	[eax + 4], ebx
	push	offset v_a
	push	dword ptr [v_j]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	push	offset v_a
	push	dword ptr [v_j]
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	pop	ebx
	mov	[eax + 4], ebx
	push	offset v_td
	pop	eax
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	push	offset v_a
	push	dword ptr [v_j]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, dword ptr 8
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	pop	ebx
	mov	[eax + 4], ebx
@endif_23:
@lcontinue_22:
	push	offset v_j
	pop	eax
	sub	[eax], dword ptr 1
	jmp	@forloop_20
@lend_21:
@lcontinue_19:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_17
@lend_18:
	push	offset fmt_str24
	call	crt_printf
	add	esp, dword ptr 4
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_a
	pop	eax
	mov	ecx, dword ptr 80
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_25:
	cmp	ebx, ecx
	jge	@L_26
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_25
@L_26:
	push	dword ptr 80
	push	ebp
	call	@print_1
	add	esp, dword ptr 84
@exit_10:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
