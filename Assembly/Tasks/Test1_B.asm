%include "io.inc"

section .bss
    N equ 255
    a resd N ; массив
    
section .text
    global CMAIN
CMAIN:
    mov ecx, N                         ; кол-во в строке
init:
    mov dword[a + ecx * 4 - 4], 0      ; заполняем нулями
    loop init
input:
    GET_CHAR eax                       ; вводим символ
    cmp eax, '.'                       ; если конец строки
    je input_end                       ; окончание
    inc dword[a + eax * 4]
    jmp input
input_end:
    xor ebx, ebx
print:
    cmp ebx,  N                        ; сравнение с макисмальной
    je out                             ; выход
    cmp ebx, 'A'                       ; проходимся по буквам
    jl next
    cmp ebx, 'Z'
    jg next
    cmp dword[a + ebx * 4], 1
    jle next
    PRINT_CHAR ebx                     ; вывод
    
next:
    inc ebx
    jmp print
    
out:
    xor eax, eax
    ret