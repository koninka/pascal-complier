.686
.model flat, stdcall
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib
.data
	v_a db 4 dup(0)
	v_b db 4 dup(0)
	fmt_int db "%d", 0
	fmt_str3 db " ", 0
	fmt_str_new_line db 10, 0
	fmt_str4 db " ", 0
.code
@swap_0 proc
	push	ebp
	mov	ebp, esp
	sub	esp, dword ptr 4
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, dword ptr -4
	push	ebx
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	pop	eax
	mov	ebx, [eax]
	push	ebx
	mov	ebx, ebp
	add	ebx, dword ptr 12
	push	[ebx]
	pop	eax
	pop	ebx
	mov	[eax], ebx
	mov	ebx, ebp
	push	[ebx - 4]
	mov	ebx, ebp
	add	ebx, dword ptr 12
	add	ebx, dword ptr 4
	push	[ebx]
	pop	eax
	pop	ebx
	mov	[eax], ebx
@exit_1:
	mov	esp, ebp
	pop	ebp
	ret	byte ptr 4
@swap_0 endp
main:
	mov	ebp, esp
	push	5
	push	offset v_a
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	10
	push	offset v_b
	pop	eax
	pop	ebx
	mov	[eax], ebx
	push	offset v_a
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str3
	call	crt_printf
	add	esp, 4
	push	offset v_b
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
	push	offset v_b
	push	offset v_a
	push	ebp
	call	@swap_0
	add	esp, 8
	push	offset v_a
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str4
	call	crt_printf
	add	esp, 4
	push	offset v_b
	pop	eax
	push	dword ptr [eax]
	push	offset fmt_int
	call	crt_printf
	add	esp, 8
	push	offset fmt_str_new_line
	call	crt_printf
	add	esp, 4
@exit_2:
	mov	esp, ebp
	mov	eax, dword ptr 0
	ret
end main
