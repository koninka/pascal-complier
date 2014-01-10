.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 8 dup(0)
	fmt_int db "%d", 0
	fmt_str3 db " ", 0
	fmt_str_new_line db 10, 0
	fmt_str4 db " ", 0
.code
@swap_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	mov	ebx, ebp
	add	ebx, -4
	push	[eax]
	mov	eax, ebx
	pop	[eax]
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	add	eax, 4
	mov	ebx, ebp
	add	ebx, 12
	push	[eax]
	mov	eax, dword ptr [ebx]
	pop	[eax]
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	pop	ebx
	add	eax, 4
	mov	[eax], ebx
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@swap_0 endp
main:
	mov	ebp, esp
	lea	eax, v_a
	mov	[eax], dword ptr 10
	mov	[eax + 4], dword ptr 20
	lea	eax, v_a
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str3
	call	crt_printf
	add	esp, 12
	mov	eax, offset v_a + 4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 12
	push	offset v_a
	push	ebp
	call	@swap_0
	add	esp, 4
	lea	eax, v_a
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str4
	call	crt_printf
	add	esp, 12
	mov	eax, offset v_a + 4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
