.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_i db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str4 db " ", 0
.code
main:
	mov	ebp, esp
	push	1
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_1:
	push	dword ptr [v_i]
	push	4
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_2
	push	dword ptr [v_i]
	push	2
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str4
	call	crt_printf
	add	esp, 4
@lcontinue_3:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_1
@lend_2:
@exit_0:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
