// Задача scalar: Скалярные произведения
// Дано три вещественных вектора длиной N: a, b и c.
// Необходимо вычислить t = (x,x) - (y,z), где x обозначает тот из векторов, в котором минимальный элемент максимален (считать, что такой вектор единственный), y и z – два других вектора, а (p,q) – скалярное произведение векторов.

// Формат входных данных
// В первой строке вводится целое число – N ( 1 ≤ N ≤ 100 ).
// Во трех последующих строках вводится по N вещественных чисел ai, bi и ci.

// Формат результата
// Вывести одно вещественное число – полученное значение t.
// Корректность ответа будет проверяться с точностью до пяти знаков после десятичной точки.

program scalar;

type
    TArr = array [1..100] of real;

var
  a, b, c: TArr;
  N: integer;
  t, min_a, min_b, min_c: real;

function min(var a: TArr; N: integer): real;
{ Возвращает минимальный элемент массива}
var
    i: integer;
begin
    min := a[1];
    for i := 2 to N do
        if a[i] < min then
            min := a[i];
end;

procedure input(var a: TArr; N: integer);
{ Ввод массива }
var
    i: integer;
begin
    for i := 1 to N do
        read(a[i]);
end;

function scalar(var a, b: TArr; N: integer): real;
{ Возвращает скалярное произведение векторов }
var
  i: integer;
  s: real;
begin
    s := 0;
    for i := 1 to n do
        s := s + a[i] * b[i];
    scalar := s;
end;

begin
    // Заполнение массивов
    readln(N);
    input(a, N);
    input(b, N);
    input(c, N);

    // Вычисление минимальных элементов
    min_a := min(a, N);
    min_b := min(b, N);
    min_c := min(c, N);

    // Поиск x обозначает тот из векторов, в котором минимальный элемент максимален
	if (min_a > min_b) and (min_a > min_c) then 
        t := scalar(a, a, n) - scalar(b, c, n);
	if (min_b > min_a) and (min_b>min_c) then
        t := scalar(b, b, n) - scalar(a, c, n);
	if (min_c > min_a) and (min_c > min_b) then
        t := scalar(c, c, n) - scalar(a, b, n);

    // Вывод результата
    writeln(t:0:5);
end.