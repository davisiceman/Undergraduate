section .data
    prompt_name db "What is your first name? ", 0
    prompt_age db "What is your age? ", 0
    prompt_graduation db "When will you graduate? ", 0
    response_format db "Hi %s, when you graduate, your age will be %d.", 10, 0

    fmt_string db "%s", 0       ; format for reading a string with scanf
    fmt_int db "%d", 0          ; format for reading an integer with scanf

section .bss
    name resb 32                ; reserve 32 bytes for the name
    age resd 1                  ; variable for storing the age
    graduation_year resd 1      ; variable for storing the graduation year
    temp_age resd 1             ; variable for storing calculated age at graduation

section .text
    extern printf, scanf
    global _start

_start:
    ; Ask for first name
    push dword prompt_name
    call printf
    add esp, 4

    ; Read first name
    push name
    push dword fmt_string
    call scanf
    add esp, 8

    ; Ask for age
    push dword prompt_age
    call printf
    add esp, 4

    ; Read age
    push age
    push dword fmt_int
    call scanf
    add esp, 8

    ; Ask for graduation year
    push dword prompt_graduation
    call printf
    add esp, 4

    ; Read graduation year
    push graduation_year
    push dword fmt_int
    call scanf
    add esp, 8

    ; Calculate age at graduation
    mov eax, [age]
    mov ebx, [graduation_year]
    sub ebx, eax
    add eax, ebx
    mov [temp_age], eax

    ; Print the final message
    push dword [temp_age]
    push dword name
    push dword response_format
    call printf
    add esp, 12

    ; Exit the program
    mov eax, 1                ; sys_exit
    xor ebx, ebx              ; exit code 0
    int 0x80
