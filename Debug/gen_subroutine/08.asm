.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fmt_int db "%d", 0
.code
@sum_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	add	ebx, dword ptr 4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@sum_0 endp
main:
	mov	ebp, esp
	sub	esp, dword ptr 4
	push	dword ptr 1
	push	dword ptr 5
	push	ebp
	call	@sum_0
	add	esp, dword ptr 8
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
@exit_2:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
