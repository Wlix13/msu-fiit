; Рекурсиваня функция, которая последовательность (до нуля) распечатывает в обратном порядке
%include 'io.inc'

section .text
    global CMAIN

rec_print:
    push ebp
    mov ebp, esp
    GET_DEC 4, eax
    cmp eax, 0
    je end
    push eax
    call rec_print
    pop eax
    PRINT_DEC 4, eax
    mov esp, ebp
    pop ebp
    ret

end:
    mov esp, ebp
    pop ebp
    ret


CMAIN:
    call rec_print
    NEWLINE
    xor eax, eax
    ret
