#include <iostream>
#include <string>

using namespace std;

// ====== Base Class: Stock ======
class Stock {
protected:
    string symbol;
    string companyName;
    double price;
    int availableQuantity;
    int maxQuantityPerInvestor;
    int stockCategoryQuantity; // ??? Fixed spelling

public:
    Stock(string s, string name, double p, int qty, int maxq, int stockq)
        : symbol(s), companyName(name), price(p), availableQuantity(qty),
          maxQuantityPerInvestor(maxq), stockCategoryQuantity(stockq) {}

    string getSymbol() const { return symbol; }
    string getCompanyName() const { return companyName; }
    double getPrice() const { return price; }
    int getAvailableQuantity() const { return availableQuantity; }
    int getMaxQuantityPerInvestor() const { return maxQuantityPerInvestor; }
    int getStockCategoryQuantity() const { return stockCategoryQuantity; }

    virtual bool isEligibleToBuy(int purchaseQuantity) const = 0;

    virtual void displayInfo() const {
        cout << "Symbol: " << symbol << endl;
        cout << "Company Name: " << companyName << endl;
        cout << "Price: " << price << endl;
        cout << "Available Quantity: " << availableQuantity << endl;
        cout << "Max Quantity Per Investor: " << maxQuantityPerInvestor << endl;
        cout << "Stock Category Quantity: " << stockCategoryQuantity << endl;
    }

    virtual ~Stock() {}
};

// ====== Derived Classes: PharmaStock and TechStock ======

class PharmaStock : public Stock {
public:
    PharmaStock(string symbol, string companyName, double price, int availableQuantity,
                int maxQuantityPerInvestor, int stockCategoryQuantity)
        : Stock(symbol, companyName, price, availableQuantity, maxQuantityPerInvestor, stockCategoryQuantity) {}

    bool isEligibleToBuy(int purchaseQuantity) const override {
        return (purchaseQuantity <= availableQuantity) &&
               (purchaseQuantity <= maxQuantityPerInvestor) &&
               (purchaseQuantity <= stockCategoryQuantity);
    }
};

class TechStock : public Stock {
public:
    TechStock(string symbol, string companyName, double price, int availableQuantity,
              int maxQuantityPerInvestor, int stockCategoryQuantity)
        : Stock(symbol, companyName, price, availableQuantity, maxQuantityPerInvestor, stockCategoryQuantity) {}

    bool isEligibleToBuy(int purchaseQuantity) const override {
        return (purchaseQuantity <= availableQuantity) &&
               (purchaseQuantity <= maxQuantityPerInvestor) &&
               (purchaseQuantity <= stockCategoryQuantity);
    }
};

// ====== Abstract Class: Investor ======

class Investor {
protected:
    string name;
    string CNIC;
    string email;
    int availableFunds;
    bool hasLoan;

public:
    Investor(string name, string CNIC, string email, int availableFunds, bool hasLoan)
        : name(name), CNIC(CNIC), email(email), availableFunds(availableFunds), hasLoan(hasLoan) {}

    string getName() const { return name; }
    string getCNIC() const { return CNIC; }
    string getEmail() const { return email; }
    int getAvailableFunds() const { return availableFunds; }
    bool getHasLoan() const { return hasLoan; }

    virtual bool canBuyStock(Stock& stock, int purchaseQuantity) = 0;
};

// ====== DayTrader ======
class DayTrader : public Investor {
public:
    DayTrader(string name, string CNIC, string email, int availableFunds, bool hasLoan)
        : Investor(name, CNIC, email, availableFunds, hasLoan) {}

    bool canBuyStock(Stock& stock, int purchaseQuantity) override {
        return stock.isEligibleToBuy(purchaseQuantity) &&
               availableFunds >= (stock.getPrice() * purchaseQuantity);
    }
};

// ====== LongTermInvestor ======
class LongTermInvestor : public Investor {
public:
    LongTermInvestor(string name, string CNIC, string email, int availableFunds, bool hasLoan)
        : Investor(name, CNIC, email, availableFunds, hasLoan) {}

    bool canBuyStock(Stock& stock, int purchaseQuantity) override {
        return stock.isEligibleToBuy(purchaseQuantity) &&
               availableFunds >= (stock.getPrice() * purchaseQuantity) &&
               !hasLoan;
    }
};

// ====== Market Class ======
class Market {
private:
    Stock* stock;
    int numStocks;

public:
    Market() : stock(nullptr), numStocks(0) {}

    void addStock(Stock* s) {
        stock = s;
        numStocks++;
    }

    void tradeStocks() {
        cout << "Trading stocks..." << endl;
    }

    int getNumStocks() const {
        return numStocks;
    }
};






