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
	push	dword ptr 23432
	push	offset v_a
	push	dword ptr 4
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 20
	push	offset v_b
	push	dword ptr 4
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_b
	pop	eax
	mov	ecx, dword ptr 1600
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_1:
	cmp	ebx, ecx
	jge	@L_2
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_1
@L_2:
	push	offset v_a
	pop	eax
	sub	eax, dword ptr 4
	mov	ebx, dword ptr 0
	mov	ecx, dword ptr 1600
@assignBegin_3:
	cmp	ebx, ecx
	jge	@assignEnd_4
	add	eax, dword ptr 4
	pop	edx
	mov	[eax], edx
	add	ebx, dword ptr 4
	jmp	@assignBegin_3
@assignEnd_4:
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
