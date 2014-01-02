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
	add	esp, 0
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
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
	add	esp, 0
	push	ebp
	call	@last_2
	add	esp, 0
@exit_6:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@bar_1 endp
@last_2 proc
	push	ebp
	mov	ebp, esp
	push	150
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	push	[ebx - 4]
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	ebx, [ebx + 8]
	add	ebx, -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
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
	add	esp, 0
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	push	[ebx - 4]
	push	137
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	add	ebx, -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_8:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@last1_3 endp
@last2_4 proc
	push	ebp
	mov	ebp, esp
	push	59
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	ebx, [ebx + 8]
	add	ebx, -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_9:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@last2_4 endp
main:
	mov	ebp, esp
	push	ebp
	call	@foo_0
	add	esp, 0
@exit_10:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
