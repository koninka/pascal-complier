.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_arr db 20 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 4
	add	eax, dword ptr [ebx]
	mov	ebx, ebp
	add	ebx, 12
	push	[eax]
	mov	eax, dword ptr 8
	add	eax, dword ptr [ebx]
	pop	[eax]
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
	mov	eax, offset v_arr + 4
	mov	[eax], dword ptr 290
	mov	eax, offset v_arr + 8
	mov	[eax], dword ptr 417
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 12
	push	offset v_arr
	push	ebp
	call	@foo_0
	add	esp, 4
	mov	eax, offset v_arr + 8
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
