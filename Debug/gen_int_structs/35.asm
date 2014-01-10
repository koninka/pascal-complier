.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 1600 dup(0)
	v_b db 1600 dup(0)
.code
main:
	mov	ebp, esp
	mov	eax, offset v_a + 12
	mov	[eax], dword ptr 23432
	mov	eax, offset v_b + 12
	mov	[eax], dword ptr 20
	mov	eax, offset v_b + 1600
	xor	ebx, ebx
@L_1:
	cmp	ebx, 1600
	jge	@L_2
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_1
@L_2:
	mov	eax, offset v_a - 4
	xor	ebx, ebx
@assignBegin_3:
	cmp	ebx, 1600
	jge	@assignEnd_4
	push	eax
	add	[esp], dword ptr 4
	pop	eax
	pop	[eax]
	add	ebx, 4
	jmp	@assignBegin_3
@assignEnd_4:
@exit_0:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
