; Задача chars06: Буква в начале и в конце слова
; Данa непустая последовательность непустых слов из маленьких латинских букв. Необходимо подсчитать количество слов этой последовательности, которые начинаются и оканчиваются одной и той же буквой.

; Формат входных данных
; Вводится последовательность непустых слов из маленьких латинских букв; между соседними словами - зяпятая, после последнего слова - точка.

; Формат результата
; Вывести одно число - количество слов, которые начинаются и оканчиваются одной и той же буквой.

%include "io.inc"
section .bss
    c resb 1
    number resd 1
section .text
    global CMAIN
CMAIN:
    mov ecx, 0              ; счетчик слов
loop:
    GET_CHAR c              ; считываем символ
    mov al, byte[c]         ; в al - текущий символ
    mov dl, al              ; в dl - предыдущий символ
cycle:
    mov bl, dl              ; в bl - предыдущий символ
    GET_CHAR c              ; считываем символ
    mov dl, byte[c]         ; в dl - текущий символ
    cmp dl,'.'              ; проверка на конец строки
    je cycle_pred_end       ; если точка, то проверяем предыдущий символ
    cmp dl, ','             ; проверка на разделитель
    jne jump                ; если не запятая, то переходим к следующему символу
    cmp al, bl              ; сравниваем предыдущий и текущий символы
    je count                ; если предыдущий равен текущему, то увеличиваем счетчик
    jmp loop                ; иначе переходим к следующему слову
count:
    inc ecx                 ; увеличиваем счетчик
    jmp loop                ; переходим к следующему слову
jump:
    jmp cycle               ; переходим к следующему символу
cycle_pred_end:
    cmp al, bl              ; сравниваем предыдущий и текущий символы
    jne cycle_end           ; если предыдущий не равен текущему, то выходим из цикла
    inc ecx                 ; увеличиваем счетчик
    jmp cycle_end           ; выходим из цикла
cycle_end:
    mov dword[number], ecx  ; записываем счетчик в память
    PRINT_UDEC 4, [number]  ; выводим счетчик
    xor eax, eax
    ret