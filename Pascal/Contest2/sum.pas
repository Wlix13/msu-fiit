// Задача sum: Сумма подпоследовательности
// Дан массив из N различных целых чисел a1...aN. Необходимо найти сумму чисел, расположенных между максимальным и минимальным элементами массива (включая их самих).
// Использование дополнительных массивов не допускается.

// Формат входных данных
// В первой строке вводится целое число - N ( 1 ≤ N ≤ 100 ).
// Во второй строке вводятся N различных целых чисел ai ( | ai | ≤ 32000 ).

// Формат результата
// Вывести одно число - ответ на задачу.

program sum;
var
    a: array [1..100] of Integer;
    i, n, min_i, max_i, s: Longint;

begin
    // Инициализация переменных
    min_i := 1;
    max_i := 1;
    s := 0;

    // Заполнение массива
    readln(n);
    for i := 1 to n do
        read(a[i]);
    
    // Поиск индекса с минимальным и максимальным элементами
    for i := 1 to n do
    begin
        if a[i] < a[min_i] then
            min_i := i;
        if a[i] > a[max_i] then
            max_i := i;
    end;

    // Подсчет суммы
    if min_i < max_i then {Если минимальный элемент находится левее максимального}
        for i := min_i to max_i do
            s := s + a[i]
    else {Если минимальный элемент находится правее максимального}
        for i := max_i to min_i do
            s := s + a[i];
    
    writeln(s);
end.