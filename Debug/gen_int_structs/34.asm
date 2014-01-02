.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 8000 dup(0)
	v_b db 8000 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
main:
	mov	ebp, esp
	push	23432
	push	offset v_a
	push	4
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
	push	20
	push	offset v_b
	push	4
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
	push	offset v_a
	push	4
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	offset v_b
	push	4
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	offset v_b
	pop	eax
	mov	ecx, 8000
	add	eax, ecx
	mov	ebx, 0
@L_1:
	cmp	ebx, ecx
	jge	@L_2
	sub	eax, 4
	mov	edx, [eax]
	push	edx
	add	ebx, 4
	jmp	@L_1
@L_2:
	push	offset v_a
	pop	eax
	sub	eax, 4
	mov	ebx, 0
	mov	ecx, 8000
@assignBegin_3:
	cmp	ebx, ecx
	jge	@assignEnd_4
	add	eax, 4
	pop	edx
	mov	[eax], edx
	add	ebx, 4
	jmp	@assignBegin_3
@assignEnd_4:
	push	offset v_a
	push	4
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	offset v_b
	push	4
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
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
@exit_0:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
