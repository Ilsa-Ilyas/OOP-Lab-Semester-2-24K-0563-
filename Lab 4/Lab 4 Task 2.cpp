#include <iostream>
#include <cstdlib> 
using namespace std;

class Account {
private:
    double balance;

public:
    Account(double initialBalance) {
        if (initialBalance >= 0)
            balance = initialBalance;
        else {
            balance = 0;
            cout << "Initial balance invalid. Setting balance to 0." << endl;
        }
    }

    void credit(double amount) {
        if (amount > 0)
            balance += amount;
        else
            cout << "Invalid deposit amount." << endl;
    }

    void debit(double amount) {
        if (amount > 0 && amount <= balance)
            balance -= amount;
        else
            cout << "Invalid withdrawal amount or insufficient balance." << endl;
    }

    double getBalance() {
        return balance;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Error: Too few arguments." << endl;
        return 1;
    }

    double initialBalance = atof(argv[1]);
    double creditAmount = atof(argv[2]);
    double debitAmount = atof(argv[3]);

    Account myAccount(initialBalance);
    myAccount.credit(creditAmount);
    myAccount.debit(debitAmount);

    cout << "Final Account Balance: " << myAccount.getBalance() << endl;
    return 0;
}