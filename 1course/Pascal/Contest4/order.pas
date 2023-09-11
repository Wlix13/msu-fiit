// Задача order: Сортировка списка
// Дана последовательность L из N целых чисел. Необходимо вывести ее элементы в порядке неубывания.

// В данной задаче запрещается использовать массивы. Для хранения последовательности необходимо использовать односвязные списки.

// Формат входных данных
// В первой строке вводится целое число N — количество элементов последовательности L ( 0 ≤ N ≤ 1000 ).
// Во второй строке вводится N целых чисел — элементы последовательности L ( |Li| ≤ 32000 ).

// Формат результата
// Вывести в одну строку элементы последовательности L в порядке неубывания.


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

procedure sort(var L: List);
{ Сортирует список }
var
    l_copy, tmp: List;
    tmp_data: integer;
begin
    l_copy := L;
    while l_copy <> nil do
    begin
        tmp := l_copy^.next;
        while tmp <> nil do
        begin
            if l_copy^.data > tmp^.data then
            begin
                tmp_data := l_copy^.data;
                l_copy^.data := tmp^.data;
                tmp^.data := tmp_data;
            end;
            tmp := tmp^.next;
        end;
        l_copy := l_copy^.next;
    end;
end;

var
    L: List;
    n: integer;

begin
    // Заполнение списка
    read(n);
    input(L, n);

    // Сортировка списка
    sort(L);

    // Вывод результата
    print(L);

    // Очистка памяти
    clear(L);
end.