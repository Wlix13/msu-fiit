// Задача fib: Число Фибоначчи
// Дано натуральное число N. Необходимо проверить, является ли оно числом Фибоначчи. В случае положительного ответа вывести "YES", в противном случае вывести "NO".

// Формат входных данных
// Вводится одно число N ( 1 ≤ N ≤ 1000000 ).

// Формат результата
// Вывести "YES" или "NO" - ответ на задачу.

program fib;
var
    n, a, b, c: LongInt;
begin
    readln(n);
    a := 1;
    b := 1;
    c := 0;
    if n = 1 then
        writeln('YES')
    else
    begin
        while c < n do
        begin
            c := a + b;
            a := b;
            b := c;
        end;
        if c = n then
            writeln('YES')
        else
            writeln('NO');
    end;
end.