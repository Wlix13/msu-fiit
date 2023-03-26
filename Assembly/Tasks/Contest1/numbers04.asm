; Задача numbers04: Фибоначчи-100000
; Вывести первое из чисел Фибоначчи, превосходящее 100000.

; Необходимо получить это число алгоритмически.

; Формат входных данных
; -

; Формат результата
; Вывести одно число - ответ на задачу.

%include "io.inc"
section .text
    global CMAIN
CMAIN:
    mov eax, 1          ; первое число Фибоначчи
    mov ebx, 1          ; второе число Фибоначчи
cycle:
    cmp eax, 100000     ; проверка на выход за границу
    ja exit             ; если вышли, то конец
    mov ecx, eax        ; сохраняем предыдущее число
    add eax, ebx        ; суммируем с предыдущим
    mov ebx, ecx        ; сохраняем предыдущее число
    jmp cycle           ; переходим к следующей итерации
exit:
    PRINT_UDEC 4, eax   ; выводим ответ
    xor eax, eax
    ret