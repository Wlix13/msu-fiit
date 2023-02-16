// Задача numbers: Числа без одинаковых цифр
// Вывести в возрастающем порядке все трехзначаные числа, в десятичной записи которых нет одинаковых цифр. Операции деления (/, div и mod) не использовать.

// Формат входных данных
// Входные данные отсутствют.

// Формат результата
// Вывести список требуемых трехзначных чисел (по одному числу в строке).

program numbers;
var
    i, j, k: integer;

begin
    for i := 1 to 9 do
        for j := 0 to 9 do
            for k := 0 to 9 do
            // Проверка наличия одинаковых цифр
            if (i <> j) and (i <> k) and (j <> k) then
                // Построение трёхзначного числа из трёх цифр
                writeln(i * 100 + j * 10 + k);
end.