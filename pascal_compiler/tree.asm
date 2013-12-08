.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 16 dup(0)
	v_c db 16 dup(0)
	v_b db 8 dup(0)
	v_d db 4 dup(0)
	v_r db 8 dup(0)
	format_str_int db "%d", 0
.code
main:
	push	dword ptr 230
	push	offset v_r
	pop	eax
	lea	eax, [eax + 4]
	push	eax
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	dword ptr 30
	push	offset v_r
	pop	eax
	lea	eax, [eax + 4]
	push	eax
	pop	ebx
	mov	eax, [ebx]
	push	eax
	pop	ebx
	pop	eax
	add	eax, ebx
	push	eax
	push	offset v_c
	push	dword ptr 2
	mov	ebx, dword ptr 8
	pop	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 4
	pop	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	ebx
	pop	eax
	mov	[ebx], eax
	push	offset v_c
	push	dword ptr 2
	mov	ebx, dword ptr 8
	pop	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	push	dword ptr 1
	mov	ebx, dword ptr 4
	pop	eax
	imul	eax, ebx
	pop	ebx
	add	eax, ebx
	push	eax
	pop	eax
	push	dword ptr [eax]
	push	offset format_str_int
	call	crt_printf
	add	esp, dword ptr 8
	ret
end main
