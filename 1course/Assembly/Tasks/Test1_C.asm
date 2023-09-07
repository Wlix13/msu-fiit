%include "io.inc"
section .bss
    a resd 1
    sum resd 1
section .text
    global CMAIN
divi:
    push ebp                ; пролог
    mov ebp, esp            ; функции

    mov dword[sum], 1       ; сумма делителей
    mov ecx, 2              ; ecx = текущий делитель
   
   cmp dword[ebp + 8], 1    ; Если 1, то несовершенное
   je one_end

    divi_loop:
        mov eax, [ebp + 8]  ; eax = n
        cmp ecx, eax        ; если текущий делитель больше числа
        jge divi_end        ; то выходим из цикла
        xor edx, edx        ; обнуляем edx
        div ecx             ; edx = eax % ecx, eax = eax / ecx
        cmp edx, 0          ; если остаток от деления равен нулю
        jnz divi_next       ; то переходим к следующему делителю
        add dword[sum], eax ; иначе увеличиваем сумму делителей

    divi_next:
        inc ecx             ; переходим к следующему делителю
        jmp divi_loop

    one_end:
        mov eax, 0
        jmp out
        
    divi_end:
        mov eax, dword[sum]
        jmp out
out:
    mov esp, ebp            ; эпилог
    pop ebp                 ; функции
    ret


; Основной код программы
CMAIN:
    mov dword[a], 0              ; количество
    mov ebx, 0              ; текущее число

    read_loop:
        GET_DEC 4, ebx      ; считываем число
        cmp ebx, 0          ; если число равно нулю
        je read_end         ; то выходим из цикла
        push ebx            ; иначе сохраняем число на стек
        call divi           ; вызываем функцию divi
        add esp, 4          ; удаляем число со стека
        
        cmp eax, ebx        ; если сумма делителей равна числу
        je read_next        ; то сохраняем новое максимальное количество делителей
        jmp read_loop

    read_next:
        inc dword[a]
        jmp read_loop

    read_end:
        mov eax, dword[a]
        PRINT_DEC 4, eax      ; выводим максимальное количество делителей
        NEWLINE
    
    xor eax, eax
    ret