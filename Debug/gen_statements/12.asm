.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_i db 4 dup(0)
	fmt_int db "%d", 0
.code
main:
	mov	ebp, esp
	push	dword ptr 0
	push	offset v_i
	pop	ebx
	pop	eax
	mov	[ebx], eax
@forloop_1:
	push	dword ptr [v_i]
	push	dword ptr 0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	jg	@lend_2
	push	offset v_i
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
@lcontinue_3:
	push	offset v_i
	pop	eax
	add	[eax], dword ptr 1
	jmp	@forloop_1
@lend_2:
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
