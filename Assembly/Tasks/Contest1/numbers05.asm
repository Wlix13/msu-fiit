; Задача numbers05: Смена знака
; Дана непустая последовательность ненулевых целых 32-битных чисел, за которыми следует число 0. Определить, сколько раз в этой последовательности меняется знак.

; В данной задаче запрещается использовать операции деления.

; Формат входных данных
; В единственной строке вводится последовательность ненулевых целых 32-битных числел, заканчивающаяся числом 0.

; Формат результата
; Вывести одно число - ответ на задачу.

%include "io.inc"
section .bss
    a resd 1
    number resd 1
section .text
    global CMAIN
CMAIN:
    mov ecx, -1             ; счетчик смен знака
    GET_DEC 4, a            ; считываем первое число
    mov eax, dword[a]       ; в eax
    cmp eax, 0              ; сравниваем с 0
    je end                  ; если 0, то конец
    jg flag_more            ; если больше 0 
    jl flag_less            ; если меньше 0
flag_more:
    mov ebx, 1              ; первое число больше 0, значит флаг больше
    inc ecx                 ; увеличиваем счетчик смен знака
    jmp cycle               ; переходим к циклу
flag_less:
    mov ebx, 0              ; первое число меньше 0, значит флаг меньше
    inc ecx                 ; увеличиваем счетчик смен знака
    jmp cycle               ; переходим к циклу
cycle:
    GET_DEC 4, a            ; считываем очередное число
    mov eax, dword[a]       ; в eax
    cmp eax, 0              ; сравниваем с 0
    je cycle_end            ; если 0, то конец
    jg cycle_more           ; если больше 0
    jl cycle_less           ; если меньше 0
cycle_more:
    cmp ebx, 0              ; сравниваем флаг с 0
    je flag_more            ; если флаг 0, то меняем флаг на больше
    jmp cycle               ; если флаг больше, то переходим к следующему числу
cycle_less:
    cmp ebx, 1              ; сравниваем флаг с 1
    je flag_less            ; если флаг 1, то меняем флаг на меньше
    jmp cycle               ; если флаг меньше, то переходим к следующему числу
cycle_end:
    PRINT_DEC 4, ecx   ; выводим number
    xor eax, eax
    ret
end:
    xor eax, eax
    ret