%include "io.inc"
; Описать макрос ABS r, x ; r=|x|, который помещает в регистр r модуль переменной x (x и r в формате dword). 
%macro ABS 2
    mov %1, dword[%2]
    cmp %1, 0
    jge %%m
    neg %1
 %%m:
 %endmacro

section .bss
    x  resd 1
    y  resd 1

section .text
    global CMAIN
CMAIN:
    mov ebp, esp
    GET_DEC 4, [x]
    ABS eax, x
    PRINT_DEC 4, eax
    NEWLINE
    GET_DEC 4, [y]
    ABS ebx, y
    PRINT_DEC 4, ebx
    NEWLINE
    xor eax, eax
    ret