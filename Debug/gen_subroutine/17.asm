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
	push	[eax]
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, dword ptr 8
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
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
	push	offset v_arr
	push	ebp
	call	@foo_0
	add	esp, dword ptr 4
@exit_2:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
