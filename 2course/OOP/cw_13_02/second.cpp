/*
Опишите класс В1 (стек из целых чисел) и класс В2 (очередь из целых чисел) так,
чтобы предлагаемый ниже фрагмент программы работал верно.
# include <iostream>
using namespace std;
main () { int a [4]= {1,2,3,4}, n, k;
          B1 st1(4, a), st2(2);
создаем стек st1 с максимальной длиной 4 и значениями 1,2,3,4 и стек st2 с
максимальной длиной 2

B2 obj1 (3);
создаем очередь о1 с максимальной длиной 3

F(st1, 6); заносим в стек число 6, стек не меняется, сообщение, что стек
переполнен
F(st2, 7); // заносим в стек число 7
F (st2, 8); // заносим в стек число 8
n=G(st1); // берем из стека число
F (st1, 5); // заносим в стек число 5
F(obj1,2); // заносим в очередь число 2
F(obj1,7); // заносим в очередь число 7
k=G(obj1); // берем из очереди число
F(obj1,9); // заносим в очередь число 9
st1.PR(); // печатаем стек1
st2.PR(); // печатаем стек2
obj1.PR(); // печатаем очередь
cout << n << ',' << k << endl;
return 0;
}
*/

#include <iostream>

using namespace std;

class B1 {
public:
  int *st;
  int maxSize;
  int top;

  B1(int size, int a[]) {
    maxSize = size;
    st = new int[maxSize];
    for (int i = 0; i < size; i++) {
      st[i] = a[i];
    }
    top = size - 1;
  }

  B1(int size) {
    maxSize = size;
    st = new int[maxSize];
    top = -1;
  }

  void PR() {
    for (int i = top; i >= 0; i--) {
      cout << st[i] << " ";
    }
    cout << endl;
  }
};

class B2 {
public:
  int *q;
  int maxSize;
  int front, rear;

  B2(int size) {
    maxSize = size;
    q = new int[maxSize];
    front = 0;
    rear = -1;
  }

  void PR() {
    for (int i = front; i <= rear; i++) {
      cout << q[i] << " ";
    }
    cout << endl;
  }
};

void F(B1 &obj, int val) {
  if (obj.top < obj.maxSize - 1) {
    obj.st[++obj.top] = val;
  } else {
    cout << "Stack is full" << endl;
  }
}

void F(B2 &obj, int val) {
  if (obj.rear < obj.maxSize - 1) {
    obj.q[++obj.rear] = val;
  } else {
    cout << "Queue is full" << endl;
  }
}

int G(B1 &obj) {
  if (obj.top >= 0) {
    return obj.st[obj.top--];
  } else {
    cout << "Stack is empty" << endl;
    return -1;
  }
}

int G(B2 &obj) {
  if (obj.rear >= obj.front) {
    return obj.q[obj.front++];
  } else {
    cout << "Queue is empty" << endl;
    return -1;
  }
}

int main() {
  int a[4] = {1, 2, 3, 4}, n, k;
  B1 st1(4, a), st2(2);
  B2 obj1(3);

  F(st1, 6);                     // Stack is full
  F(st2, 7);                     // 7,
  F(st2, 8);                     // 8, 7,
  n = G(st1);                    // 4
  F(st1, 5);                     // 5, 3, 2, 1,
  F(obj1, 2);                    // 2,
  F(obj1, 7);                    // 2, 7,
  k = G(obj1);                   // 2
  F(obj1, 9);                    // 7, 9,
  st1.PR();                      // 5 3 2 1
  st2.PR();                      // 8 7
  obj1.PR();                     // 7 9
  cout << n << ',' << k << endl; // 4, 
  return 0;
}