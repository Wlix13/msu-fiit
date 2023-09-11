// Задача merge_sub: Слияние списков (разность множеств)
// Даны две последовательности L1 и L2 из N и M целых чисел. Необходимо сформировать новую последовательность L, включив в нее по одному разу элементы, которые входят в L1, но не входят в L2.

// В данной задаче запрещается использовать массивы. Для хранения последовательности необходимо использовать односвязные списки. Для решения задачи опишите процедуру merge_sub(L1,L2, L), которая формирует требуемый список L.

// Формат входных данных
// В первой строке вводится два целых числа N и M — количество элементов последовательностей L1 и L2 ( 0 ≤ N,M ≤ 1000 ).
// В второй строке вводится N целых чисел — элементы последовательности L1 ( |L1i| ≤ 32000 ).
// В третьей строке вводится M целых чисел — элементы последовательности L2 ( |L2i| ≤ 32000 ).

// Формат результата
// Необходимо вывести в одну строку элементы последовательности L (порядок элементов значения не имеет).

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

procedure merge_sub(L1, L2: List; var L: List);
{ Слияние списков }
begin
    if L1 = nil then
        exit;
    while L1 <> nil do
    begin
        if not find(L2, L1^.data) and (not find(L, L1^.data)) then
            add(L, L1^.data);
        L1 := L1^.next;
    end;
end;

var
    L1, L2, L: List;
    n, m: integer;

begin
    // Заполнение списков
    read(n, m);
    input(L1, n);
    input(L2, m);

    // Вывод результата
    merge_sub(L1, L2, L);
    print(L);

    // Очистка памяти
    clear(L1);
    clear(L2);
    clear(L);
end.
