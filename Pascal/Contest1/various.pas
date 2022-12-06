// Задача various: Различные числа
// Дана неубывающая последовательность из N целых чисел a1...aN. Необходимо определить количество различных элементов в этой последовательности.
// Использование массивов не допускается.

// Формат входных данных
// В первой строке вводится одно число - N ( 1 ≤ N ≤ 100 ).
// Во второй строке вводятся N чисел ai ( | ai | ≤ 32000, ai ≤ ai+1 ).

// Формат результата
// Вывести одно число - ответ на задачу.

program various;
var
    n, i, count, a, b: integer;
begin
    readln(n);
    count := 1;
    read(a);
    for i := 2 to n do
    begin
        read(b);
        if a <> b then
            count := count + 1;
        a := b;
    end;
    writeln(count);
end.