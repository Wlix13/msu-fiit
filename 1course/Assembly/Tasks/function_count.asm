; Написать функцию, которая считает количество десятичных цифр в числе N


%include 'io.inc'

section .text
    global CMAIN

count:
    push ebp                ; пролог
    mov ebp, esp            ; функции

    xor ecx, ecx            ; счетчик
    push ebx                ; сохраняем ebx

    mov ebx, 10
    mov eax, [ebp + 8]      ; eax = N

    cycle:
        xor edx, edx        ; обнуляем edx
        div ebx             ; делим на 10
        inc ecx             ; иначе увеличиваем счетчик
        cmp eax, 0          ; если N = 0, то выходим из цикла
        jne cycle           ; иначе продолжаем делить на 10
        je cycle_end        ; иначе выходим из цикла


    cycle_end:
        pop ebx             ; восстанавливаем ebx
        mov eax, ecx        ; возвращаем результат
        pop ebx             ; восстанавливаем ebx
        ret

CMAIN:
    GET_DEC 4, ecx          ; вводим число c
    push ecx                ; сохраняем число c
    call count              ; вызываем функцию count
    add esp, 4              ; восстанавливаем стек
    PRINT_DEC 4, eax        ; выводим результат
    NEWLINE
    xor eax, eax
    ret