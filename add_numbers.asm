section .data
    num1 dq 25
    num2 dq 13

section .text
    global _main

_main:
    mov rax, [rel num1]
    mov rbx, [rel num2]
    add rax, rbx                   ; Result stored in RAX

    ; Exit syscall
    mov rax, 0x2000001             ; macOS exit syscall number
    xor rdi, rdi                   ; Exit code 0
    syscall
