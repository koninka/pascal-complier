.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_arr db 20 dup(0)
	fmt_int db "%d", 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	push	dword ptr 3
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	[eax]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	add	ebx, eax
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
	push	dword ptr 562
	pop	eax
	neg	eax
	push	eax
	push	offset v_arr
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
	sub	esp, dword ptr 4
	push	offset v_arr
	pop	eax
	mov	ecx, dword ptr 20
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_3:
	cmp	ebx, ecx
	jge	@L_4
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_3
@L_4:
	push	dword ptr 20
	push	ebp
	call	@foo_0
	add	esp, dword ptr 24
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
@exit_2:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
