.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
.code
@proc_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	eax, ebp
	mov	[eax - 4], dword ptr 10
	mov	ebx, ebp
	mov	eax, ebp
	add	eax, -8
	mov	ebx, dword ptr [ebx - 4]
	mov	[eax], ebx
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@proc_0 endp
main:
	mov	ebp, esp
@exit_2:
	mov	esp, ebp
	xor	eax, eax
	ret
end main
