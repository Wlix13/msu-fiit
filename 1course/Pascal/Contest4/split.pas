// Задача split: Разделение списка
// Дана последовательность L из N целых чисел. Необходимо разделить L на две последовательности: L1 — из положительных элементов L, и L2 — из остальных элементов. Относительный порядок элементов в новых последовательностях должен сохраняться.

// В данной задаче запрещается использовать массивы. Для хранения последовательности необходимо использовать односвязные списки. Для решения задачи опишите процедуру split(L,L1,L2), которая по списку L формирует требуемые списки L1 и L2.

// Формат входных данных
// В первой строке вводится целое число N — количество элементов последовательности L ( 0 ≤ N ≤ 1000 ).
// В второй строке вводится N целых чисел — элементы последовательности L ( |Li| ≤ 32000 ).

// Формат результата
// Первую строку вывода необходимо начать с метки "L1: ", после которой выводятся элементы списка L1.
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

procedure split(L: List; var L1, L2: List);
{ Разделяет список на два }
begin
    while L <> nil do
    begin
        if L^.data > 0 then
            add(L1, L^.data)
        else
            add(L2, L^.data);
        L := L^.next;
    end;
end;

var
    L, L1, L2: List;
    n: integer;

begin
    // Заполнение списка
    read(n);
    input(L, n);

    // Инициализация списков
    L1 := nil;
    L2 := nil;

    // Разделение списка
    split(L, L1, L2);

    // Вывод результата
    write('L1: ');
    print(L1);
    writeln;
    write('L2: ');
    print(L2);
    writeln;

    // Очистка памяти
    clear(L);
    clear(L1);
    clear(L2);
end.

