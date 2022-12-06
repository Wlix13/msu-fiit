// Задача max3: Три максимума
// Дана последовательность из не менее чем трех различных натуральных чисел ai, за которой следует 0. Необходимо определить три наибольших числа среди них.
// Использование массивов не допускается.

// Формат входных данных
// В единственной строке вводится последовательность чисел ai ( 0 < ai ≤ 32000 ). Строка завершается числом 0.

// Формат результата
// Вывести в одну строку три максимальных числа в порядке убывания.

program max_3;
var
    tmp, max1, max2, max3: Integer;
begin
    read(tmp);
    max1:=tmp;
    while tmp<>0 do
    begin
        if tmp>max1 then
        begin
            max3:=max2;
            max2:=max1;
            max1:=tmp
        end; 
        if (tmp<max1) and (tmp>max2) then
        begin
            max3:=max2;
            max2:=tmp;
        end;
        if (tmp>max3) and (tmp<max2) and (tmp<max1) then
            max3:=tmp;
        read(tmp);
    end;
    writeln(max1,' ',max2,' ',max3)
end.