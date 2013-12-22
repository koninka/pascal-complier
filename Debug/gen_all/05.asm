.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 32 dup(0)
	v_b db 32 dup(0)
	v_i db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str5 db " ", 0
	fmt_str_new_line db 10, 0
.code
@print_0 proc
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
@forloop_2:
	mov	ebx, ebp
	push	[ebx - 4]
	push	dword ptr 4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_3
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	ebx
	pop	eax
	add	eax, dword ptr 0
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
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str5
	call	crt_printf
	add	esp, dword ptr 4
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	ebx
	pop	eax
	add	eax, dword ptr 16
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
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
@lcontinue_4:
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_2
@lend_3:
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@print_0 endp
main:
	mov	ebp, esp
	push	dword ptr 1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_7:
	push	dword ptr [v_i]
	push	dword ptr 4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_8
	push	dword ptr 1
	push	offset v_a
	pop	eax
	add	eax, dword ptr 0
	push	eax
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
	push	dword ptr 2
	push	offset v_a
	pop	eax
	add	eax, dword ptr 16
	push	eax
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
	push	offset v_a
	pop	eax
	mov	ecx, dword ptr 32
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_10:
	cmp	ebx, ecx
	jge	@L_11
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_10
@L_11:
	push	ebp
	call	@print_0
	add	esp, dword ptr 32
	push	offset v_a
	pop	eax
	mov	ecx, dword ptr 32
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_12:
	cmp	ebx, ecx
	jge	@L_13
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_12
@L_13:
	push	offset v_b
	pop	eax
	sub	eax, dword ptr 4
	mov	ebx, dword ptr 0
	mov	ecx, dword ptr 32
@assignBegin_14:
	cmp	ebx, ecx
	jge	@assignEnd_15
	add	eax, dword ptr 4
	pop	edx
	mov	[eax], edx
	add	ebx, dword ptr 4
	jmp	@assignBegin_14
@assignEnd_15:
	push	offset v_a
	pop	eax
	add	eax, dword ptr 16
	push	eax
	pop	eax
	mov	ebx, [eax + 12]
	push	ebx
	mov	ebx, [eax + 8]
	push	ebx
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	push	offset v_b
	pop	eax
	add	eax, dword ptr 0
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	pop	ebx
	mov	[eax + 4], ebx
	pop	ebx
	mov	[eax + 8], ebx
	pop	ebx
	mov	[eax + 12], ebx
	push	offset v_b
	pop	eax
	mov	ecx, dword ptr 32
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_16:
	cmp	ebx, ecx
	jge	@L_17
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_16
@L_17:
	push	ebp
	call	@print_0
	add	esp, dword ptr 32
@exit_6:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
