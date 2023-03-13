%include 'io.inc'
section .text         ; c := 10 * (a + b) – d mod 27
global CMAIN          ; a, b, d - числа со знаком в формате двойного слова
CMAIN:
  GET_DEC 4, ecx      ; ввод a
  GET_DEC 4, ebx      ; ввод b
  GET_DEC 4, eax      ; ввод d
  add ecx, ebx        ; ecx := a + b
  imul ecx, ecx, 10   ; ecx := 10 * (a + b)
  cdq                 ; (edx, eax) := dqword
  mov ebx, 27
  idiv ebx            ; edx := d mod 27
  sub ecx, edx        ; ecx := 10 * (a + b) – d mod 27
  PRINT_DEC 4, ecx    ; вывод ecx
  NEWLINE
  xor eax, eax
  ret