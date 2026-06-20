section .data
    format_key db "Node Key: %d", 10, 0
    format_prev db "  Previous Node Address: %016x", 10, 0
    format_next db "  Next Node Address: %016x", 10, 0
    format_newline db 10, 0

section .bss
    nodes resb 96              ; 4 nodes of 24 bytes each (key: 4, next: 8, prev: 8)

section .text
    extern printf
    global _start

_start:
    ; Base address of nodes array
    lea rdi, [rel nodes]

    ; Initialize Node 1
    mov dword [rdi], 1                 ; Set key = 1
    lea rsi, [rdi + 24]                ; Address of Node 2
    mov qword [rdi + 8], rsi           ; Set next pointer to Node 2
    mov qword [rdi + 16], 0            ; Set prev pointer to NULL

    ; Initialize Node 2
    lea rsi, [rdi + 24]                ; Address of Node 2
    mov dword [rsi], 2                 ; Set key = 2
    lea rdx, [rdi + 48]                ; Address of Node 3
    mov qword [rsi + 8], rdx           ; Set next pointer to Node 3
    mov qword [rsi + 16], rdi          ; Set prev pointer to Node 1

    ; Initialize Node 3
    lea rsi, [rdi + 48]                ; Address of Node 3
    mov dword [rsi], 3                 ; Set key = 3
    lea rdx, [rdi + 72]                ; Address of Node 4
    mov qword [rsi + 8], rdx           ; Set next pointer to Node 4
    lea rdx, [rdi + 24]                ; Address of Node 2
    mov qword [rsi + 16], rdx          ; Set prev pointer to Node 2

    ; Initialize Node 4
    lea rsi, [rdi + 72]                ; Address of Node 4
    mov dword [rsi], 4                 ; Set key = 4
    mov qword [rsi + 8], 0             ; Set next pointer to NULL
    lea rdx, [rdi + 48]                ; Address of Node 3
    mov qword [rsi + 16], rdx          ; Set prev pointer to Node 3

    ; Print all nodes
    xor rsi, rsi                       ; Loop counter (node index)

print_nodes:
    mov rax, rsi                       ; Store loop counter
    imul rax, rax, 24                  ; Offset for the current node (24 bytes per node)
    add rax, rdi                       ; Address of the current node

    ; Print key
    mov edx, dword [rax]               ; Load key (32-bit)
    lea rdi, [rel format_key]          ; Format string for key
    call printf

    ; Print previous node address
    mov rdx, qword [rax + 16]          ; Load previous pointer (64-bit)
    lea rdi, [rel format_prev]         ; Format string for prev pointer
    call printf

    ; Print next node address
    mov rdx, qword [rax + 8]           ; Load next pointer (64-bit)
    lea rdi, [rel format_next]         ; Format string for next pointer
    call printf

    ; Print newline
    lea rdi, [rel format_newline]
    call printf

    ; Move to next node
    inc rsi
    cmp rsi, 4                         ; Check if all nodes are printed
    jl print_nodes

    ; Exit program
    mov rax, 0x2000001                 ; sys_exit
    xor rdi, rdi                       ; Exit code 0
    syscall
