; Написать функцию zeros(int *a, int N), которая считает количество нулей в массиве a длины N.

%include 'io.inc'


section .bss
    N equ 5
    A resd N

section .text
    global CMAIN

zeros:
    push ebp                    ; пролог
    mov ebp, esp                ; функции
    push edi                    ; сохраняем edi в стек

    mov edi, dword[ebp + 8]          ; адрес массива

    xor eax, eax                ; счетчик нулей
    xor edx, edx                ; i = 0
    mov ecx, dword[ebp + 12]   ; N

    cycle:
        cmp dword[edi + edx * 4], 0 ; если a[i] == 0
        je zero
        jmp next
    zero:
        inc eax
    next:
        inc edx
        loop cycle
    
    ; pop edi                     ; эпилог
    mov esp, ebp                ; функции
    pop ebp
    ret

CMAIN:
    ; Считываем массив A
    mov ecx, N
    xor ebx, ebx
    loop_input:
        GET_DEC 4, eax
        mov dword[A + ebx * 4], eax
        inc ebx
        loop loop_input

    push dword N                ; сохраняем длину массива
    push dword A                ; сохраняем адрес массива
    call zeros              ; вызываем функцию zeros
    add esp, 8              ; восстанавливаем стек
    PRINT_DEC 4, eax        ; выводим результат
    NEWLINE
    xor eax, eax
    ret