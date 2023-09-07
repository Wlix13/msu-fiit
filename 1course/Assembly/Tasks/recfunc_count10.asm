; Рекурсиваня функция, которая считает количество цифр в числе
%include 'io.inc'

section .text
    global CMAIN

rec_count:
    push ebp
    mov ebp, esp
    sub esp, 4
    cmp dword[ebp+8], 10
    jb .exit
    mov eax, dword[ebp+8]
    mov ecx, 10
    xor edx, edx
    div ecx
    mov dword[esp], eax
    call rec_count
    inc eax
    mov esp, ebp
    pop ebp
    ret 


.exit:
    mov eax, 1
    mov esp, ebp
    pop ebp
    ret

CMAIN:
    GET_UDEC 4, eax
    push eax
    call rec_count
    add esp, 4
    PRINT_DEC 4, eax
    NEWLINE
    xor eax, eax
    ret
