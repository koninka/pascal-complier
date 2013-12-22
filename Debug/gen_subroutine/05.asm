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
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	ebx
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
	push	dword ptr 500
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	ebx
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, dword ptr 4
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@proc_0 endp
main:
	mov	ebp, esp
	push	dword ptr 10
	push	ebp
	call	@proc_0
	add	esp, dword ptr 4
@exit_2:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
