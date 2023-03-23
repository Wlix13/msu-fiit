

%include 'io.inc'

section .bss
    N equ 5
    A resb N

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

    ; Find max
    mov ecx, N
    xor ebx, ebx
    mov eax, dword[A] ; First element is max
    loop_max:
        cmp eax, dword[A + (ebx + 1) * 4] ; Compare with next element
        jge loop_max_1 ; If greater or equal, continue
        mov eax, dword[A + (ebx + 1) * 4] ; If less, set new max
    loop_max_1:
        inc ebx
        loop loop_max

    ; Print max
    PRINT_STRING 'Maximum is: '
    PRINT_DEC 4, eax
    NEWLINE

    ; Print array
    PRINT_STRING 'Array is: '
    NEWLINE
    mov ecx, N
    xor ebx, ebx
    loop_output:
        mov eax, dword[A + ebx * 4]
        PRINT_DEC 4, eax
        inc ebx
        loop loop_output
    NEWLINE
    xor eax, eax
    ret

    