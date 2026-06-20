section .data
    sourceFile db "file1.txt", 0
    destFile db "file2.txt", 0
    buffer db 1024 dup(0)      ; 1024-byte buffer for file contents

section .text
    global _start

_start:
    ; Open source file (file1.txt) for reading
    mov rax, 0x2000003         ; sys_open
    lea rdi, [rel sourceFile]  ; RIP-relative pointer to source file name
    xor rsi, rsi               ; O_RDONLY
    syscall
    mov r12, rax               ; store source file descriptor

    ; Check if source file opened successfully
    cmp r12, 0
    jl error_exit

    ; Open destination file (file2.txt) for writing (create if not exists)
    mov rax, 0x2000005         ; sys_open
    lea rdi, [rel destFile]    ; RIP-relative pointer to destination file name
    mov rsi, 0x602             ; O_CREAT | O_WRONLY (octal 0602 = rw-------)
    mov rdx, 0x1b6             ; file permissions (octal 0666 = rw-rw-rw-)
    syscall
    mov r13, rax               ; store destination file descriptor

    ; Check if destination file opened successfully
    cmp r13, 0
    jl error_exit

copy_loop:
    ; Read from source file
    mov rax, 0x2000004         ; sys_read
    mov rdi, r12               ; source file descriptor
    lea rsi, [rel buffer]      ; RIP-relative pointer to buffer
    mov rdx, 1024              ; bytes to read
    syscall
    test rax, rax              ; check if end of file (0 bytes read)
    jz close_files             ; if end of file, exit loop
    mov r14, rax               ; store number of bytes read

    ; Write to destination file
    mov rax, 0x2000004         ; sys_write
    mov rdi, r13               ; destination file descriptor
    lea rsi, [rel buffer]      ; RIP-relative pointer to buffer
    mov rdx, r14               ; number of bytes to write
    syscall
    jmp copy_loop              ; continue loop

close_files:
    ; Close source file
    mov rax, 0x2000006         ; sys_close
    mov rdi, r12               ; source file descriptor
    syscall

    ; Close destination file
    mov rax, 0x2000006         ; sys_close
    mov rdi, r13               ; destination file descriptor
    syscall

    ; Exit program
    mov rax, 0x2000001         ; sys_exit
    xor rdi, rdi               ; exit code 0
    syscall

error_exit:
    ; Exit program with error
    mov rax, 0x2000001         ; sys_exit
    mov rdi, 1                 ; exit code 1
    syscall
