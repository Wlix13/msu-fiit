// Задача norm: Меры матриц
// Даны три вещественных матрицы размера N*M: A, B и C. Вычислить величину t:
// t = ( || A || + || B || + || C || ) / || A + B + C ||,
// где || D || = max(|D1j|) + max(|D2j|) + ... + max(|DNj|).
// Считать, что || A + B + C || не обращается в 0.

// Формат входных данных
// В первой строке вводится два целых числа - N и M ( 1 ≤ N,M ≤ 500 ).
// Во 3*N последующих строках вводится по M вещественных чисел: в первых N строках - aij, далее bij и в конце cij.

// Формат результата
// Вывести одно вещественное число t - ответ на задачу.
// Корректность чисел будет проверяться с точностью до пяти знаков после десятичной точки.

program norm;

type
    TMatrix = array[1..500, 1..500] of real;

var
    N, M: integer;
    A, B, C: TMatrix;
    t, norm_a, norm_b, norm_c, norm_sum: real;

procedure sum(var A, B, C: TMatrix; N, M: integer; var norma: real);
{ Подсчёт нормы суммы матриц }
var
    i, j: integer;
    max, tmp: real;
begin
    norma := 0;
    max := 0;
    for i := 1 to N do
    begin
        for j := 1 to M do
        begin
            tmp := A[i, j] + B[i, j] + C[i, j];
            if abs(tmp) > max then
                max := abs(tmp);
        end;
        norma := norma + max;
        max := 0;
    end;
end;

procedure input(var A: TMatrix; N, M: integer; var norma: real);
{ Ввод матрицы и подсчёт её нормы}
var
    i, j: integer;
    max: real;
begin
    max := 0;
    for i := 1 to N do
    begin
        for j := 1 to M do
        begin
            read(A[i, j]);
            if abs(A[i, j]) > max then
                max := abs(A[i, j]);
        end;
        norma := norma + max;
        max := 0;
    end;
end;

function maximum(A: TMatrix; i: integer): real;
{ Возвращает максимальный элемент i-й строки матрицы }
var
    j: integer;
begin
    maximum := 0;
    for j := 1 to M do
        if abs(A[i, j]) > maximum then
            maximum := abs(A[i, j]);
end;

begin
    // Заполнение матриц и подсчёт их норм
    read(N, M);
    input(A, N, M, norm_a);
    input(B, N, M, norm_b);
    input(C, N, M, norm_c);

    // Нахождение нормы суммы матриц
    sum(A, B, C, N, M, norm_sum);

    // Вычисление t по формуле
    t := (norm_a + norm_b + norm_c) / norm_sum;

    // Вывод результата
    writeln(t:0:5);
end.