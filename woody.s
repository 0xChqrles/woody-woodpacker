section .data
woody_data:
	.msg db "....WOODY....", 10

section .text
	global main
	global _woody

_start:
	call main
	ret

main:
	jmp _woody

_woody:
	mov rdi, 1
	lea rsi, [rel woody_data.msg]
	mov rdx, 10
	mov rax, 1
	syscall
	ret
