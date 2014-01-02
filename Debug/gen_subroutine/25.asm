.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_d db 4 dup(0)
	v_rr db 12 dup(0)
	v_arr db 20 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	push	20
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	add	ebx, 4
	add	ebx, 4
	mov	eax, [ebx]
	add	ebx, 4
	add	ebx, eax
	add	ebx, 4
	push	[ebx]
	push	3
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
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
	push	562
	pop	eax
	neg	eax
	push	eax
	push	offset v_arr
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
	push	3
	push	5
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset v_arr
	push	offset v_d
	push	offset v_arr
	pop	eax
	mov	ecx, 20
	add	eax, ecx
	mov	ebx, 0
@L_3:
	cmp	ebx, ecx
	jge	@L_4
	sub	eax, 4
	mov	edx, [eax]
	push	edx
	add	ebx, 4
	jmp	@L_3
@L_4:
	push	20
	push	5
	push	offset v_rr
	push	4
	push	ebp
	call	@foo_0
	add	esp, 48
	push	offset v_arr
	push	4
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
@exit_2:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
