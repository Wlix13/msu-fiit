;На стандартном потоке ввода задаётся массив из N (N = 25) целых чисел и число k (k < N).
;Реализуйте функцию
;void shift_left(int *x, int n, int k)
;которая выполняет циклический сдвиг массива на k позиций влево.
;Функция должна удовлетворять соглашению cdecl.
;На стандартный поток вывода напечатайте результат работы указанной функции. 

%include "io.inc"

section .bss 
    N equ 25
    A resd N
    
section .text
    global CMAIN

    
shift_left:
    xor ebx, ebx
    
    ; Пролог функции
    push ebp
    mov ebp, esp
    
    ; Сохраняем в стек
    push ebx
    push edi
    
    ; Сдвиг
    mov edx, dword[ebp + 16]
    imul edx, 4
        
    ; Размер массива
    mov edi, dword[ebp + 12] 
    
    ; Адрес массива
    mov eax, dword[ebp + 8]
    mov ecx, edi
    
    .first_loop:
        push dword[eax + 4 * ebx]
        inc ebx
        loop .first_loop
    mov ecx, edi
    .second_loop:
        pop dword[eax + 4 * edi - edx]
        loop .second_loop
        
    ; Эпилог
    mov esp, ebp
    pop ebp    
   ; leave
    ret

CMAIN:
    xor ebx, ebx
    mov ecx, N
    
    ; Ввод массива
    loop_input:
        GET_DEC 4, [A + 4 * ebx]
        inc ebx
        loop loop_input
        
    ; Ввод сдвига
    GET_DEC 4, eax
    
    ; Отправка на стек
    push eax
    push dword N
    push dword A
    
    ; Вызов
    call shift_left
    
    ; Возвращение стека
    add esp, 12
    xor ebx, ebx
    mov ecx, A
    
    ; Вывод массива
    print_loop:
        PRINT_DEC 4, [A + 4 * ebx]
        inc ebx
        loop print_loop
    xor eax, eax
    ret