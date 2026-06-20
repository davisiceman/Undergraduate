section .data
    msg1 db "A program to add two numbers", 10
    msg2 db "Value of the first Integer Number is 25", 10
    msg3 db "Memory location of the first Integer Number is ", 0
    msg4 db "Value of the second Integer Number is 13", 10
    msg5 db "Memory location of the second Integer Number is ", 0
    msg6 db "Sum of the two numbers is ", 0
    newline db 10

section .bss
    first resb 4
    second resb 4
    sum resb 4

section .text
    global _start

_start:
    ; Assign values to the numbers
    mov dword [first], 25
    mov dword [second], 13

    ; Print the messages and values
    ; Print "A program to add two numbers"
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, 26
    int 0x80

    ; Print "Value of the first Integer Number is 25"
    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, 36
    int 0x80

    ; Print memory location of the first integer
    mov eax, 4
    mov ebx, 1
    mov ecx, msg3
    mov edx, 43
    int 0x80
    mov eax, 4
    mov ebx, 1
    mov ecx, first
    mov edx, 4
    int 0x80
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; Print "Value of the second Integer Number is 13"
    mov eax, 4
    mov ebx, 1
    mov ecx, msg4
    mov edx, 36
    int 0x80

    ; Print memory location of the second integer
    mov eax, 4
    mov ebx, 1
    mov ecx, msg5
    mov edx, 43
    int 0x80
    mov eax, 4
    mov ebx, 1
    mov ecx, second
    mov edx, 4
    int 0x80
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

    ; Add the numbers
    mov eax, [first]
    add eax, [second]
    mov [sum], eax

    ; Print the sum
    mov eax, 4
    mov ebx, 1
    mov ecx, msg6
    mov edx, 26
    int 0x80
    mov eax, 4
    mov ebx, 1
    mov ecx, sum
    mov edx, 4
    int 0x80

    ; Exit
    mov eax, 1
    int 0x80
