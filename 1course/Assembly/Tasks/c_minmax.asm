; Найти максимаум из двух чисел, используя внешние функции из C: scanf и printf

%include 'io.inc'
CEXTERN printf
CEXTERN scanf
section .rodata
    format1 db "%d", 0
    format2 db "%d", 10, 0

section .text
    global CMAIN
CMAIN:
    ; Пролог
    push ebp
    mov ebp, esp

    ; Выравнивание стека
    and esp, -16
    sub esp, 16

    ; Форматная стока для scanf
    mov dword[esp], format1

    ; Получаем первое число a
    lea eax, [esp+12]
    mov dword[esp+4], eax
    call scanf

    ; Получаем второе число b
    lea eax, [esp+8]
    mov dword[esp+4], eax
    call scanf

    ; Сравниваем a и b
    mov eax, dword[esp+12]
    cmp eax, dword[esp+8]
    jg a_greater_b

    ; Если b > a, то выводим b
    mov eax, dword[esp+8]
    jmp print

a_greater_b:
    ; Если a > b, то выводим a
    mov eax, dword[esp+12]


print:
    ; Форматная строка для printf
    mov dword[esp], format2

    ; Выводим максимум
    mov dword[esp+4], eax
    call printf

    ; Эпилог
    mov esp, ebp
    pop ebp
    ret
