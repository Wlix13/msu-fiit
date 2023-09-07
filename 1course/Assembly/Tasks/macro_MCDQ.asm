%include "io.inc"

; Считая, что в ассемблере нет команды cdq, описать макрос MCDQ, реализующий указанную команду.
%macro MCDQ 0
    mov  edx, eax
    sar  edx, 31
%endmacro

section .text
    global CMAIN
CMAIN:
    GET_DEC  4, eax
    MCDQ
    PRINT_DEC  4, edx
    NEWLINE
    mov ecx, 3
    idiv ecx
    PRINT_DEC  4, eax
    NEWLINE
    xor eax, eax
    ret 