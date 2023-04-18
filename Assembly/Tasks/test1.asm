%include "io.inc"
section .bss
    a resb 10
section .text
    global CMAIN
CMAIN:
    GET_UDEC 4, eax             ; eax = число
    mov ecx, 10                 ; ecx - система счисления
    cmp eax, 0                  ; проверка на 0                  
    jz out                      ; если 0, то выход

numbers:
    xor edx, edx                ; расширение для деления
    div ecx                     ; деление на систему счисления
    inc byte[a+edx]             ; запись остатка в массив
    cmp eax, 0                  ; проверка на 0
    jnz numbers                 ; если не 0, то продолжаем деление
    
    xor eax, eax                ; обнуление eax
    mov ebx, 10                 ; ebx - система счисления
print:
    num:
        cmp byte[a+ecx-1], 0    ; проверка на 0
        je endnum               ; если 0, то к следующему числу
        dec ecx                 ; если не 0, то продолжаем деление
        mul ebx                 ; умножение на систему счисления
        add eax, ecx            ; прибавление остатка
        inc ecx                 ; увеличение счетчика
        dec byte[a+ecx-1]       ; уменьшение остатка
        jmp num                 ; переход к умножению
    endnum:
        loop print              ; переход к следующему числу
        jmp out

out:
    PRINT_DEC 4, eax            ; вывод числа
    NEWLINE        
    xor eax, eax
    ret