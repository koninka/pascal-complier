.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fv1 real4 32.540000
	v_a db 4 dup(0)
	fmt_float db "% 0.14E", 0
.code
@foo_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	push	fv1
	pop	[eax]
@exit_2:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@foo_0 endp
main:
	mov	ebp, esp
	push	offset v_a
	push	ebp
	call	@foo_0
	add	esp, 4
	lea	eax, v_a
	push	dword ptr [eax]
	fld	dword ptr [esp]
	sub	esp, 8
	fstp	qword ptr [esp]
	push	offset fmt_float
	call	crt_printf
@exit_3:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
