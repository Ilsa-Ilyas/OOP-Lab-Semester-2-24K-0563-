#include<iostream>
#include<string>
using namespace std;

// Base class representing a general currency
class Currency {
protected:
    double currAmount;        // amount in currency
    string code;              // currency code e.g., USD
    char symbol;              // currency symbol e.g., $
    double rateToBase;        // exchange rate to base (USD assumed)

public:
    // Constructor to initialize currency
    Currency(double amt, string currCode, char currSymbol, double rate)
        : currAmount(amt), code(currCode), symbol(currSymbol), rateToBase(rate) {}

    // Converts this currency to base (e.g., USD equivalent)
    virtual void convertToBase() {
        currAmount = currAmount * rateToBase;
    }

    // Displays currency info
    virtual void displayCurrency() {
        cout << symbol << currAmount << " (" << code << ")" << endl;
    }

    // Converts this currency to a target currency
    void convertToTargetCurrency(Currency& target) {
        double baseValue = currAmount * rateToBase;         // Convert to base
        currAmount = baseValue / target.rateToBase;         // Then convert to target
        code = target.code;
        symbol = target.symbol;
        rateToBase = target.rateToBase;
    }
};

// Dollar class
class Dollar : public Currency {
public:
    Dollar(double amt) : Currency(amt, "USD", '$', 1.0) {}
};

// Euro class
class Euro : public Currency {
public:
    Euro(double amt) : Currency(amt, "EUR", '€', 0.93) {}
};

// Rupee class
class Rupee : public Currency {
public:
    Rupee(double amt) : Currency(amt, "INR", '₹', 82.0) {}
};

int main() {
    // Create currency objects with initial amounts
    Dollar usd(100.0);
    Euro eur(100.0);
    Rupee inr(100.0);

    cout << "=== Original Amounts ===" << endl;
    usd.displayCurrency();
    eur.displayCurrency();
    inr.displayCurrency();

    // Convert USD to EUR
    cout << "\nConverting USD to EUR:" << endl;
    usd.convertToTargetCurrency(eur);
    usd.displayCurrency();

    // Convert EUR to INR
    cout << "\nConverting EUR to INR:" << endl;
    eur.convertToTargetCurrency(inr);
    eur.displayCurrency();

    // Convert INR to USD
    cout << "\nConverting INR to USD:" << endl;
    inr.convertToTargetCurrency(usd);
    inr.displayCurrency();

    return 0;
}
