// Задача concat: Добавление в конец списка
// Даны две последовательности L1 и L2 из N и M целых чисел. Необходимо добавить в конец списка L1 копии всех элементов списка L2 (список L2 должен остаться в неизменном виде).

// В данной задаче запрещается использовать массивы. Для хранения последовательности необходимо использовать односвязные списки. Для решения задачи опишите нерекурсивную процедуру concat(L1,L2), которая добавляет в конец списка L1 копии всех элементов списка L2.

// Формат входных данных
// В первой строке вводится два целых числа N и M — количество элементов последовательностей L1 и L2 ( 0 ≤ N,M ≤ 1000 ).
// В второй строке вводится N целых чисел — элементы последовательности L1 ( |L1i| ≤ 32000 ).
// В третьей строке вводится M целых чисел — элементы последовательности L2 ( |L2i| ≤ 32000 ).

// Формат результата
// Первую строку вывода необходимо начать с метки "L1: ", после которой выводятся элементы списка L1 после модификации.
// Во второй строке выводится список L2 в аналогичном формате.

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

procedure add(var L: List; x: integer);
{ Добавляет элемент в конец списка }
begin
    if L = nil then
    begin
        new(L);
        L^.data := x;
        L^.next := nil;
    end
    else
        add(L^.next, x);
end;

procedure concat(var L1, L2: List);
{ Добавляет в конец списка L1 копии всех элементов списка L2 }
begin
    if L2 = nil then
        exit;
    add(L1, L2^.data);
    concat(L1, L2^.next);
end;

var
    L1, L2: List;
    n, m: integer;

begin
    // Заполнение списков
    read(n, m);
    input(L1, n);
    input(L2, m);

    // Вывод результата
    concat(L1, L2);
    write('L1: ');
    print(L1);
    writeln;
    write('L2: ');
    print(L2);

    // Очистка памяти
    clear(L1);
    clear(L2);
end.

