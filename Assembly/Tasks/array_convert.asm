%include 'io.inc'

section .bss
    N equ 5
    A resd N
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

    ; Convert word array B to dword array A
    mov ecx, N
    xor ebx, ebx
    loop_convert:
        movsx eax, word[B + ebx * 2]
        mov dword[A + ebx * 4], eax
        inc ebx
        loop loop_convert
    

    ; Print array A
    PRINT_STRING 'Array is: '
    NEWLINE
    mov ecx, N
    xor ebx, ebx
    loop_output_start:
        mov eax, dword[A + ebx * 4]
        PRINT_DEC 4, eax
        inc ebx
        loop loop_output_start
    NEWLINE

    xor eax, eax
    ret