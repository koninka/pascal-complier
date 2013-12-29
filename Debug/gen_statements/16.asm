.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 400 dup(0)
	v_i db 4 dup(0)
	v_j db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str5 db " ", 0
	fmt_str_new_line db 10, 0
.code
@p_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 4
	push	1
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_2:
	mov	ebx, ebp
	push	[ebx - 4]
	push	10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_3
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str5
	call	crt_printf
	add	esp, 4
@lcontinue_4:
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_2
@lend_3:
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@p_0 endp
main:
	mov	ebp, esp
	push	1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_7:
	push	dword ptr [v_i]
	push	10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_8
	push	1
	push	offset v_j
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_10:
	push	dword ptr [v_j]
	push	10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_11
	push	dword ptr [v_i]
	push	2
	push	dword ptr [v_j]
	pop	ebx
	pop	eax
	imul	ebx
	push	eax
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset v_a
	push	dword ptr [v_i]
	mov	ebx, 40
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr [v_j]
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
@lcontinue_12:
	push	offset v_j
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_10
@lend_11:
@lcontinue_9:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_7
@lend_8:
	push	1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_13:
	push	dword ptr [v_i]
	push	10
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_14
	push	offset v_a
	push	dword ptr [v_i]
	mov	ebx, 40
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ecx, 40
	add	eax, ecx
	mov	ebx, 0
@L_16:
	cmp	ebx, ecx
	jge	@L_17
	sub	eax, 4
	mov	edx, [eax]
	push	edx
	add	ebx, 4
	jmp	@L_16
@L_17:
	push	40
	push	ebp
	call	@p_0
	add	esp, 44
@lcontinue_15:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_13
@lend_14:
@exit_6:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
