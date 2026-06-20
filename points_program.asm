section .data
    prompt_x db "Enter x coordinate: ", 0
    prompt_y db "Enter y coordinate: ", 0
    output_format db "Point %d: x = %d, y = %d", 10, 0
    int_format db "%d", 0
    newline db 10, 0

section .bss
    points resb 40              ; 5 structures of 8 bytes each (x: 4 bytes, y: 4 bytes)
    input_buffer resb 10        ; buffer for reading input

section .text
    extern printf, scanf
    global _start

_start:
    ; Initialize loop counter
    xor rsi, rsi                ; rsi = 0 (loop counter for input)

input_loop:
    ; Calculate address for x
    lea rdi, [rel points]       ; Base address of points array
    mov rdx, rsi                ; Index
    imul rdx, rdx, 8            ; Offset = rsi * 8 (size of each Point structure)
    add rdi, rdx                ; Address of current Point's x

    ; Prompt user for x coordinate
    lea rsi, [rel prompt_x]     ; Load prompt_x address
    call printf                 ; Print prompt

    ; Read x coordinate
    lea rsi, [rel int_format]   ; Load format specifier
    call scanf                  ; Read input into [rdi]

    ; Calculate address for y
    lea rdi, [rel points]       ; Base address of points array
    mov rdx, rsi        
