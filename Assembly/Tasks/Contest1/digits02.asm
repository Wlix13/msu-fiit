; Задача digits01: Наибольшая цифра
; Дано целое неотрицательное 32-битное число. Необходимо найти наибольшую цифру в его десятичной записи.

; В данной задаче не разрешается считывать число посимвольно.

; Формат входных данных
; Вводится единственное целое неотрицательное 32-битное число N.

; Формат результата
; Вывести одно число - наибольшую цифру в десятичном представлении числа N.

%include "io.inc"
section .bss
    a resd 1
section .text
    global CMAIN
CMAIN:
    GET_UDEC 4, a       ; считываем беззнаковое число
    mov eax, dword[a]   ; переносим в eax 
    mov ecx, 10         ; основание системы счисления
    mov ebx, 0          ; счетчик
cycle:
    cmp eax, 0          ; проверка на ноль
    je pred_exit        ; если ноль, то выходим
    cdq                 ; расширение для деления
    div ecx             ; деление на основание системы счисления
    add ebx, 1          ; увеличиваем счетчик
    jmp cycle           ; переходим в начало цикла
pred_exit:
    cmp ebx, 0          ; проверка на ноль
    jne exit            ; если не ноль, то выходим
    mov ebx, 1          ; иначе, счетчик равен 1
    jmp exit            ; выходим
exit:
    PRINT_UDEC 4, ebx   ; выводим результат
    xor eax, eax
    ret
