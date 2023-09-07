// Задача sum: Сумма элементов списка
// Дана последовательность L из N целых чисел. Необходимо найти сумму элементов между максимальным и минимальным элементами последовательности, включая и эти элементы (считать, что все элементы последовательности различны).

// В данной задаче запрещается использовать массивы. Для хранения последовательности необходимо использовать односвязные списки. Для решения задачи требуется описать нерекурсивную функцию sum(L), которая возвращает необходимую сумму для списка L.

// Формат входных данных
// В первой строке вводится целое число N — количество элементов последовательности L ( 1 ≤ N ≤ 1000 ).
// В второй строке вводится N целых чисел — элементы последовательности L ( |Li| ≤ 32000 ).

// Формат результата
// Необходимо вывести одно число - требуемую сумму.

type
    List = ^TNode;
    TNode = record
        data: integer;
        next: List;
    end;

procedure input(var L: List; n: integer);
{ Создаёт список из n элементов }
begin
    if n = 0 then
    begin
        L := nil;
        exit;
    end;
    new(L);
    read(L^.data);
    input(L^.next, n - 1);
end;

procedure clear(var L: List);
{ Очищает список }
begin
    if L = nil then
        exit;
    clear(L^.next);
    dispose(L);
end;

function sum(L: List): integer;
{ Возвращает сумму элементов между максимальным и минимальным элементами списка L, включая и эти элементы }
procedure minmax(var x, y: integer);
{ Переставляет x и y так, чтобы x <= y }
var
    tmp: integer;
begin
    if x > y then
    begin
        tmp := x;
        x := y;
        y := tmp;
    end;
end;

var
    i, j, k, min, max, tmp: integer;
    l_copy: List;
begin
    // Инициализация переменных
    l_copy := L;
    min := L^.data;
    max := L^.data;
    i := 1;
    j := 1;
    tmp := 0;

    // Поиск минимального и максимального элементов
    while l_copy <> nil do
    begin
        if l_copy^.data < min then
            min := l_copy^.data;
        if l_copy^.data > max then
            max := l_copy^.data;
        l_copy := l_copy^.next;
    end;

    // Поиск индекса минимального элемента
    l_copy := L;
    while l_copy^.data <> min do
    begin
        l_copy := l_copy^.next;
        i := i + 1;
    end;
    
    // Поиск индекса максимального элемента
    l_copy := L;
    while l_copy^.data <> max do
    begin
        l_copy := l_copy^.next;
        j := j + 1;
    end;
    minmax(i, j); { Перестановка i и j, если i > j }

    // Поиск суммы элементов между минимальным и максимальным элементами
    l_copy := L;
    for k := 1 to i - 1 do
        l_copy := l_copy^.next;
    for k := i to j do
    begin
        tmp := tmp + l_copy^.data;
        l_copy := l_copy^.next;
    end;

    // Возвращение результата
    sum := tmp;
end;

var
    L: List;
    n: integer;
begin
    // Заполнение списка
    read(n);
    input(L, n);

    // Вывод результата
    writeln(sum(L));

    // Очистка памяти
    clear(L);
end.