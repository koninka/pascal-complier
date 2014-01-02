.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
.code
@f_0 proc
	push	ebp
	mov	ebp, esp
	push	5
	mov	ebx, ebp
	add	ebx, 12
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	jmp	@exit_1
	push	20
	mov	ebx, ebp
	add	ebx, 12
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@f_0 endp
main:
	mov	ebp, esp
	sub	esp, 4
	push	ebp
	call	@f_0
	add	esp, 0
@exit_2:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
