#include <iostream>
#include <string>

using namespace std;

class Wallet
{
private:
    double balance;
    double dailyDepositLimit;
    double dailyWithdrawalLimit;
    double depositedToday;
    double withdrawnToday;

public:
    Wallet(double depositLimit = 1000.0, double withdrawLimit = 500.0)
        : balance(0.0), dailyDepositLimit(depositLimit), dailyWithdrawalLimit(withdrawLimit), depositedToday(0.0), withdrawnToday(0.0) {}

    bool deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid deposit amount.\n";
            return false;
        }
        if (depositedToday + amount > dailyDepositLimit)
        {
            cout << "Deposit exceeds daily limit.\n";
            return false;
        }
        balance += amount;
        depositedToday += amount;
        return true;
    }
    bool withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid withdrawal amount.\n";
            return false;
        }
        if (amount > balance)
        {
            cout << "Insufficient balance.\n";
            return false;
        }
        if (withdrawnToday + amount > dailyWithdrawalLimit)
        {
            cout << "Withdrawal exceeds daily limit.\n";
            return false;
        }
        balance -= amount;
        withdrawnToday += amount;
        return true;
    }

    double getBalance() const
    {
        return balance;
    }

    void resetDailyLimits()
    {
        depositedToday = 0.0;
        withdrawnToday = 0.0;
    }
};

class User {
private:
    string userID;
    string name;
    Wallet wallet;

public:
    User(string id, string username) : userID(id), name(username) {}

    bool deposit(double amount) {
        return wallet.deposit(amount);
    }

    bool withdraw(double amount) {
        return wallet.withdraw(amount);
    }

    void checkBalance() const {
        cout << "User: " << name << " | Balance: $" << wallet.getBalance() << endl;
    }

    void resetLimits() {
        wallet.resetDailyLimits();
    }
};

int main()
{
    User ali("101", "Ali");
    User sara("102", "Sara");

    cout << "== Ali's Transactions ==\n";
    ali.deposit(500);  
    ali.deposit(600);  
    ali.withdraw(200); 
    ali.withdraw(400); 
    ali.checkBalance();

    ali.resetLimits();
    cout << "\n-- Next Day for Ali --\n";
    ali.deposit(700);  
    ali.withdraw(300); 
    ali.checkBalance();

    cout << "\n== Sara's Transactions ==\n";
    sara.deposit(1000); 
    sara.withdraw(100); 
    sara.checkBalance();

    return 0;
}