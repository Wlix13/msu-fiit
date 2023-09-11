// Задача recdigits: Рекурсивный подсчет цифр
// Даны символьный текст, оканчивающийся точкой. Необходимо описать рекурсивную функцию или процедуру, подсчитывающую количество цифр в данном тексте.

// Формат входных данных
// В единственной строке вводится последовательность символов, оканчивающаяся точкой.

// Формат результата
// Вывести количество цифр в тексте.

program recdigits;

function recdigits(count: integer): integer;
var
    c: char;
begin
    read(c);
    // Базовый случай рекурсии
    if c = '.' then
        recdigits := count
    // Рекурсивный вызов
    else
        if c in ['0'..'9'] then
            recdigits := recdigits(count + 1)
        else
            recdigits := recdigits(count);
end;

begin
    writeln(recdigits(0));
end.