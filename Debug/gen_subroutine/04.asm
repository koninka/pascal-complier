.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
.code
@proc_0 proc
	push	ebp
	mov	ebp, esp
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@proc_0 endp
main:
	mov	ebp, esp
	push	ebp
	call	@proc_0
	add	esp, 0
@exit_2:
	mov	esp, ebp
	mov	eax, 0
	ret
end main
