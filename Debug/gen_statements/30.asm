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
	sub	esp, dword ptr 4
	push	dword ptr 1000
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 300
	push	offset v_arr
	pop	eax
	mov	ecx, dword ptr 20
	add	eax, ecx
	mov	ebx, dword ptr 0
@L_6:
	cmp	ebx, ecx
	jge	@L_7
	sub	eax, dword ptr 4
	mov	edx, [eax]
	push	edx
	add	ebx, dword ptr 4
	jmp	@L_6
@L_7:
	push	dword ptr 20
	push	ebp
	call	@bar_1
	add	esp, dword ptr 28
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
@exit_5:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
@bar_1 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 4
	push	ebp
	call	@last1_3
	add	esp, dword ptr 0
	push	ebp
	call	@last_2
	add	esp, dword ptr 0
@exit_8:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@bar_1 endp
@last_2 proc
	push	ebp
	mov	ebp, esp
	push	dword ptr 150
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
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_9:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@last_2 endp
@last1_3 proc
	push	ebp
	mov	ebp, esp
	push	dword ptr 137
	sub	esp, dword ptr 4
	push	ebp
	call	@ll_4
	add	esp, dword ptr 0
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	push	ebx
	push	dword ptr 3
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 0
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	[eax]
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
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
	add	ebx, dword ptr 12
	push	[ebx]
	mov	ebx, ebp
	mov	ebx, [ebx + 8]
	mov	ebx, [ebx + 8]
	add	ebx, dword ptr 12
	mov	eax, [ebx]
	add	ebx, dword ptr 4
	add	ebx, eax
	push	[ebx]
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_11:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@ll_4 endp
main:
	mov	ebp, esp
	push	dword ptr 30
	pop	eax
	neg	eax
	push	eax
	push	offset v_arr
	push	dword ptr 1
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 290
	push	offset v_arr
	push	dword ptr 2
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 417
	push	offset v_arr
	push	dword ptr 3
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 562
	pop	eax
	neg	eax
	push	eax
	push	offset v_arr
	push	dword ptr 4
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 29
	push	offset v_arr
	push	dword ptr 5
	mov	ebx, dword ptr 4
	pop	eax
	sub	eax, dword ptr 1
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	dword ptr 1000
	push	ebp
	call	@foo_0
	add	esp, dword ptr 4
@exit_12:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
