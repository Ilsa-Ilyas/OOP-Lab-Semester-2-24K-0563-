#include <iostream>
#include <string>
using namespace std;

class PastryReport; // forward declaration

class Pastry {
protected:
    string name;
    string ingredients;
    double productionCost;
    double salesTaxRate;
    double GST = 0.06;
    double totalCost;
    double retailPrice;
    double profit;

public:
    Pastry(string n = "", string i = "", double cost = 0.0)
        : name(n), ingredients(i), productionCost(cost), totalCost(0), retailPrice(0), profit(0) {}

    virtual void calculate() {
        // overridden in child classes
    }

    virtual void display() const {
        cout << "\nName: " << name;
        cout << "\nIngredients: " << ingredients;
        cout << "\nProduction Cost: AED " << productionCost;
        cout << "\nSales Tax: " << salesTaxRate * 100 << "%";
        cout << "\nTotal Cost: AED " << totalCost;
        cout << "\nRetail Price: AED " << retailPrice;
        cout << "\nProfit: AED " << profit << "\n";
    }

    friend void PastryCalculator(Pastry &p);
    friend class PastryReport;
};

class SweetPastry : public Pastry {
public:
    SweetPastry(string n, string i, double cost) : Pastry(n, i, cost) {
        salesTaxRate = 0.08;
    }

    void calculate() override {
        PastryCalculator(*this);
    }
};

class SavoryPastry : public Pastry {
public:
    SavoryPastry(string n, string i, double cost) : Pastry(n, i, cost) {
        salesTaxRate = 0.05;
    }

    void calculate() override {
        PastryCalculator(*this);
    }
};

// ? Friend Function (only once, no nesting!)
void PastryCalculator(Pastry &p) {
    double markup = p.productionCost * 0.10;
    double costWithMarkup = p.productionCost + markup;
    double gstAmount = costWithMarkup * p.GST;
    double salesTax = costWithMarkup * p.salesTaxRate;

    p.totalCost = costWithMarkup + gstAmount + salesTax;
    p.retailPrice = p.totalCost + markup;
    double grossProfit = p.retailPrice - p.totalCost;
    p.profit = grossProfit * 0.70;
}

class PastryReport {
public:
    void generate(Pastry* pastries[], int count) {
        double totalSales = 0, totalProfit = 0;

        cout << "\n--- Pastry Report ---\n";
        for (int i = 0; i < count; ++i) {
            pastries[i]->display();
            totalSales += pastries[i]->retailPrice;
            totalProfit += pastries[i]->profit;
        }

        cout << "\nTotal Sales: AED " << totalSales;
        cout << "\nTotal Profit Retained: AED " << totalProfit << "\n";
    }
};

class PastryShop {
private:
    Pastry* menu[10];
    int count;

public:
    PastryShop() {
        count = 0;
    }

    void AddPastry(Pastry* p) {
        if (count < 10) {
            menu[count++] = p;
        } else {
            cout << "Menu is full!\n";
        }
    }

    void calculateTotalProfit() {
        for (int i = 0; i < count; ++i) {
            menu[i]->calculate();
        }
    }

    void showReport() {
        PastryReport report;
        report.generate(menu, count);
    }

    ~PastryShop() {
        for (int i = 0; i < count; ++i) {
            delete menu[i];
        }
    }
};