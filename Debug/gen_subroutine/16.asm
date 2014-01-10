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
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 12
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 932
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
	mov	eax, dword ptr -562
	mov	ebx, 4
	push	eax
	mov	eax, dword ptr 3
	imul	eax, ebx
	pop	ebx
	add	eax, offset v_arr
	mov	[eax], ebx
	push	offset v_arr
	push	ebp
	call	@foo_0
	add	esp, 4
	mov	eax, offset v_arr + 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
