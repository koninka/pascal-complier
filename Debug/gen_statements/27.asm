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
	mov	eax, ebp
	add	eax, -4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
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
@exit_4:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo1_1 endp
@foo2_2 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	eax, [ebx + 8]
	mov	[eax - 4], dword ptr 123
@exit_5:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo2_2 endp
main:
	mov	ebp, esp
	push	ebp
	call	@foo_0
@exit_6:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
