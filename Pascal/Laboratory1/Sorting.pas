program Lab_sorting;

const
  ARRAY_SIZE = 1000;

type
  TArray = array[0..ARRAY_SIZE] of integer;
  Tuple = record
    comparisons: integer;
    permutations: integer;
  end;


var
  arr, shell_arr, select_arr: TArray;
  shell, select: Tuple;
  N: integer;

procedure generate_array(var arr: TArray; N: integer; order: char);
{ 
  Заполнить массив случайными числами
  `order` отвечает за вид расстановки элементов массива:
    A - неубывающий
    D - невозрастающий
}
var
  i: integer;
begin
  Randomize;
  case order of
    'A', 'a': // Ascending order
      begin
        arr[0] := Random(10);
        for i := 1 to N - 1 do
          arr[i] := arr[i-1] + Random(10) + 1;
      end;
    'D', 'd': // Descending order
      begin
        arr[0] := Random(10) + 10*(n-1);
        for i := 1 to N - 1 do
          arr[i] := arr[i-1] - Random(10) - 1;
      end;
    else // Random 
      for i := 0 to N - 1 do
        arr[i] := Random(100);
  end;
end;

procedure copy_copy(var init, copy_a, copy_b: TArray; N: integer);
{ Делает копии массива init в переменные copy_a и copy_b }
var
  i:integer;

begin
  for i:=0 to N - 1 do
    begin
      copy_a[i] := init[i];
      copy_b[i] := init[i];
    end;
end;

procedure print_array(arr: TArray; N: integer);
{ Выводит массив на экран }
var
  i: integer;
begin
  for i := 0 to N-1 do
    write(arr[i], ' ');
  writeln;
end;

procedure ShellSort(var arr: TArray; N: integer; var stats: Tuple);
{ Процедура сортировки Шелла }
var
  i, j, gap, temp: integer;
begin
  // Установить начальный промежуток равный половине массива
  gap := N div 2;
  
  // Повторять, пока промежуток не станет нелевым
  while gap > 0 do
  begin
    // Iterate over the array from gap to N
    // Итерируем по массиву, начиная с промежутка с промежутка 
    for i := gap to N - 1 do
    begin
      // Сравнить элементы, находящиеся на расстоянии друг от друга, и при необходимости поменять их местами
      j := i;
      while (j >= gap) and (arr[j - gap] > arr[j]) do
      begin
        // Поменять элементы местами
        temp := arr[j];
        arr[j] := arr[j - gap];
        arr[j - gap] := temp;
        
        // Увеличение числа перестановок
        stats.permutations := stats.permutations + 1;
        
        // Переход к следующим элементам
        j := j - gap;
      end;
      
      // Увеличение числа сравнений
      stats.comparisons := stats.comparisons + 1;
    end;
    
    // Сократить промежуток
    gap := gap div 2;
  end;
end;

procedure SelectionSort(var arr: TArray; N: integer; var stats: Tuple);
var
  i, j, min_idx, temp: integer;
begin
  for i := 0 to N - 1 do
  begin
    min_idx := i;

    // Найти минимальный элемент в несортированной части массива
    for j := i + 1 to N - 1 do
    begin
      // Увеличить счетчик сравнения
      stats.comparisons := stats.comparisons + 1;

      if arr[j] < arr[min_idx] then
        min_idx := j;
    end;
    
    // Поменять местами минимальный элемент с первым элементом несортированной части
    if min_idx <> i then
    begin
      temp := arr[i];
      arr[i] := arr[min_idx];
      arr[min_idx] := temp;

      // Увеличить счетчик перестановок
      stats.permutations := stats.permutations + 1; 
    end;
  end;
end;


begin
  // Ввод размера массива
  readln(N);

  // Запуск генератора случайных чисел
  randomize;

  // Сгенерировать массив случайных целых чисел по неубыванию
  generate_array(arr, N, 'D');

  // Сделать копии исходного массива для проверки алгоритмов
  copy_copy(arr, shell_arr, select_arr, N);

  // Выведите исходный массив
  write('Исходный массив: ');
  print_array(arr, N);
  writeln;

  // Отсортировать массив, используя ShellSort алгоритм
  ShellSort(shell_arr, N, shell);

  // Выведите сортированный ShellSort массив
  write('ShellSort массив: ');
  print_array(shell_arr, N);

  // Вывести количество сравнений и перестановок при ShellSort сортировке
  write('Сравнений в ShellSort: ', shell.comparisons);
  writeln;
  write('Перестановок в ShellSort: ', shell.permutations);
  writeln;
  writeln;

  // Отсортировать массив, используя SelectionSort алгоритм
  SelectionSort(select_arr, N, select);

  // Выведите сортированный SelectionSort массив
  write('SelectionSort массив: ');
  print_array(select_arr, N);

  // Вывести количество сравнений и перестановок при SelectionSort сортировке
  write('Сравнений в SelectionSort: ', select.comparisons);
  writeln;
  write('Перестановок в SelectionSort: ', select.permutations);
  writeln;
end.