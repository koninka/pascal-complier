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
	push	offset v_arr
	pop	eax
	mov	ecx, 20
	add	eax, ecx
	mov	ebx, 0
@L_7:
	cmp	ebx, ecx
	jge	@L_8
	sub	eax, 4
	mov	edx, [eax]
	push	edx
	add	ebx, 4
	jmp	@L_7
@L_8:
	push	20
	push	ebp
	call	@bar_1
	add	esp, 24
	mov	ebx, ebp
	add	ebx, -4
	push	ebx
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
@exit_6:
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
@exit_9:
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
@exit_10:
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
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	push	ebx
	push	1
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ebx, [eax]
	push	ebx
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
@exit_11:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@last1_3 endp
@last2_4 proc
	push	ebp
	mov	ebp, esp
	push	59
	sub	esp, 4
	push	4
	push	ebp
	call	@ll_5
	add	esp, 4
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
@exit_12:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@last2_4 endp
@ll_5 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	ebx, [ebx + 8]
	mov	ebx, [ebx + 8]
	add	ebx, 12
	mov	eax, [ebx]
	add	ebx, 4
	push	ebx
	mov	ebx, ebp
	add	ebx, 12
	push	[ebx]
	mov	ebx, 4
	pop	eax
	sub	eax, 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, 12
	add	ebx, 4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_13:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@ll_5 endp
main:
	mov	ebp, esp
	push	30
	pop	eax
	neg	eax
	push	eax
	push	offset v_arr
	push	1
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	290
	push	offset v_arr
	push	2
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	417
	push	offset v_arr
	push	3
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	562
	pop	eax
	neg	eax
	push	eax
	push	offset v_arr
	push	4
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	29
	push	offset v_arr
	push	5
	mov	ebx, 4
	pop	eax
	sub	eax, 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	ebp
	call	@foo_0
	add	esp, 0
@exit_14:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
