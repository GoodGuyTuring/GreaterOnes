SECTION .data

; define the fibonacci number that should be calculated
n:      dq   10

SECTION .text

global _start

_start:
    ; call Fibonacci function f(n)
    mov     rdi, [n] 
    mov		rax, 0   ; parameter: fibonacci number to calculate
    call    f           ; call function

    ; print calculated Fibonacci number on stdout
    call    printnumber

    ; exit process with exit code 0
    mov     rax, 60
    mov     rdi, 0
    syscall
 
; f: Calculates a Fibonacci number
;   f(n) = {n, if n<=1; f(n-1)+f(n-2), else}.
;   Parameter: Integer n >= 0, passed on stack
;   Returns:   Fibonacci number f(n), returned in rax
f:
	cmp rdi, 0
	je bot
	cmp rdi, 1
	je bot
	mov r8, rdi
	push r8
	sub rdi, 1
	call f
	sub rdi, 1
	call f
	pop rdi
	jmp ende
bot: 
	add rax, 1
ende:    
	ret

