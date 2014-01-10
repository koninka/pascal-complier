.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 16 dup(0)
	fmt_int db "%d", 0
	fmt_str3 db " ", 0
	fmt_str4 db " ", 0
	fmt_str5 db " ", 0
.code
@fill_0 proc
	push	ebp
	mov	ebp, esp
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	mov	[eax], dword ptr 10
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 8
	add	eax, dword ptr [ebx]
	mov	[eax], dword ptr 20
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr [ebx]
	mov	[eax + 4], dword ptr 30
	mov	ebx, ebp
	add	ebx, 12
	mov	eax, dword ptr 8
	add	eax, dword ptr [ebx]
	mov	[eax + 4], dword ptr 40
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@fill_0 endp
main:
	mov	ebp, esp
	push	offset v_a
	push	ebp
	call	@fill_0
	add	esp, 4
	lea	eax, v_a
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str3
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_a + 8
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str4
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_a + 4
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str5
	call	crt_printf
	add	esp, 4
	mov	eax, offset v_a + 12
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
