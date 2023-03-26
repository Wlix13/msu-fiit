; Задача bits03: 5 единиц подряд
; Данa непустая последовательность целых 32-битных чисел. Необходимо подсчитать количество чисел этой последовательности, в двоичном представлении которых содержится не менее 5 подряд стоящих единиц.

; В данной задаче запрещается использовать операции деления.

; Формат входных данных
; В единственной строке вводится целое 32-битное число N - длина последовательности, после которого вводится N целых 32-битных чисел - элементы последовательности.

; Формат результата
; Вывести одно число - количество чисел, в двоичном представлении которых содержится не менее 5 подряд стоящих единиц.

%include "io.inc"
section .bss
    N resd 1
    a resd 1
    number resd 1
section .text
    global CMAIN
CMAIN:
    mov ebx, 0              ; ebx - счетчик чисел, в двоичном представлении которых содержится не менее 5 подряд стоящих единиц
    GET_UDEC 4, N           ; N - длина последовательности
loop:
    cmp dword[N], 0         ; проверка на пустую последовательность
    je loop_end             ; если последовательность пустая, то выход из цикла
    GET_DEC 4, a            ; a - элемент последовательности
    dec dword[N]            ; уменьшение длины последовательности
    mov eax, dword[a]       ; eax - элемент последовательности
    mov ecx, 0              ; ecx - счетчик единиц
cycle:
    cmp ecx, 5              ; проверка на 5 единиц подряд
    jae reassign            ; если 5 единиц подряд, то переход к следующему числу
    cmp eax, 0              ; проверка на нулевой элемент
    je loop                 ; если нулевой элемент, то переход к следующему числу
    shr eax, 1              ; сдвиг вправо на 1 бит
    jc counter              ; если последний бит равен 1, то переход к counter
    xor ecx, ecx            ; иначе обнуление счетчика
    jmp cycle               ; переход к следующему биту
counter:
    inc ecx                 ; увеличение счетчика
    jmp cycle               ; переход к следующему биту
reassign:
    inc ebx                 ; увеличение счетчика чисел, в двоичном представлении которых содержится не менее 5 подряд стоящих единиц
    jmp loop                ; переход к следующему числу
loop_end:
    mov dword[number], ebx  ; number - количество чисел, в двоичном представлении которых содержится не менее 5 подряд стоящих единиц
    PRINT_DEC 4, [number]   ; вывод результата
    xor eax, eax
    ret