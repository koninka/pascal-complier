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
	sub	esp, 4
	push	ebp
	call	@foo1_1
	add	esp, 0
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
@exit_3:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
@foo1_1 proc
	push	ebp
	mov	ebp, esp
	push	ebp
	call	@foo2_2
	add	esp, 0
@exit_4:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo1_1 endp
@foo2_2 proc
	push	ebp
	mov	ebp, esp
	push	123
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	ebx, [ebx + 8]
	add	ebx, -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_5:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo2_2 endp
main:
	mov	ebp, esp
	push	ebp
	call	@foo_0
	add	esp, 0
@exit_6:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
