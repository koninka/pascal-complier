.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_arr db 20 dup(0)
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
@bar_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 8
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 38
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@bar_0 endp
main:
	mov	ebp, esp
	mov	eax, offset v_arr + 8
	mov	[eax], dword ptr 20
	push	offset v_arr
	push	ebp
	call	@bar_0
	add	esp, 4
	mov	eax, offset v_arr + 8
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
