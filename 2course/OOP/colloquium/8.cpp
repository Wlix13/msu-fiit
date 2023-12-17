/*
Есть ли ошибки в приведенном ниже фрагменте программы? Если да — исправить их,
не изменяя функций f, main и не определяя новых функций. Что будет выдано при
работе программы?

class cat{ double weight;
           char name[100];
public: explicit cat(const char* n, double w=10.0): weight(w){
                                    strcpy(name,n); cout << 1 <<endl; }
        cat(double w): weight (w) { strcpy(name,"cat");
                                    cout << 2 << endl; }
cat (const cat & of) { weight= of.weight;
                strcpy(name, of.name); cout << 3 << endl; }

~cat () { cout << 4 << endl;} };

int f (const cat &c1, cat c2)
{ return c1.weight+c2.weight; }
int main(){ cat r(3.4); f("Murzik", r); return 0; }
*/

/*
Будет выведено:
2 1 3 4 4 4

Ошибки:
explicit стоит перед конструктором, который должен быть вызван из-за функции f
*/
