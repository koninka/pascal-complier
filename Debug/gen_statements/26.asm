.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fmt_int db "%d", 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	push	dword ptr 500
	push	ebp
	call	@bar_1
	add	esp, dword ptr 4
@exit_2:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
@bar_1 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	add	ebx, dword ptr 12
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_3:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@bar_1 endp
main:
	mov	ebp, esp
	sub	esp, dword ptr 4
	push	ebp
	call	@foo_0
	add	esp, dword ptr 0
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
@exit_4:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
