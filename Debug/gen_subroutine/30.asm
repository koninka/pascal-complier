.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_arr db 20 dup(0)
	fmt_int db "%d", 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	eax, ebp
	mov	[eax + 12], dword ptr 1000
	mov	eax, offset v_arr + 20
	xor	ebx, ebx
	push	300
@L_6:
	cmp	ebx, 20
	jge	@L_7
	sub	eax, 4
	add	ebx, 4
	push	dword ptr [eax]
	jmp	@L_6
@L_7:
	push	20
	push	ebp
	call	@bar_1
	add	esp, 28
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
@exit_8:
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
@exit_9:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@last_2 endp
@last1_3 proc
	push	ebp
	mov	ebp, esp
	push	137
	sub	esp, 4
	push	ebp
	call	@ll_4
	pop	ebx
	pop	eax
	add	eax, ebx
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	add	ebx, 12
	push	eax
	mov	eax, [ebx]
	add	ebx, 4
	mov	eax, dword ptr 12
	add	eax, ebx
	mov	ebx, dword ptr [eax]
	pop	eax
	add	eax, ebx
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	add	ebx, -4
	push	eax
	mov	eax, ebx
	pop	[eax]
@exit_10:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@last1_3 endp
@ll_4 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	ebx, [ebx + 8]
	mov	ebx, [ebx + 8]
	add	ebx, 12
	push	[ebx]
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	ebx, [ebx + 8]
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	add	ebx, eax
	pop	eax
	add	eax, dword ptr [ebx]
	mov	ebx, ebp
	add	ebx, 12
	push	eax
	mov	eax, ebx
	pop	[eax]
@exit_11:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@ll_4 endp
main:
	mov	ebp, esp
	mov	eax, dword ptr -30
	mov	ebx, 4
	lea	ebx, v_arr
	mov	[ebx], eax
	mov	eax, offset v_arr + 4
	mov	[eax], dword ptr 290
	mov	eax, offset v_arr + 8
	mov	[eax], dword ptr 417
	mov	eax, dword ptr -562
	mov	ebx, 4
	push	eax
	mov	eax, dword ptr 3
	imul	eax, ebx
	pop	ebx
	add	eax, offset v_arr
	mov	[eax], ebx
	mov	eax, offset v_arr + 16
	mov	[eax], dword ptr 29
	push	1000
	push	ebp
	call	@foo_0
@exit_12:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
