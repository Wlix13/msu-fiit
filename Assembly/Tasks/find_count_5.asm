%include 'io.inc'
section .text
global CMAIN
CMAIN:
    GET_UDEC 4, eax     ; Ввод n
    mov ecx, 0          ; Count = 0
    mov ebx, 10         ; Система счисления 10
    cycle:
        cmp eax, 0      ; При n =0
        je cycle_end
        mov edx, 0      ; Расширение n для деления
        div ebx         ; eax = n / 10, edx = n % 10
        cmp edx, 5      ; Проверка нового числа на 5
        jne cycle       ; Не равно 5
        add ecx, 1      ; Count += 1
        jmp cycle       ; Повтор 
cycle_end:
    PRINT_DEC 4, ecx
    NEWLINE
    xor eax, eax
    ret
