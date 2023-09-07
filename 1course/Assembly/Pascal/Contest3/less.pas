// Задача less: Количество делителей
// Необходимо реализовать логическую функцию less(a,b) от натуральных чисел, которая возвращает true, если у числа a меньше делителей, чем у числа b, и false иначе.
// Решение должно получать ответ с помощью требуемой функции.

// Формат входных данных
// В единственной строке вводятся два целых числа - a и b ( 1 ≤ a,b ≤ 32000 ).

// Формат результата
// Вывести "YES", если less(a,b) = true, и "NO" иначе.

program less;

var
    a, b: integer;

function divCount(n: integer): integer;
{ Возвращает количество делителей числа n }
var
    i, count: integer;
begin
    // У каждого числа есть делители 1 и само число
    count := 2;
    
    // Считаем делители до корня из числа
    for i:=2 to trunc(sqrt(n)) do 
        if n mod i = 0 then
            count := count + 2;
    
    // Если число полный квадрат, то уменьшаем на 1
    if sqrt(n) = trunc(sqrt(n)) then
        count := count - 1;
    divCount := count;
end;

function less(a, b: integer): boolean;
{ Возвращает true, если у числа a меньше делителей, чем у числа b, и false иначе }
begin
    less := divCount(a) < divCount(b);
end;

begin
    // Ввод данных
    readln(a, b);

    // Вывод результата
    if less(a, b) then
        writeln('YES')
    else
        writeln('NO');
end.