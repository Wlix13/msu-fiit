// Задача frequent: Наиболее частый символ
// Дано:
// const MAXN = 10000;
// type word = packed array[1..MAXN] of 'a'..'z';
// var W: word;

// Необходимо реализовать функцию frequent(W, N), которая определяет символ, который чаще других встречается в слове W длины N.
// Считать, что такой символ единственный. Решение должно использовать описанные структуры и получать ответ с помощью требуемой функции.

// Формат входных данных
// В первой строке вводится целое число – N ( 1 ≤ N ≤ 10000 ).
// Во второй строке вводятся N символов – элементы массива W.

// Формат результата
// Вывести один символ – ответ на задачу.

program frequent;

const
    MAXN = 10000;
type
    word = packed array[1..MAXN] of 'a'..'z';

var 
    W: word;
    N, i: integer;


function frequent(W: word; N: integer): char;
{ Наиболее частый символ }
var
    i, j, max, count: integer;
    tmp: char;
begin
    max := 0;
    for i := 1 to N do
    begin
        // Подсчитываем количество вхождений символа
        count := 0;
        for j := 1 to N do
            // Если i-й символ совпадает с последующими, то увеличиваем счетчик
            if W[i] = W[j] then
                count := count + 1;
        if count > max then
        begin
            // Запоминаем символ
            max := count;
            tmp := W[i];
        end;
    end;
    frequent := tmp;
end;

begin
    // Заполение массива
    readln(N);
    for i := 1 to N do
        read(W[i]);

    // Вывод результата
    writeln(frequent(W, N));
end.