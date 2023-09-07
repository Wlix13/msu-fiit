// Задача first: Первое вхождение элементов
// Дана последовательность L из N целых чисел. Необходимо оставить в последовательности только первые вхождения одинаковых элементов.

// В данной задаче запрещается использовать массивы. Для хранения последовательности необходимо использовать односвязные списки. Для решения задачи опишите нерекурсивную процедуру first(L), которая оставляет в списке L только первые вхождения равных элементов.

// Формат входных данных
// В первой строке вводится целое число N — количество элементов последовательности L ( 0 ≤ N ≤ 1000 ).
// Во второй строке вводится N целых чисел — элементы последовательности L ( |Li| ≤ 32000 ).

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

procedure first(var L: List);
{ Удаляет повторяющиеся элементы в списке L }

function find(var L: List; x: integer): boolean;
{ Проверяет, есть ли в списке L элемент x }
begin
    if L = nil then
    begin
        find := false;
        exit;
    end;
    if L^.data = x then
    begin
        find := true;
        exit;
    end;
    find := find(L^.next, x);
end;

var
    l_copy: List;
    x: integer;
begin
    if L = nil then
        exit;
    l_copy := nil;
    while L <> nil do
    begin
        x := L^.data;
        if not find(l_copy, x) then
            add(l_copy, x);
        L := L^.next;
    end;
    L := l_copy;
end;


var
    L: List;
    n: integer;

begin
    // Заполнение списка
    read(n);
    input(L, n);

    // Удаление повторяющихся элементов
    first(L);

    // Вывод списка
    print(L);

    // Очистка памяти
    clear(L);
end.

