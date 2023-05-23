%include "io.inc"
; Ввести последовательность символов (признак конца последовательности ‘.’) и заменить каждую цифру на следующую по порядку, цифру ‘9’ заменить на ‘0’.
%macro  NEXT_DIG 1
    cmp %1, '0'
    jb %%exit
    cmp %1, '8'
    ja %%not1
    inc %1
    jmp %%exit
%%not1: cmp %1, '9'
    jne %%exit
    mov %1, '0'
   
%%exit:
%endmacro

section .text
    global CMAIN
CMAIN:
.cycle:
    GET_CHAR al
    cmp al, '.'
    je .exit
    NEXT_DIG al
    PRINT_CHAR al
    jmp .cycle
.exit:
    xor eax, eax
    ret