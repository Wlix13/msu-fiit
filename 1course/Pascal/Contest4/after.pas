// Задача after: Вставка после элемента списка
// Дана последовательность L из N целых чисел. Необходимо вставить новый элемент E1 после каждого вхождения элемента E в L.

// В данной задаче запрещается использовать массивы. Для хранения последовательности необходимо использовать односвязные списки. Для решения задачи опишите процедуру after(L,E,E1), которая вставляет в списке L элемент E1 после каждого вхождения элемента E.

// Формат входных данных
// В первой строке вводится целое число N — количество элементов последовательности L ( 0 ≤ N ≤ 1000 ).
// Во второй строке вводится N целых чисел — элементы последовательности L ( |Li| ≤ 32000 ).
// В третьей строке вводится два числа — E и E1 ( |E|,|E1| ≤ 32000 ).

// Формат результата
// Вывести в одну строку последовательность L после преобразования.

type
    List = ^TNode;
    TNode = record
        data: integer;
        next: List;
    end;

procedure print(L: List);
{ Выводит список }
begin
    if L = nil then
        exit;
    write(L^.data, ' ');
    print(L^.next);
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

procedure after(var L: List; E, E1: integer);
{ Вставляет элемент E1 после каждого вхождения элемента E }
var
    p: List;
begin
    if L = nil then
        exit;
    if L^.data = E then
    begin
        new(p);
        p^.data := E1;
        p^.next := L^.next;
        L^.next := p;
        after(p^.next, E, E1);
    end
    else
        after(L^.next, E, E1);
end;

var
    L: List;
    n, E, E1: integer;

begin
    // Заполнение списка
    read(n);
    input(L, n);

    // Вставка элемента
    read(E, E1);
    after(L, E, E1);
    
    // Вывод результата
    print(L);

    // Очистка памяти
    clear(L);
end.

