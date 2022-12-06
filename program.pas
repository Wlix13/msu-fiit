
type
    text = file of char;

procedure Delete(var F: text);
// Описать процедуру Delete(F), удаляющую последний элемент файла F Элементами файла являются символы.
var
    F1: text;
    c: char;
begin
    reset(F);
    rewrite(F1);
    while not eof(F) do
    begin
        read(F, c);
        if not eof(F) then
            write(F1, c);
    end;
    reset(F1);
    rewrite(F);
    while not eof(F1) do
    begin
        read(F1, c);
        write(F, c);
    end;
    close(F);
    close(F1);
end;


// Привести определение типа для списка из целых чисел. Считая все числа в списке
// различными, описать процедуру, которая разбивает исходный непустой список L на
// два списка (L1, L2) по позиции его максимального элемента. В L1 попадают все
// элементы исходного списка, начиная с первого и заканчивая максимальным
// элементом, в L2 - все остальные элементы исходного списка.

type
    list = ^node;
    node = record
        data: integer;
        next: list;
    end;

procedure Split(L: list; var L1, L2: list);
var
    max: integer;
    tmp: list;
begin
    max := L^.data;
    tmp := L;
    while tmp <> nil do
    begin
        if tmp^.data > max then
            max := tmp^.data;
        tmp := tmp^.next;
    end;
    tmp := L;
    while tmp^.data <> max do
    begin
        L1 := tmp;
        tmp := tmp^.next;
    end;
    while tmp^.next <> nil do
    begin
        L2 := tmp;
        tmp := tmp^.next;
    end;
end;

// В вершинах дерева записаны целые числа. Описать рекурсивную функцию для
// проверки на равенство деревьев Т1 и Т2. Деревья считаются равными, если они
// совпадают по структуре и в соответствующих вершинах записаны одинаковые
// значения. Описать необходимые типы.

type
    tree = ^node;
    node = record
        data: integer;
        left, right: tree;
    end;

function Equal(T1, T2: tree): boolean;
begin
    if (T1 = nil) and (T2 = nil) then
        Equal := true
    else
        if (T1 <> nil) and (T2 <> nil) then
            Equal := (T1^.data = T2^.data) and Equal(T1^.left, T2^.left) and Equal(T1^.right, T2^.right)
        else
            ЕEqual := false;
end;

// Описать процедуру Add(L). которая добавляет в конец непустого списка L новый
// злемент, значение которого равно произведению первого и последнего элементов
// исходного списка. Список однонаправленный, без заглавного звена.

type
    list = ^node;
    node = record
        data: integer;
        next: list;
    end;

procedure Add(var L: list);
var
    tmp_i : integer;
begin
    tmp_i := L^.data;
    while L^.next <> nil do
        L := L^.next;
    tmp_i := tmp_i * L^.data;
    new(L^.next);
    L := L^.next;
    L^.data := tmp_i;   
end;