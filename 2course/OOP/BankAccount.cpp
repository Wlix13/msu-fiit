#include <iostream>
#include <string>

using namespace std;

namespace Banking {

// Класс для представления владельца счета
class AccountOwner {
public:
  string firstName;
  string lastName;

  AccountOwner(string firstName, string lastName)
      : firstName(firstName), lastName(lastName) {}
};

// Класс для представления операции со счетом
class AccountOperation {
public:
  string date;
  string type; // "deposit" или "withdraw"
  double amount;

  AccountOperation(string date, string type, double amount)
      : date(date), type(type), amount(amount) {}
};

// Класс для представления банковского счета
class BankAccount {
private:
  string creationDate;
  double balance;
  AccountOwner owner;
  AccountOperation *lastOperation;

public:
  BankAccount(string creationDate, double initialBalance, AccountOwner owner)
      : creationDate(creationDate), balance(initialBalance), owner(owner),
        lastOperation(nullptr) {}

  // Метод для пополнения счета
  void deposit(double amount, string date) {
    balance += amount;
    lastOperation = new AccountOperation(date, "deposit", amount);
  }

  // Метод для снятия денег со счета
  void withdraw(double amount, string date) {
    if (amount > balance) {
      cout << "Ошибка: недостаточно средств на счете." << endl;
      return;
    }
    balance -= amount;
    lastOperation = new AccountOperation(date, "withdraw", amount);
  }

  // Метод для печати информации о последней операции
  void printLastOperation() const {
    if (lastOperation != nullptr) {
      cout << "Дата: " << lastOperation->date
           << ", Тип: " << lastOperation->type
           << ", Сумма: " << lastOperation->amount << endl;
    }
  }

  // Метод для печати доступной суммы денег на счете
  void printBalance() const { cout << "Текущий баланс: " << balance << endl; }
};
} // namespace Banking

using namespace Banking;

int main() {
  AccountOwner owner("Иван", "Иванов");
  BankAccount account("2023-11-14", 1000, owner);

  account.deposit(500, "2023-11-15");
  account.printBalance();
  account.printLastOperation();

  account.withdraw(200, "2023-11-16");
  account.printBalance();
  account.printLastOperation();

  return 0;
}
