// Задача trace: След матрицы
// Даны две вещественные матрицы размера N*N. Вывести на экран квадрат матрицы, имеющей наименьший след (сумму диагональных элементов). Считать, что такая матрица одна.

// Формат входных данных
// В первой строке вводится целое число – N ( 1 ≤ N ≤ 100 ).
// В 2*N последующих строках вводится по N вещественных чисел: в первых N строках - элементы первой матрицы, в следующих N строках – элементы второй матрицы.

// Формат результата
// Вывести N строк по N вещественных чисел – квадрат матрицы с наименьшим следом.
// Корректность ответа будет проверяться с точностью до пяти знаков после десятичной точки.


program trace;

type 
    TMatrix = array[1..100, 1..100] of real;

var
    N: integer;
    A, B, tmp: TMatrix;
    traceA, traceB: real;

procedure inputMatix(N: integer; var A: TMatrix);
{ Ввод матрицы }
var
    i, j: integer;
begin
    for i := 1 to N do
        for j := 1 to N do
            read(A[i, j]);
end;

procedure printMatrix(N: integer; var A: TMatrix);
{ Вывод матрицы }
var
    i, j: integer;
begin
    for i := 1 to N do
    begin
        for j := 1 to N do
            write(A[i, j]:0:5, ' ');
        writeln;
    end;
end;

function trace(N: integer; var A: TMatrix): real;
{ Возвращает след матрицы }
var
    i: integer;
    tmp: real;
begin
    tmp := 0;
    for i := 1 to N do
        tmp := tmp + A[i, i];
    trace := tmp;
end;

procedure multiplyMatrix(N: integer; var A, B, C: TMatrix);
{ Умножение матриц }
var
    i, j, k: integer;
begin
    for i := 1 to N do
        for j := 1 to N do
        begin
            C[i, j] := 0;
            for k := 1 to N do
                C[i, j] := C[i, j] + A[i, k] * B[k, j];
        end;
end;


begin
    // Заполнение матриц
    readln(N);
    inputMatix(N, A);
    inputMatix(N, B);

    // Вычисление следов
    traceA := trace(N, A);
    traceB := trace(N, B);

    // Нахождение квадрата матрицы с наименьшим следом
    if traceA < traceB then
        multiplyMatrix(N, A, A, tmp)
    else
        multiplyMatrix(N, B, B, tmp);

    // Вывод результата
    printMatrix(N, tmp);
end.