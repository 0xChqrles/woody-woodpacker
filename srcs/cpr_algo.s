section .text
	global cpr_algo

cpr_algo:
	add rsi, rdi

algo_loop:
	xor byte [rdi], 0xff
	add byte [rdi], 0x2a
	inc rdi
	cmp rdi, rsi
	jne algo_loop
	ret
