%include "io.inc"

; Опишите макрос IFEQ x, y, lab, k, реализующий действие: 
; if x = y then goto lab. 
; x и y - имена знаковых переменных одинакового размера, k - размер переменных в байтах (k = 1, 2, 4).
; Макрос может использовать регистр eax без сохранения.
%macro IFEQ 4
%if %4 = 1
    mov al, byte[%1]
    cmp al, byte[%2]
%endif
%if %4 = 2
    mov ax, word[%1]
    cmp ax, word[%2]
%endif
%if %4 = 4
    mov eax, dword[%1]
    cmp eax, dword[%2]
%endif
je %3
%endmacro