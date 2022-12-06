// Задача sum: Сумма максимумов
// Дано:
// const MAXN = 1000;
// type matrix = array[1..MAXN, 1..MAXN] of real;
// var A: matrix;

// Необходимо реализовать функцию sum(A, N, M), вычисляющую величину t = x1*xn + x2*xn-1 + ... + xn*x1, где xi – максимальный элемент i-й строки матрицы A размера N*M.
// Решение должно использовать описанные структуры и получать ответ с помощью требуемой функции.

// Формат входных данных
// В первой строке вводится два целых числа – N и М ( 1 ≤ N,M ≤ 1000 ).
// Во последующих N строках вводятся по М вещественных чисел – элементы матрицы А.

// Формат результата
// Вывести одно вещественное число – полученное значение t – не менее чем с пятью знаками после десятичной точки.

program sum;

const
    MAXN = 1000;
type
    matrix = array[1..MAXN, 1..MAXN] of real;
var
    A: matrix;
    N, M: integer;
    t: real;

procedure inputMatrix(N, M: integer; var A: matrix);
{ Ввод матрицы }
var
    i, j: integer;
begin
    for i := 1 to N do
        for j := 1 to M do
            read(A[i, j]);
end;

function max(var A: matrix; i: integer): integer;
{ Находим индекс максимального элемента i-й строки матрицы A }
var
    j, max_i: integer;
begin
    max_i := 1;
    for j := 2 to M do
        if A[i, j] > A[i, max_i] then
            max_i := j;
    max := max_i;
end;

function sum(N, M: integer; var A: matrix): real;
{ Вычисляет величину t = x1*xn + x2*xn-1 + ... + xn*x1, где xi – максимальный элемент i-й строки матрицы A размера N*M. }
var
    i: integer;
    t: real;
begin
    t := 0;
    for i := 1 to N do
        t := t + A[i, max(A, i)] * A[N - i + 1, max(A, N - i + 1)];
    sum := t;
end;

begin
    // Заполнение матрицы N*M
    readln(N, M);
    inputMatrix(N, M, A);
    
    // Подсчёт величины t
    t := sum(N, M, A);

    // Вывод результата
    writeln(t:0:5);
end.