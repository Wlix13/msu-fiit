%include 'io.inc'

section .bss
    N equ 5
    B resw N

section .text
    global CMAIN

CMAIN:
    ; Read array B of short 
    mov ecx, N
    xor ebx, ebx
    loop_input:
        GET_DEC 2, eax
        mov [B + ebx * 2], eax
        inc ebx
        loop loop_input

    ; Find sum of array B
    mov ecx, N
    xor ebx, ebx
    xor eax, eax
    loop_sum:
        add eax, dword[B + ebx * 2]
        inc ebx
        loop loop_sum
    

    ; Print sum
    PRINT_STRING 'Sum of array is: '
    PRINT_DEC 2, eax
    NEWLINE

    xor eax, eax
    ret
    