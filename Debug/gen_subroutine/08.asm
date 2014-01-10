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
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 16
	add	eax, dword ptr [ebx]
	mov	ebx, ebp
	add	ebx, dword ptr 20
	push	eax
	mov	eax, ebx
	pop	[eax]
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@sum_0 endp
main:
	mov	ebp, esp
	sub	esp, 4
	push	1
	push	5
	push	ebp
	call	@sum_0
	add	esp, 8
	push	offset fmt_int
	call	crt_printf
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
