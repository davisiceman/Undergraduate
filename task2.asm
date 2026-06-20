section .data
    array db 12, 16, 6, 18, 10, 40, 30 ; Declare array
    len equ 7                          ; Length of the array
    max_msg db "Maximum: ", 0
    min_msg db "Minimum: ", 0
    newline db 0xA, 0

section .bss
    max resb 1
    min resb 1

section .text
    global _start

_start:
    ; Find maximum value
    mov ecx, len
    mov esi, array
    mov al, [array]      ; Initialize max
    mov [max], al
find_max:
    dec ecx
    jz max_done
    movzx eax, byte [esi + 1]
    cmp al, [max]
    jle skip_max
    mov [max], al
skip_max:
    inc esi
    jmp find_max
max_done:

    ; Find minimum value
    mov ecx, len
    mov esi, array
    mov al, [array]      ; Initialize min
    mov [min], al
find_min:
    dec ecx
    jz min_done
    movzx eax, byte [esi + 1]
    cmp al, [min]
    jge skip_min
    mov [min], al
skip_min:
    inc esi
    jmp find_min
min_done:

    ; Print maximum value
    mov ecx, max_msg
    call print_string
    movzx eax, byte [max]
    add eax, '0'
    call print_char
    call print_newline

    ; Print minimum value
    mov ecx, min_msg
    call print_string
    movzx eax, byte [min]
    add eax, '0'
    call print_char
    call print_newline

    ; Exit program
    mov eax, 60
    xor edi, edi
    syscall

; Print string procedure
print_string:
    mov eax, 1
    mov edi, 1
    mov rsi, ecx
    mov edx, 9              ; Adjust length as needed
    syscall
    ret

; Print character procedure
print_char:
    mov eax, 1
    mov edi, 1
    lea rsi, [rsp - 1]
    mov [rsp - 1], al
    mov edx, 1
    syscall
    ret

; Print newline procedure
print_newline:
    mov eax, 1
    mov edi, 1
    mov rsi, newline
    mov edx, 1
    syscall
    ret
