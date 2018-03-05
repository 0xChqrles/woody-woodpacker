global loader:function
global g_loader_sz:function

section .text
	g_loader_sz dd end - loader

loader:
	jmp loader_start

dcpr_algo:
	add rsi, rdi

algo_loop:
	sub byte [rdi], 0x2a
	xor byte [rdi], 0xff
	inc rdi
	cmp rdi, rsi
	jne algo_loop
	ret

loader_start:
	pushf
	push rax
	push rdi
	push rsi
	push rsp
	push rdx
	mov edi, 0x1
	lea rsi, [rel woody]
	mov rdx, 0xe
	mov rax, 0x1
	syscall
	jmp exec_text
	woody db "....WOODY....", 0xa

exec_text:
	mov rdi, qword [rel text_addr]
	mov rsi, qword [rel text_size]
	call dcpr_algo
	pop rdx
	pop rsp
	pop rsi
	pop rdi
	pop rax
	popf
	jmp 0xffffffff
	text_addr dq 0x0
	text_size dq 0x0

end:
