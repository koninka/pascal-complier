.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_c db 4 dup(0)
	v_d db 4 dup(0)
	v_rr db 8 dup(0)
	v_arr db 20 dup(0)
	fmt_int db "%d", 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	add	ebx, 8
	add	ebx, 4
	mov	eax, [ebx]
	add	ebx, 4
	add	ebx, eax
	push	[ebx]
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
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
	pop	eax
	mov	ebx, [eax + 4]
	push	ebx
	mov	ebx, [eax]
	push	ebx
	push	4
	push	ebp
	call	@foo_0
	add	esp, 52
@exit_2:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
