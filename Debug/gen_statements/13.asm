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
	lea	ebx, v_i
	xor	eax, eax
	mov	[ebx], eax
@forloop_1:
	mov	eax, dword ptr [v_i]
	cmp	eax, dword ptr -5
	jg	@lend_2
	lea	eax, v_i
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
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
