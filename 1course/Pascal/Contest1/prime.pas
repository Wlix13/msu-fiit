// Задача prime: Простое число
// Дано натуральное число N. Необходимо проверить, является ли это число простым. В случае положительного ответа вывести "YES", в противном случае вывести "NO".

// Формат входных данных
// Вводится одно число N ( 1 ≤ N ≤ 1000000 ).

// Формат результата
// Вывести "YES" или "NO" - ответ на задачу.
var
    N,i: LongInt;
    flag: boolean;
begin
    readln(N);
    i := 2;
    flag := true;
    while i*i <= N do
    begin
        if N mod i = 0 then
            flag := false;
        i := i + 1;
    end;
    if N = 1 then
        flag := false;
    if flag then
        writeln('YES')
    else
        writeln('NO');
end.