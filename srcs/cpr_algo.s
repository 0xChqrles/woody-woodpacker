section .data
	random db "/dev/random", 0x0

section .text
	global rot_xor
	global cpr_algo

; -----------
; | ROT_XOR |
; -----------

rot_xor:
	push rdi
	push rsi
	add rsi, rdi

rot_xor_loop:
	xor byte [rdi], 0xff
	add byte [rdi], 0x2a
	inc rdi
	cmp rdi, rsi
	jne rot_xor_loop
	pop rsi
	pop rdi
	ret

; ---------
; | XXTEA |
; ---------

xxtea:
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

	mov r14, rsi
	dec r14								; i = sz - 1;
	xor rdx, rdx
	mov rax, 0x34
	div rsi
	add rax, 0x6
	mov r12, rax						; rounds = 6 + 52 / sz;
	xor r10, r10						; sum = 0;
	xor r9, r9
	mov r9d, dword [rdi + r14 * 0x4]	; z = text[sz - 1]
	pop rdx

xxtea_rounds_loop:				; do {
	add r10d, 0x9e3779b9			; sum += DELTA
	mov r13, r10
	shr r13, 0x2
	and r13, 0x3					; e = (sum >> 2) & 3;
	mov r11, 0

xxtea_loop:							; for (p = 0; p < sz - 1; p++) {
	cmp r11d, r14d
	jae xxtea_end_loop

	inc r11
	mov r8d, dword [rdi + r11 * 0x4]	; y = text[p + 1];
	dec r11
	call xxtea_mx
	add dword [rdi + r11 * 0x4], eax	; text[p] += MX;
	mov r9d, dword [rdi + r11 * 0x4]	; z = text[p];

	inc r11
	jmp xxtea_loop

xxtea_end_loop:							; }
	mov r8d, dword [rdi]				; y = text[0];
	call xxtea_mx
	add dword [rdi + r14 * 0x4], eax	; text[n - 1] += MX;
	mov r9d, dword [rdi + r14 * 0x4]	; z = text[p];

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

; ------------
; | CPR_ALGO |
; ------------

; void    cpr_algo(uint32_t *text, size_t sz, uint32_t key[4]);

; *text => rdi    sz => rsi    key => rdx

cpr_algo:
	push rbp
	mov rbp, rsp
	sub rsp, 0x10
	call rot_xor
	call xxtea
	leave
	ret
