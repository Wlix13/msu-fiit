

%include 'io.inc'

section .bss
    N equ 5
    A resd N
    B resd N

section .text
    global CMAIN

CMAIN:
    ; Read array
    mov ecx, N
    xor ebx, ebx
    loop_input:
        GET_DEC 4, eax
        mov dword[A + ebx * 4], eax
        inc ebx
        loop loop_input

    ; Print array A
    PRINT_STRING 'Starting array is: '
    NEWLINE
    mov ecx, N
    xor ebx, ebx
    loop_output_start:
        mov eax, dword[A + ebx * 4]
        PRINT_DEC 4, eax
        inc ebx
        loop loop_output_start
    NEWLINE

    ; Reverse A and store in B
    mov ecx, N
    xor ebx, ebx
    loop_reverse:
        mov eax, dword[A + ebx * 4]
        mov dword[B + (ecx - 1) * 4], eax
        inc ebx
        loop loop_reverse


    ; Print array B
    PRINT_STRING 'Reversed array is: '
    NEWLINE
    mov ecx, N
    xor ebx, ebx
    loop_output_reversed:
        mov eax, dword[B + ebx * 4]
        PRINT_DEC 4, eax
        inc ebx
        loop loop_output_reversed
    NEWLINE
    xor eax, eax
    ret

    