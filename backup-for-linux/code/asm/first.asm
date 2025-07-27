section .data
    msg db 'Hello, World!', 10
    len equ $ - msg

section .text
    global _start

_start:
    ; write(1, msg, len)
    mov rax, 1          ; syscall номер (1 = write)
    mov rdi, 1          ; fd (1 = stdout)
    mov rsi, msg ; указатель на строку
    mov rdx, len; длина строки
    mov r10, 39
    syscall             ; 64-bit использует syscall вместо int 0x80

    ; exit(0)
    mov rax, 60         ; syscall номер (60 = exit)
    mov rdi, 0          ; код возврата
    syscall
