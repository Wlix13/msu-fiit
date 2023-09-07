; Написать функцию pow(int a, int n), которая возводит число a в степень n.
%include 'io.inc'

section .text
    global CMAIN

pow:
    push ebp                ; пролог
    mov ebp, esp            ; функции

    mov eax, 1
    mov ecx, dword[ebp+12]  ; ecx = n
    mov edx, dword[ebp+8]   ; edx: eax = a

    pow_cycle:
        imul eax, edx       ; умножаем edx: eax на а
        loop pow_cycle      ; повторяем цикл, пока ecx не равен 0

    mov esp, ebp            ; эпилог
    pop ebp                 ; функции
    ; leave
    ret

CMAIN:
    GET_DEC 4, eax          ; вводим число а
    GET_UDEC 4, ecx         ; вводим степень n
    push ecx                ; сохраняем степень n
    push eax                ; сохраняем число а
    call pow                ; вызываем функцию pow
    add esp, 8              ; восстанавливаем стек
    PRINT_DEC 4, eax        ; выводим результат
    NEWLINE
    xor eax, eax
    ret