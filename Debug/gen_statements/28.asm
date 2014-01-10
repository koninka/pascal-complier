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
	call	@bar_1
	mov	eax, ebp
	add	eax, -4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_5:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
@bar_1 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	ebp
	call	@last1_3
	push	ebp
	call	@last_2
@exit_6:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@bar_1 endp
@last_2 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	eax, 150
	add	eax, dword ptr [ebx - 4]
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	ebx, [ebx + 8]
	add	ebx, -4
	push	eax
	mov	eax, ebx
	pop	[eax]
@exit_7:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@last_2 endp
@last1_3 proc
	push	ebp
	mov	ebp, esp
	push	ebp
	call	@last2_4
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	eax, dword ptr [ebx - 4]
	add	eax, 137
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	add	ebx, -4
	push	eax
	mov	eax, ebx
	pop	[eax]
@exit_8:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@last1_3 endp
@last2_4 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	eax, [ebx + 8]
	mov	[eax - 4], dword ptr 59
@exit_9:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@last2_4 endp
main:
	mov	ebp, esp
	push	ebp
	call	@foo_0
@exit_10:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
