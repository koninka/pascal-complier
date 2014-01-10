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
	lea	ebx, v_i
	mov	[ebx], dword ptr 1
@forloop_1:
	mov	eax, dword ptr [v_i]
	cmp	eax, 4
	jg	@lend_2
	mov	eax, dword ptr [v_i]
	add	eax, 2
	push	eax
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str4
	call	crt_printf
	add	esp, 12
@lcontinue_3:
	lea	eax, v_i
	inc	dword ptr [eax]
	jmp	@forloop_1
@lend_2:
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
