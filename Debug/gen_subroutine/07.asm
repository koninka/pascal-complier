.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fmt_int db "%d", 0
.code
@f_0 proc
	push	ebp
	mov	ebp, esp
	mov	eax, ebp
	mov	[eax + 12], dword ptr 5
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@f_0 endp
main:
	mov	ebp, esp
	sub	esp, 4
	push	ebp
	call	@f_0
	push	offset fmt_int
	call	crt_printf
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
