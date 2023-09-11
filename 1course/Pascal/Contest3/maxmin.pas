// Задача maxmin: Снова минимумы и максимумы
// Дано три массива вещественных чисел длиной N: a, b и c. Необходимо вычислить t согласно следующим правилам:

// t = max( (b+c)i ) + min(ci)  при min(ai) ≥ max(bi),
// t = min(bi) / max(ai) + max(ci) / min( (b+c)i )  иначе

program maxmin;

type
    TArr = array [1..100] of real;

var
    a, b, c, tmp: TArr;
    N: integer;
    t, minA, maxB, minC, maxC: real;

function min(N: integer; a: TArr): real;
{ Возвращает минимальный элемент массива}
var
    i, min_i: integer;
begin
    min_i := 1;
    for i := 2 to N do
        if a[i] < a[min_i] then
            min_i := i;
    min := a[min_i];
end;

function max(N:integer; a: TArr): real;
{ Возвращает максимальный элемент массива}
var
    i, max_i: integer;
begin
    max_i := 1;
    for i := 2 to N do
        if a[i] > a[max_i] then
            max_i := i;
    max := a[max_i];
end;

procedure input(N: integer; var a: TArr);
{ Ввод массива }
var
    i: integer;
begin
    for i := 1 to N do
        read(a[i]);
end;

procedure sum(N:integer; var a,b: TArr; var c: TArr);
{ Сумма двух массивов }
var
    i: integer;
begin
    for i := 1 to N do
        c[i] := a[i] + b[i];
end;

begin
    // Заполнение массивов
    readln(N);
    input(N, a);
    input(N, b);
    input(N, c);

    // Нахождение минимумов и максимумов для формулы
    minA := min(N, a);
    maxB := max(N, b);
    sum(N, b, c, tmp);

    // Вычисление t
    if minA >= maxB then
    begin
        minC := min(N, c);
        t := max(N, tmp) + minC;
    end
    else
    begin
        maxC := max(N, c);
        t := min(N, b) / max(N, a) + maxC / min(N, tmp);
    end;

    // Вывод результата
    writeln(t:0:5);
end.