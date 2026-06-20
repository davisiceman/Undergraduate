section .data
    array1 db 2, 4, 6, 8, 10, 20, 40 ; Declare array1
    array2 db 0, 0, 0, 0, 0, 0, 0    ; Declare array2
    len equ 7                        ; Length of the arrays
    newline db 0xA                   ; Newline character
    msg1 db "Array1 elements:", 0xA, 0
    msg2 db "Array2 elements (multiplied by 5):", 0xA, 0

section .bss

section .text
    global _start

_start:
    ; Print Array1
    mov rdi, msg1
    call print_string
    mov rcx, 0            ; Initialize counter to 0
print_array1:
    cmp rcx, len          ; Check if counter == len
    jge print_array2      ; If equal or greater, go to print_array2
    movzx rax, byte [array1 + rcx]
    call print_number
    inc rcx               ; Increment counter
    jmp print_array1      ; Loop

print_array2:
    ; Multiply each element of Array1 by 5 and store in Array2
    mov rcx, 0            ; Reset counter to 0
multiply_elements:
    cmp rcx, len          ; Check if counter == len
    jge output_array2     ; If equal or greater, go to output_array2
    movzx rax, byte [array1 + rcx] ; Load element from array1
    imul rax, rax, 5      ; Multiply by 5
    mov [array2 + rcx], al ; Store result in array2
    inc rcx               ; Increment counter
    jmp multiply_elements ; Loop

output_array2:
    ; Print Array2
    mov rdi, msg2
    call print_string
    mov rcx, 0            ; Initialize counter to 0
print_array2:
    cmp rcx, len          ; Check if counter == len
    jge exit              ; If equal or greater, exit
    movzx rax, byte [array2 + rcx]
    call print_number
    inc rcx               ; Increment counter
    jmp print_array2      ; Loop

exit:
    mov rax, 60           ; Exit system call
    xor rdi, rdi          ; Status 0
    syscall

; Helper Functions
print_string:
    mov rax, 1            ; sys_write
    mov rdi, 1            ; stdout
    mov rsi, rdi          ; String to print
    mov rdx, [rdi - 1]    ; String length
    syscall
    ret

print_number:
    push rax
    mov rsi, rsp
    call itoa             ; Convert number to string
    mov rax, 1            ; sys_write
    mov rdi, 1            ; stdout
    mov rsi, rsp          ; String to print
    mov rdx, rsp          ; String length
    syscall
    pop rax
    ret

itoa:
    ; Convert number in RAX to string
    xor rcx, rcx
    mov rdi, rsp
    test rax, rax         ; If zero
    jz zero_case          ; Jump to zero case
reverse_loop:
;jmp sm- rx;base rx sa
