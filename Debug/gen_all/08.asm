.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_m db 4 dup(0)
	v_n db 4 dup(0)
	v_x db 40 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
@generate_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 8
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr [v_n]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	sete	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@else_3
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_4:
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr [v_n]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_5
	push	offset v_x
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
@lcontinue_6:
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_4
@lend_5:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	jmp	@endif_2
@else_3:
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_7:
	mov	ebx, ebp
	push	[ebx - 8]
	push	dword ptr [v_m]
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_8
	mov	ebx, ebp
	push	[ebx - 8]
	push	offset v_x
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 1
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
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
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 1
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	ebp
	call	@generate_0
	add	esp, dword ptr 4
@lcontinue_9:
	mov	ebx, ebp
	add	ebx, dword ptr -8
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_7
@lend_8:
	jmp	@endif_2
@endif_2:
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@generate_0 endp
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
	push	dword ptr 0
	push	ebp
	call	@generate_0
	add	esp, dword ptr 4
@exit_10:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
