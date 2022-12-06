// Задача letters: Уникальные буквы
// Дан текст из строчных латинских букв, за которым следует точка. Вывести в алфавитном порядке все буквы, которые входят в этот текст по одному разу.

// Формат входных данных
// В единственной строке вводится последовательность строчных букв, оканчивающаяся точкой.

// Формат результата
// Вывести в одну строку через пробел все буквы, встречающиеся в тексте ровно один раз.


program letters;
var 
    k : array ['a'..'z'] of integer;
    j : char;
begin 
    for j := 'a' to 'z' do
        k[j] := 0;
    while not eoln do
    begin
        read(j);
        k[j] := k[j] + 1;
    end;
    for j := 'a' to 'z' do
        if k[j] = 1 then
            write(j, ' ');
end. 