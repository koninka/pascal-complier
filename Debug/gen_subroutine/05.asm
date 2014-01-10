.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fmt_int db "%d", 0
	fmt_str_new_line db 10, 0
.code
@proc_0 proc
	push	ebp
	mov	ebp, esp
	mov	eax, ebp
	add	eax, 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	mov	eax, ebp
	mov	[eax + 12], dword ptr 500
	add	eax, 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@proc_0 endp
main:
	mov	ebp, esp
	push	10
	push	ebp
	call	@proc_0
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
