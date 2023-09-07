; Задача numbers02: Простое число
; Дано целое 32-битное число. Необходимо определить, является ли это число простым.

; Формат входных данных
; Вводится целое 32-битное число N (N > 1).

; Формат результата
; Вывести 1, если N является простым, и 0 - иначе.

%include "io.inc"
section .bss
    N resd 1
    x resd 1
section .text
    global CMAIN
CMAIN:
    GET_UDEC 4, N       ; ввод числа N
    mov ebx, dword[N]   ; сохраняем его в ebx
    cmp ebx, 1          ; проверка на 1
    je no               ; если 1, то вывод 0
    cmp ebx, 2          ; проверка на 2
    je yes              ; если 2, то вывод 1
    finit               ; инициализация FPU
    fild dword[N]       ; загрузка числа N в FPU
    fsqrt               ; вычисление квадратного корня
    fist dword[x]       ; сохранение результата в x
    mov ecx, dword[x]   ; ecx = x
cycle:
    cmp ecx, 1          ; проверка на 1
    je yes              ; если 1, то вывод 1
    mov eax, ebx        ; eax = N
    xor edx, edx        ; обнуление edx
    div ecx             ; деление eax на ecx
    cmp edx, 0          ; проверка остатка от деления
    je no               ; если остаток есть, то вывод 0
    dec ecx             ; уменьшение ecx на 1
    jmp cycle           ; переход в начало цикла
yes:
    mov eax, 1          ; eax = 1
    jmp end             ; переход в конец программы
no:
    mov eax, 0          ; eax = 0
    jmp end             ; переход в конец программы
end:
    PRINT_UDEC 4, eax   ; вывод результата
    xor eax, eax
    ret