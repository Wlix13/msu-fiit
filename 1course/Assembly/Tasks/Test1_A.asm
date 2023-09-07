%include "io.inc"
section .bss
    a resd 1
    N resd 1
section .text
    global CMAIN
CMAIN:
    GET_UDEC 4, N           ; вводим N
    GET_DEC 4, a            ; вводим первое число
    mov eax, dword[a]       ; сохраняем его в eax
    dec dword[N]            ; уменьшаем N на 1
loop:
    cmp dword[N], 0         ; проверяем, не закончилась ли последовательность
    je loop_end             ; если закончилась, то переходим к выводу
    GET_DEC 4, a            ; вводим следующее число
    dec dword[N]            ; уменьшаем N на 1
    cmp dword[a], eax       ; сравниваем с предыдущим
    jle out
    mov eax, dword[a]       ; сохраняем его в eax
    jmp loop

loop_end:
    PRINT_DEC 4, 1
    xor eax, eax
    ret
    
 out:
    PRINT_DEC 4, 0
    xor eax, eax
    ret