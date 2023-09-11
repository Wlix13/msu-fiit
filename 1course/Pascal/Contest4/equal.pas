// Задача equal: Равенство списков
// Даны две последовательности L1 и L2 из N и M целых чисел. Необходимо проверить эти последовательности на равенство.

// В данной задаче запрещается использовать массивы. Для хранения последовательности необходимо использовать односвязные списки. Для решения задачи требуется описать нерекурсивную логическую функцию equal(L1,L2), которая проверяет два списка на равенство. Сравнение длин последовательностей не допускается.

// Формат входных данных
// В первой строке вводится два целых числа N и M — количество элементов последовательностей L1 и L2 ( 0 ≤ N,M ≤ 1000 ).
// В второй строке вводится N целых чисел — элементы последовательности L1 ( |L1i| ≤ 32000 ).
// В третьей строке вводится M целых чисел — элементы последовательности L2 ( |L2i| ≤ 32000 ).

// Формат результата
// Необходимо вывести "YES", если списки равны, и "NO" — иначе.

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

function equal(L1, L2: List): boolean;
{ нерекурсивно проверяет два списка на равенство}
begin
    while (L1 <> nil) and (L2 <> nil) do
    begin
        if L1^.data <> L2^.data then
        begin
            equal := false;
            exit;
        end;
        L1 := L1^.next;
        L2 := L2^.next;
    end;
    equal := (L1 = nil) and (L2 = nil);
end;

var
    L1, L2: List;
    n, m: integer;

begin

    // Заполнение списков
    read(n, m);
    input(L1, n);
    input(L2, m);

    // Проверка на равенство
    if equal(L1, L2) then
        writeln('YES')
    else
        writeln('NO');

    // Очистка памяти
    clear(L1);
    clear(L2);
end.