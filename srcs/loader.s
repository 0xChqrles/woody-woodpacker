global loader:function
global g_loader_sz:function

section .text
	g_loader_sz dd end - loader

loader:
	jmp loader_start

dcpr_rot_xor:
	push rdi
	push rsi
	add rsi, rdi

dcpr_rot_xor_loop:
	sub byte [rdi], 0x2a
	xor byte [rdi], 0xff
	inc rdi
	cmp rdi, rsi
	jne dcpr_rot_xor_loop
	pop rsi
	pop rdi
	ret

dcpr_xxtea:
	push rbp
	mov rbp, rsp
	sub rsp, 0x10
	push r8				; uint32_t    y;
	push r9				; uint32_t    z;
	push r10			; uint32_t    sum;
	push r11			; uint32_t    p;
	push r12			; uint32_t    rounds;
	push r13			; uint32_t    e;
	push r14			; uint32_t    i;
	push rdx

	xor rdx, rdx
	mov rax, rsi
	mov r8, 0x4
	div r8
	mov rsi, rax

	mov r14, rsi
	dec r14								; i = sz - 1;
	xor rdx, rdx
	mov rax, 0x34
	div rsi
	add rax, 0x6
	mov r12, rax						; rounds = 6 + 52 / sz;
	mov rax, r12
	mov r10, 0x9e3779b9
	mul r10
	mov r10, rax						; sum = rounds * DELTA;
	xor r8, r8
	mov r8d, dword [rdi]				; z = text[sz - 1];
	pop rdx

xxtea_rounds_loop:				; do {
	mov r13, r10
	shr r13, 0x2
	and r13, 0x3					; e = (sum >> 2) & 3;
	mov r11, r14

xxtea_loop:							; for (p = n - 1; p > 0; p--) {
	cmp r11, 0
	jbe xxtea_end_loop

	dec r11
	mov r9d, dword [rdi + r11 * 0x4]	; z = text[p - 1];
	inc r11
	call xxtea_mx
	sub dword [rdi + r11 * 0x4], eax	; text[p] -= MX;
	mov r8d, dword [rdi + r11 * 0x4]	; y = text[p];

	dec r11
	jmp xxtea_loop

xxtea_end_loop:							; }
	xor r9, r9
	mov r9d, dword [rdi + r14 * 0x4]	; z = text[n - 1];
	call xxtea_mx
	sub dword [rdi], eax				; text[0] -= MX;
	mov r8d, dword [rdi]				; y = text[0];
	sub r10d, 0x9e3779b9				; sum -= DELTA

	dec r12
	cmp r12, 0
	jne xxtea_rounds_loop 		; } while (--rounds)

	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	leave
	ret

xxtea_mx:
	push rbp
	mov rbp, rsp
	sub rsp, 0x10
	push r15
	push rcx
	mov r15, r8
	mov rcx, r9
	shl r15, 0x2
	shr rcx, 0x5
	xor r15, rcx
	mov rax, r15					; res = (z >> 5 ^ y << 2)
	mov r15, r8
	mov rcx, r9
	shr r15, 0x3
	shl rcx, 0x4
	xor r15, rcx
	add rax, r15					; res += (y >> 3 ^ z << 4)
	mov r15, r11
	and r15, 0x3
	xor r15, r13					; i = (p & 3) ^ e
	xor rcx, rcx
	mov ecx, dword[rdx + r15 * 0x4]	; j = key[i]
	xor rcx, r9						; j ^= z
	mov r15, r10
	xor r15, r8						; i = sum ^ y
	add r15, rcx					; i += j
	xor rax, r15					; res ^= i
	pop rcx
	pop r15
	leave
	ret

dcpr_algo:
	call dcpr_xxtea
	call dcpr_rot_xor
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
	lea rdx, [rel text_key1]
	call dcpr_algo
	
;	mov edi, 0x1
;	lea rsi, [rel woody]
;	mov rdx, 0xe
;	mov rax, 0x1
;	syscall

	pop rdx
	pop rsp
	pop rsi
	pop rdi
	pop rax
	popf
	jmp 0xffffffff
	text_key1 dq 0x0
	text_key2 dq 0x0
	text_addr dq 0x0
	text_size dq 0x0

end:
