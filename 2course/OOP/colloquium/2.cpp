/*
Проинициализируйте предложенную ссылку динамически создаваемым объектом.
int &a = ...
После (с помощью delete) осовободите выделенную память
*/

int main() {
  int &a = *(new int); // создание ссылки на динамически создаваемый объект
                       // (указатель на int)

  delete &a; // освобождение памяти
}