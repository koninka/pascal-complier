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
	sub	esp, 4
	mov	eax, offset v_arr + 8
	mov	ebx, ebp
	add	ebx, -4
	push	[eax]
	mov	eax, ebx
	pop	[eax]
	mov	eax, ebp
	add	eax, -4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
	mov	eax, dword ptr -562
	mov	ebx, 4
	push	eax
	mov	eax, dword ptr 3
	imul	eax, ebx
	pop	ebx
	add	eax, offset v_arr
	mov	[eax], ebx
	push	offset v_arr
	push	ebp
	call	@foo_0
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
