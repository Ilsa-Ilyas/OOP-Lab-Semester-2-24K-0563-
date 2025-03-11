#include <iostream>
using namespace std;

class BankAccount {
public:
    string accountNumber;
    double balance;

    BankAccount(string accNum, double balance) : accountNumber(accNum), balance(balance) {}

    void deposit(double value) {
        balance += value;
    }

    void withdraw(double value) {
        balance -= value;
    }

    double getBalance() {
        return balance;
    }
};

class SavingsAccount : public BankAccount {
public:
    double monthlyInterest;

    SavingsAccount(string accNum, double balance, double monthlyInterest) 
        : BankAccount(accNum, balance), monthlyInterest(monthlyInterest) {}

    void applyMonthlyInterest() {
        double interest = balance * monthlyInterest;
        balance += interest;
        cout << "Monthly interest applied. New balance: " << balance << endl;
    }
};

class CheckingAccount : public BankAccount {
public:
    double overdraftLimit;

    CheckingAccount(string accNum, double balance, double overdraftLimit) 
        : BankAccount(accNum, balance), overdraftLimit(overdraftLimit) {}

    void withdraw(double value) {
        if (balance - value < -overdraftLimit) {
            cout << "Alert: Overdraft limit exceeded. Withdrawal denied!" << endl;
        } else {
            balance -= value;
            cout << "Withdrawal successful. New balance: " << balance << endl;
        }
    }

    void setOverdraftLimit(double limit) {
        overdraftLimit = limit;
    }

    double getOverdraftLimit() const {
        return overdraftLimit;
    }
};

class BusinessAccount : public BankAccount {
public:
    double corporateTax;

    BusinessAccount(string accNum, double balance, double corporateTax)
        : BankAccount(accNum, balance), corporateTax(corporateTax) {}

    void deposit(double value) {
        double tax = value * corporateTax;
        value -= tax;
        balance += value;
        cout << "Deposit after tax deduction. New balance: " << balance << endl;
    }
};

class Customer {
public:
    void deposit(BankAccount& account, double value) {
        account.deposit(value);
        cout << "Customer deposited: " << value << ". New balance: " << account.getBalance() << endl;
    }

    void withdraw(BankAccount& account, double value) {
        account.withdraw(value);
        cout << "Customer withdrew: " << value << ". New balance: " << account.getBalance() << endl;
    }
};

class Employee {
public:
    void freezeAccount(BankAccount& account) {
        cout << "Account " << account.accountNumber << " has been frozen." << endl;
    }
};

class Teller : public Employee {
public:
    void deposit(BankAccount& account, double value) {
        account.deposit(value);
        cout << "Teller deposited: " << value << ". New balance: " << account.getBalance() << endl;
    }

    void withdraw(BankAccount& account, double value) {
        account.withdraw(value);
        cout << "Teller withdrew: " << value << ". New balance: " << account.getBalance() << endl;
    }
};

class Manager : public Employee {
public:
    void deposit(BankAccount& account, double value) {
        account.deposit(value);
        cout << "Manager deposited: " << value << ". New balance: " << account.getBalance() << endl;
    }

    void withdraw(BankAccount& account, double value) {
        account.withdraw(value);
        cout << "Manager withdrew: " << value << ". New balance: " << account.getBalance() << endl;
    }

    void adjustOverdraftLimit(CheckingAccount& account, double newLimit) {
        account.setOverdraftLimit(newLimit);
        cout << "Manager adjusted overdraft limit to: " << newLimit << endl;
    }
};

int main() {
    SavingsAccount savings("874ABC", 1000.0, 0.05);
    savings.applyMonthlyInterest();

    CheckingAccount checking("9827IJK", 700.0, 500.0);
    checking.withdraw(600);

    BusinessAccount business("456FGJ", 2000.0, 0.05);
    business.deposit(1000);

    Customer customer;
    customer.deposit(savings, 200);
    customer.withdraw(savings, 100);

    Teller teller;
    teller.deposit(checking, 300);
    teller.withdraw(checking, 100);

    Manager manager;
    manager.adjustOverdraftLimit(checking, 300);

    return 0;
}
