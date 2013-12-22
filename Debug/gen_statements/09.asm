.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	fmt_str4 db "true", 0
	fmt_str5 db "false", 0
.code
main:
	mov	ebp, esp
	push	dword ptr 5
	push	dword ptr 0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@endif_1
	push	dword ptr 0
	push	dword ptr 0
	pop	ebx
	pop	eax
	cmp	eax, ebx
	setg	al
	movzx	eax, al
	push	eax
	pop	eax
	mov	ebx, dword ptr 0
	cmp	eax, ebx
	je	@else_3
	push	offset fmt_str4
	call	crt_printf
	add	esp, dword ptr 4
	jmp	@endif_2
@else_3:
	push	offset fmt_str5
	call	crt_printf
	add	esp, dword ptr 4
	jmp	@endif_2
@endif_2:
@endif_1:
@exit_0:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
