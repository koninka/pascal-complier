.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_i db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str8 db "! = ", 0
	fmt_str_new_line db 10, 0
.code
@fact_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 1
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setle	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@else_3
	push	dword ptr 1
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@endif_2
@else_3:
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	sub	esp, dword ptr 4
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	push	dword ptr 1
	pop	ebx
	pop	eax
	sub	eax, ebx
	push	eax
	push	ebp
	call	@fact_0
	add	esp, dword ptr 4
	pop	ebx
	pop	eax
	imul	ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@endif_2
@endif_2:
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@fact_0 endp
main:
	mov	ebp, esp
	push	dword ptr 1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_5:
	push	dword ptr [v_i]
	push	dword ptr 7
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_6
	push	offset v_i
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str8
	call	crt_printf
	add	esp, dword ptr 4
	sub	esp, dword ptr 4
	push	dword ptr [v_i]
	push	ebp
	call	@fact_0
	add	esp, dword ptr 4
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
@lcontinue_7:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_5
@lend_6:
@exit_4:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
