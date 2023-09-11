// Задача recsym: Симметричность подстроки
// Дано:
// type pstring = packed array [1..1000] of char;
// var s: pstring;

// Необходимо описать рекурсивную логическую функцию sym(s,i,j), которая проверяет, симметрична ли часть строки s, начиная с i-го символа и заканчивая j-м.

// Формат входных данных
// В первой строке вводится число N - длина строки ( 1 ≤ N ≤ 1000 ).
// Во второй строке вводится строка из N символов.
// В третьей строке вводится два числа i, j - границы подстроки, симметричность которой надо проверить ( 1 ≤ i ≤ j ≤ N ).

// Формат результата
// Вывести "YES", если подстрока симметрична, и "NO" иначе.

program recsym;

type
    pstring = packed array [1..1000] of char;
var
    s: pstring;
    n, i, j: integer;

procedure input(var s: pstring; n: integer);
{ Ввод строки(массива символов) }
var
    i: integer;
begin
    for i := 1 to n do
        read(s[i]);
end;

function sym(s: pstring; i, j: integer): boolean;
begin
    // Базовый случай рекурсии
    if i = j then
        sym := true
    
    else
        // Если первый и последний символы совпадают, то проверяем симметричность строки со сдвигом
        if s[i] = s[j] then
            sym := sym(s, i + 1, j - 1)
        
        // Если первый и последний символы не совпадают, то строка не симметрична
        else
            sym := false;
end;

begin
    // Заполнение строки(массива символов)
    readln(n);
    input(s, n);

    // Ввод границ подстроки
    readln(i, j);

    // Вывод результата
    if sym(s, i, j) then
        writeln('YES')
    else
        writeln('NO');
end.