%include 'io.inc'

section .bss
    N equ 5
    A resd N*4
    B resd N*4

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

    ; Store positive elements of A at start of B
    ; and then negative
    mov ecx, N
    xor ebx, ebx
    xor edi, edi
    loop_B:
        mov eax, dword[A + ebx * 4]
        cmp eax, 0
        jge positive
        mov dword[B + edi * 4], eax
        inc edi
        jmp next
    positive:
        mov dword[B + ecx * 4 - 4], eax
        dec ecx
    next:
        inc ebx
        loop loop_B


    ; Print array B
    PRINT_STRING 'New array is: '
    NEWLINE
    mov ecx, N
    xor ebx, ebx
    loop_output_B:
        mov eax, dword[B + ebx*4]
        PRINT_DEC 4, eax
        inc ebx
        loop loop_output_B
    NEWLINE

    xor eax, eax
    ret