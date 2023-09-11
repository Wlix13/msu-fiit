// Задача negative: Удаление отрицательных элементов
// Дана последовательность L из N целых чисел. Необходимо удалить из нее все отрицательные элементы.

// В данной задаче запрещается использовать массивы. Для хранения последовательности необходимо использовать односвязные списки. Для решения задачи опишите процедуру delete(L), которая удаляет из списка L все отрицательные элементы.

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

procedure delete(var L: List);
{ Удаляет отрицательные элементы в списке L }
var
    p: List;
begin
    if L = nil then
        exit;
    if L^.data < 0 then
    begin
        p := L;
        L := L^.next;
        dispose(p);
        delete(L);
    end
    else
        delete(L^.next);
end;

var
    L: List;
    n: integer;

begin
    // Заполнение списка
    read(n);
    input(L, n);

    // Удаление отрицательных элементов
    delete(L);

    // Вывод результата
    print(L);

    // Очистка памяти
    clear(L);
end.
