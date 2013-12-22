.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_m db 4 dup(0)
	v_n db 4 dup(0)
	v_i db 4 dup(0)
	v_x db 40 dup(0)
	v_yes db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
@next_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 4
	push	dword ptr [v_n]
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_3:
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
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
	push	[eax]
	push	dword ptr [v_m]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	sete	al
	movzx	eax, al
	push	eax
	pop	ebx
	pop	eax
	and	eax, ebx
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@lend_2
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
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
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@lcontinue_3
@lend_2:
	mov	ebx, ebp
	push	[ebx - 4]
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
	je	@else_5
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
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
	push	[eax]
	push	dword ptr 1
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
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
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@endif_4
@else_5:
	push	dword ptr 0
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@endif_4
@endif_4:
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@next_0 endp
main:
	mov	ebp, esp
	push	dword ptr 2
	push	offset v_m
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 3
	push	offset v_n
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_7:
	push	dword ptr [v_i]
	push	dword ptr [v_n]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_8
	push	dword ptr 1
	push	offset v_x
	push	dword ptr [v_i]
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
@lcontinue_9:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_7
@lend_8:
@lcontinue_11:
	push	dword ptr 1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_12:
	push	dword ptr [v_i]
	push	dword ptr [v_n]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_13
	push	offset v_x
	push	dword ptr [v_i]
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
@lcontinue_14:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_12
@lend_13:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	offset v_yes
	push	offset v_x
	push	ebp
	call	@next_0
	add	esp, dword ptr 8
	push	dword ptr [v_yes]
	push	dword ptr 0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setle	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@lcontinue_11
	jmp	@lend_10
@lend_10:
@exit_6:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
