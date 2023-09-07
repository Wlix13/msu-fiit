// Задача digits: Арифметическая прогрессия цифр
// Дан текст ненулевой длины, состоящий из цифр и заглавных латинских букв. Текст оканчивается точкой. Необходимо определить, состоит ли данный текст только из цифр, причем их числовые значения образуют арифметическую прогрессию.
// Использование массивов и строк не допускается.

// Формат входных данных
// В единственной строке вводится последовательность символов, оканчивающаяся точкой.

// Формат результата
// Вывести "YES" или "NO" - ответ на задачу.

program digits;
var
    c: char;
    prev, cur, diff, numbers: integer;

begin
    prev := -100;
    diff := -100;
    numbers := 0;
    read(c);
    while c <> '.' do
    begin
        if (c >= '0') and (c <= '9') then
        begin
            cur := ord(c) - ord('0');
            if prev <> -100 then
            begin
                if diff = -100 then
                    diff := cur - prev
                else
                if cur - prev <> diff then
                begin
                    writeln('NO');
                    exit;
                end;
            end;
            prev := cur;
        end
        else
        begin
            writeln('NO');
            exit;
        end;
        numbers := numbers + 1;
        read(c);
    end;
    if numbers = 1 then
        writeln('NO')
    else
        writeln('YES');
end.