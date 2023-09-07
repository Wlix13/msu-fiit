// Задача matrix: Максимальные элементы матриц
// Дано:
// const MAXN = 1000;
// type matrix = array[1..MAXN, 1..MAXN] of real;
// var A, B: matrix;

// Необходимо реализовать процедуру swap(A, B, N1, M1, N2, M2), меняющую местами максимальные элементы матрицы A размера N1*M1 и матрицы B размера N2*M2.
// Считать, что в каждой матрице только один максимальный элемент. Решение должно использовать описанные структуры и получать ответ с помощью требуемой функции.

// Формат входных данных
// В первой строке вводится четыре целых числа N1, M1, N2, М2 - размеры матриц A и B
// ( 1 ≤ N1, M1, N2, М2 ≤ 1000 ).
// В следующих N1 строках вводится по М1 вещественных чисел - элементы матрицы А.
// Далее в N2 строках вводится по M2 вещественных чисел - элементы матрицы B.

// Формат результата
// В первых N1 строках выводится по M1 вещественных чисел - элементы матрицы A после преобразования.
// В следующих N2 строках выводится по M2 вещественных чисел - элементы матрицы B после преобразования.
// Корректность чисел будет проверяться с точностью до пяти знаков после десятичной точки.

program matrix_max_swap;

const
    MAXN = 1000;
type
    matrix = array[1..MAXN, 1..MAXN] of real;
var
    A, B: matrix;
    N1, M1, N2, M2: integer;

procedure inputMatix(N, M: integer; var A: matrix);
{ Ввод матрицы }
var
    i, j: integer;
begin
    for i := 1 to N do
        for j := 1 to M do
            read(A[i, j]);
end;

procedure printMatrix(N, M: integer; var A: matrix);
{ Вывод матрицы }
var
    i, j: integer;
begin
    for i := 1 to N do
    begin
        for j := 1 to M do
            write(A[i, j]:0:5, ' ');
        writeln;
    end;
end;

procedure maximum(N, M: integer; var A: matrix; var max: real; var i, j: integer);
{ Поиск максимального элемента и его индексов в матрице A}
var
    k, l: integer;
begin
    max := A[1, 1];
    i := 1;
    j := 1;
    for k := 1 to N do
        for l := 1 to M do
            if A[k, l] > max then
            begin
                max := A[k, l];
                i := k;
                j := l;
            end;
end;

procedure swap(N1, M1, N2, M2: integer; var A, B: matrix);
{ Меняет местами максимальные элементы матриц A и B }
var
    maxA, maxB: real;
    iA, jA, iB, jB: integer;
begin
    maximum(N1, M1, A, maxA, iA, jA);
    maximum(N2, M2, B, maxB, iB, jB);
    A[iA, jA] := maxB;
    B[iB, jB] := maxA;
end;


begin
    // Заполнение матриц
    readln(N1, M1, N2, M2);
    inputMatix(N1, M1, A);
    inputMatix(N2, M2, B);

    // Обмен максимальных элементов
    swap(N1, M1, N2, M2, A, B);

    // Вывод матриц
    printMatrix(N1, M1, A);
    printMatrix(N2, M2, B);
end.