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
	push	500
	push	ebp
	call	@bar_1
@exit_2:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
@bar_1 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	mov	eax, [ebx + 8]
	pop	ebx
	add	eax, 12
	mov	[eax], ebx
@exit_3:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@bar_1 endp
main:
	mov	ebp, esp
	sub	esp, 4
	push	ebp
	call	@foo_0
	push	offset fmt_int
	call	crt_printf
@exit_4:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
