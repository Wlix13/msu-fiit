%include 'io.inc'

section .text
global CMAIN
CMAIN:
    GET_DEC 4, eax      ; Начальный максимум
    cycle:
        GET_DEC 4, ebx  ; Новое число
        cmp ebx, 0      ; Сравнение с 0
        jz end          ; Если 0, то конец
        cmp ebx, eax    ; Проверка на максимум
        jle cycle       ; Не подходит на роль максимума
        mov eax, ebx    ; Подходит на максимум
        jmp cycle       ; Новая итерация

end:
    PRINT_DEC 4, eax
    NEWLINE
    xor eax, eax
    ret

