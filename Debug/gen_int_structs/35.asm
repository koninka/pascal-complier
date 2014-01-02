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
	push	offset v_b
	pop	eax
	mov	ecx, 1600
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
	mov	ecx, 1600
@assignBegin_3:
	cmp	ebx, ecx
	jge	@assignEnd_4
	add	eax, 4
	pop	edx
	mov	[eax], edx
	add	ebx, 4
	jmp	@assignBegin_3
@assignEnd_4:
@exit_0:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
