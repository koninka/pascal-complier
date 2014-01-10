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
	mov	eax, offset v_a + 12
	mov	[eax], dword ptr 23432
	mov	eax, offset v_b + 12
	mov	[eax], dword ptr 20
	mov	eax, offset v_a + 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_b + 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_b + 8000
	xor	ebx, ebx
@L_1:
	cmp	ebx, 8000
	jge	@L_2
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_1
@L_2:
	mov	eax, offset v_a - 4
	xor	ebx, ebx
@assignBegin_3:
	cmp	ebx, 8000
	jge	@assignEnd_4
	push	eax
	add	[esp], dword ptr 4
	pop	eax
	pop	[eax]
	add	ebx, 4
	jmp	@assignBegin_3
@assignEnd_4:
	mov	eax, offset v_a + 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_b + 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
