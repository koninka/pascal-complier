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
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	cmp	eax, 1
	setle	al
	movzx	eax, al
	xor	ebx, ebx
	cmp	eax, ebx
	je	@else_3
	mov	eax, ebp
	mov	[eax + 16], dword ptr 1
	jmp	@endif_2
@else_3:
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	sub	esp, 4
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	dec	eax
	push	eax
	push	ebp
	call	@fact_0
	add	esp, 4
	pop	ebx
	pop	eax
	imul	ebx
	mov	ebx, ebp
	add	ebx, dword ptr 16
	push	eax
	mov	eax, ebx
	pop	[eax]
	jmp	@endif_2
@endif_2:
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@fact_0 endp
main:
	mov	ebp, esp
	lea	ebx, v_i
	mov	[ebx], dword ptr 1
@forloop_5:
	mov	eax, dword ptr [v_i]
	cmp	eax, 7
	jg	@lend_6
	lea	eax, v_i
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str8
	call	crt_printf
	add	esp, 12
	sub	esp, 4
	push	dword ptr [v_i]
	push	ebp
	call	@fact_0
	add	esp, 4
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 12
@lcontinue_7:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_5
@lend_6:
@exit_4:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
