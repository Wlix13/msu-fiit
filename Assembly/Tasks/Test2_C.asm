;Задача 2-C: Числовая последовательность
;На стандартном потоке ввода задаётся непустая последовательность целых чисел.
;На стандартный поток вывода напечатайте количество чисел в самой длинной подпоследовательности из подряд идущих положительных чисел.
;При решении задачи для ввода и вывода чисел необходимо использовать функции из стандартной библиотеки Си. Вводимые числа располагать в стеке. Обеспечить выравнивание стека в функции CMAIN.


%include "io.inc"
CEXTERN printf
CEXTERN scanf

section .rodata
    format1 db "%d", 0
    format2 db "%d", 10, 0
    
section .text
    global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ; Счётчики
    xor esi, esi
    xor edi, edi

    ; Пролог
    push ebp
    mov ebp, esp

    ; Выравнивание стека
    and esp, -16
    sub esp, 16
    
    ; Форматная строка для scanf
    mov dword[esp], format1
    
    lea eax, [esp + 12]
    mov dword[esp + 4], eax

    
cycle:
    ; Вызов фукнции
    call scanf
    
    ; Если больше нет ввода -> конец ввода
    cmp eax, 0
    jle print
    
    mov ebx, dword[esp + 12] 
    cmp ebx, 0
    ; Меньше равно нуля -> новый счётчик
    jle new
    ; Увеличить
    inc edi
    ; Проверка на новый максимум
    jmp check
    
new:
    xor edi, edi
    
check:
    cmp edi, esi
    jle loop
    mov esi, edi
    
loop:
    jmp cycle
    
print:
    ; Форматная строка для printf
    mov dword[esp], format2
    
    ; Выводим максимум
    mov dword[esp + 4], esi
    call printf
    
    ; Эпилог
    xor eax, eax
    mov esp, ebp
    pop ebp
    ret