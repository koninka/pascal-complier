.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_i db 4 dup(0)
	v_j db 4 dup(0)
	v_a db 80 dup(0)
	fmt_int db "%d", 0
	fmt_str8 db " ", 0
	fmt_str_new_line db 10, 0
.code
@init_0 proc
	push	ebp
	mov	ebp, esp
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 1
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
	push	dword ptr 2
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 11
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
	push	dword ptr 3
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 6
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
	push	dword ptr 4
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 16
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
	push	dword ptr 5
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 2
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
	push	dword ptr 6
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 12
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
	push	dword ptr 7
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 7
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
	push	dword ptr 8
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 17
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
	push	dword ptr 9
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 3
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
	push	dword ptr 10
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 13
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
	push	dword ptr 11
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 8
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
	push	dword ptr 12
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 18
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
	push	dword ptr 13
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 4
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
	push	dword ptr 14
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 14
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
	push	dword ptr 15
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 9
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
	push	dword ptr 16
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 19
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
	push	dword ptr 17
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 5
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
	push	dword ptr 18
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 15
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
	push	dword ptr 19
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 10
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
	push	dword ptr 20
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 20
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
@exit_3:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@init_0 endp
@writearr_1 proc
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
@forloop_5:
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 20
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_6
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
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
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str8
	call	crt_printf
	add	esp, dword ptr 4
@lcontinue_7:
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_5
@lend_6:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
@exit_4:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@writearr_1 endp
@swap_2 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 4
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_9:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@swap_2 endp
main:
	mov	ebp, esp
	push	offset v_a
	push	ebp
	call	@init_0
	add	esp, dword ptr 4
	push	offset v_a
	pop	eax
	mov	ecx, dword ptr 80
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_11:
	cmp	ebx, ecx
	jge	@L_12
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_11
@L_12:
	push	dword ptr 80
	push	ebp
	call	@writearr_1
	add	esp, dword ptr 84
	push	dword ptr 2
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_13:
	push	dword ptr [v_i]
	push	dword ptr 20
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_14
	push	dword ptr [v_i]
	push	offset v_j
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_16:
	push	dword ptr [v_j]
	push	dword ptr 2
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jl	@lend_17
	push	offset v_a
	push	dword ptr [v_j]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	[eax]
	push	offset v_a
	push	dword ptr [v_j]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	[eax]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@endif_19
	push	offset v_a
	push	dword ptr [v_j]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	offset v_a
	push	dword ptr [v_j]
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	ebp
	call	@swap_2
	add	esp, dword ptr 8
@endif_19:
@lcontinue_18:
	push	offset v_j
	pop	eax
	sub	[eax], dword ptr 1
	jmp	@forloop_16
@lend_17:
@lcontinue_15:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_13
@lend_14:
	push	offset v_a
	pop	eax
	mov	ecx, dword ptr 80
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
	push	dword ptr 80
	push	ebp
	call	@writearr_1
	add	esp, dword ptr 84
@exit_10:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
