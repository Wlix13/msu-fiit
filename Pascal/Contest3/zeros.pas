// Задача zeros: Нулевые строки
// Даны три целых матрицы размера N*M: A, B и C. Вывести на экран ту из них, где больше нулевых строк.
// Если таких матриц несколько, вывести их все в том порядке, в котором они были введены.

// Формат входных данных
// В первой строке вводится два целых числа - N и M ( 1 ≤ N,M ≤ 500 ).
// Во 3*N последующих строках вводится по M целых чисел: в первых N строках - aij, далее bij и в конце cij ( | aij, bij, cij | ≤ 32000 ).

// Формат результата
// Вывести матрицы, содержащие больше всего нулевых строк.

program zeros;

type
    TMatrix = array[1..500, 1..500] of integer;
    TFlag = array['A'..'C'] of boolean;

var
    A, B, C: TMatrix;
    flag: TFlag;
    N, M, zero_a, zero_b, zero_c: integer;
    i: char;

procedure input(var A: TMatrix; N, M: integer);
{ Ввод матрицы }
var
    i, j: integer;
begin
    for i := 1 to N do
        for j := 1 to M do
            read(A[i, j]);
end;

procedure print(var A: TMatrix; N, M: integer);
{ Вывод матрицы }
var
    i, j: integer;
begin
    for i := 1 to N do
    begin
        for j := 1 to M do
            write(A[i, j], ' ');
        writeln;
    end;
end;

function count_zero(var A: TMatrix; N, M: integer): integer;
{ Считает количество нулевых строк в матрице }
var
    i, j, count: integer;
begin
    count := 0;
    for i := 1 to N do
    begin
        for j := 1 to M do
        begin
            if A[i, j] <> 0 then
                break;
            if j = M then
                count := count + 1;
        end;
    end;
    count_zero := count;
end;

procedure check(zero_a, zero_b, zero_c: integer; var flag: TFlag);
{ Проверяет, какая матрица содержит больше нулевых строк }
var
    max: integer;
    i: char;
begin
    // Предполагаем, что нет матриц с нулевыми строками
    for i:= 'A' to 'C' do
        flag[i] := false;
    
    // Находим максимальное количество нулевых строк
    max := zero_a;
    if zero_b > max then
        max := zero_b;
    if zero_c > max then
        max := zero_c;
    
    // Проверяем, какие матрицы содержат максимальное количество нулевых строк
    if zero_a = max then
        flag['A'] := true;
    if zero_b = max then
        flag['B'] := true;
    if zero_c = max then
        flag['C'] := true;
end;


begin
    // Заполнение матриц
    read(N, M);
    input(A, N, M);
    input(B, N, M);
    input(C, N, M);

    // Подсчёт нулевых строк в каждой матрице
    zero_a := count_zero(A, N, M);
    zero_b := count_zero(B, N, M);
    zero_c := count_zero(C, N, M);

    // Определить матрицы с максимальным количеством нулевых строк
    check(zero_a, zero_b, zero_c, flag);

    // Вывод результата
    for i:='A' to 'C' do
        if flag[i] then
            case i of
                'A': print(A, N, M);
                'B': print(B, N, M);
                'C': print(C, N, M);
            end;
end.