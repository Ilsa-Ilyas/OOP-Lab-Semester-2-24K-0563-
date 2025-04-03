#include<iostream>
#include<string>
using namespace std;

// Base class for all account types
class Account {
protected:
    string holderName;
    int accNumber;
    double accBalance;
    string accType;
    static int totalAccounts; // Keeps track of all accounts created

public:
    // Constructor initializes name, number, and type. Balance starts at 0
    Account(string name, int number, string type) : holderName(name), accNumber(number), accType(type), accBalance(0) {
        totalAccounts++;
    }

    // Deposit money into account
    void depositFunds(double amount) {
        accBalance += amount;
        cout << "Balance after deposit: " << accBalance << endl;
    }

    // Get current balance
    double getBalance() {
        return accBalance;
    }

    // Withdraw funds - base logic (can be overridden)
    virtual void withdrawFunds(double amount) {
        if (accBalance >= amount) {
            accBalance -= amount;
            cout << "Balance after withdrawal: " << accBalance << endl;
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    // Print current statement
    virtual void printStatement() {
        cout << "Current balance for Account " << accNumber << " is: " << accBalance << endl;
    }

    // Display account info
    virtual void displayAccountInfo() {
        cout << "Account Details:" << endl;
        cout << "Holder Name: " << holderName << endl;
        cout << "Account Number: " << accNumber << endl;
        cout << "Account Type: " << accType << endl;
    }

    // Base interest calculation - overridden in derived classes
    virtual double computeInterest() {
        return 0.0;
    }

    // Returns total accounts created
    static int getTotalAccountCount() {
        return totalAccounts;
    }
};

int Account::totalAccounts = 0;

// SavingsAccount subclass
class SavingsAccount : public Account {
    double rateOfInterest;
    double minRequiredBalance;

public:
    SavingsAccount(string name, int number, string type, double rate, double minBal)
        : Account(name, number, type), rateOfInterest(rate), minRequiredBalance(minBal) {}

    // Additional info display for savings account
    void displayAccountInfo() override {
        Account::displayAccountInfo();
        cout << "Interest Rate: " << rateOfInterest << endl;
        cout << "Minimum Required Balance: " << minRequiredBalance << endl;
    }

    // Override withdrawal to enforce minimum balance rule
    void withdrawFunds(double amount) override {
        if (accBalance - amount >= minRequiredBalance) {
            accBalance -= amount;
            cout << "Balance after withdrawal: " << accBalance << endl;
        } else {
            cout << "Withdrawal denied. Minimum balance requirement not met!" << endl;
        }
    }

    // Calculate interest for savings account
    double computeInterest() override {
        return accBalance * rateOfInterest;
    }
};

// CheckingAccount subclass
class CheckingAccount : public Account {
public:
    CheckingAccount(string name, int number, string type) : Account(name, number, type) {}

    // Withdrawal logic for checking (no overdraft)
    void withdrawFunds(double amount) override {
        if (accBalance >= amount) {
            accBalance -= amount;
            cout << "Balance after withdrawal: " << accBalance << endl;
        } else {
            cout << "Insufficient balance! Overdraft not allowed." << endl;
        }
    }
};

// FixedDepositAccount subclass
class FixedDepositAccount : public Account {
    string maturityDate;
    double fixedRate;

public:
    FixedDepositAccount(string name, int number, string type, string mDate, double rate)
        : Account(name, number, type), maturityDate(mDate), fixedRate(rate) {}

    // Display extra fixed deposit info
    void displayAccountInfo() override {
        Account::displayAccountInfo();
        cout << "Maturity Date: " << maturityDate << endl;
        cout << "Fixed Interest Rate: " << fixedRate << endl;
    }

    // Withdrawal restricted before maturity
    void withdrawFunds(double amount) override {
        cout << "Withdrawal not allowed before maturity date!" << endl;
    }

    // Interest computation for fixed deposit
    double computeInterest() override {
        return accBalance * fixedRate;
    }
};

int main() {
    // Create accounts
    SavingsAccount sAcc("Jane", 101, "Savings", 0.05, 500);
    CheckingAccount cAcc("KAKA", 102, "Checking");
    FixedDepositAccount fAcc("Binn", 103, "Fixed Deposit", "2025-12-31", 0.08);

    // Store them in base class pointers for polymorphism
    Account* accountList[] = { &sAcc, &cAcc, &fAcc };

    cout << "\n=== Depositing money ===\n";
    for (Account* acc : accountList) {
        acc->depositFunds(2000);
    }

    cout << "\n=== Withdrawing money ===\n";
    accountList[0]->withdrawFunds(1000);  // Savings: Should succeed
    accountList[1]->withdrawFunds(2500);  // Checking: Should fail
    accountList[2]->withdrawFunds(500);   // FixedDeposit: Not allowed

    cout << "\n=== Calculating interest ===\n";
    for (Account* acc : accountList) {
        cout << "Interest on balance " << acc->getBalance() << ": "
             << acc->computeInterest() << endl;
    }

    cout << "\n=== Account Information ===\n";
    for (Account* acc : accountList) {
        acc->displayAccountInfo();
        acc->printStatement();
        cout << "-----------------------\n";
    }

    cout << "\nTotal accounts created: " << Account::getTotalAccountCount() << endl;

    return 0;
}
