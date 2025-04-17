#include <iostream>
#include <string>

using namespace std;

class Car {
protected:
    string model;
    double price;

public:
    Car(string m) {
        model = m;
        price = 0.0;
    }

    string getModel() {
        return model;
    }

    double getPrice() {
        return price;
    }

    void setModel(string m) {
        model = m;
    }

    virtual void setPrice(double p) = 0;

    virtual ~Car() {}
};

class Color : public Car {
private:
    string color;
public:
    Color(string m, string c) : Car(m) {
        color = c;
    }

    void setPrice(double p) override {
        price = p + 1000.0;
    }

    void display() {
        cout << "Model: " << model << ", Color: " << color << ", Price: $" << price << endl;
    }
};

class Company : public Car {
private:
    string companyName;
public:
    Company(string m, string company) : Car(m) {
        companyName = company;
    }

    void setPrice(double p) override {
        price = p + 2000.0;
    }

    void display() {
        cout << "Model: " << model << ", Company: " << companyName << ", Price: $" << price << endl;
    }
};

int main() {
    Color colorCar("Elantra", "Black");
    colorCar.setPrice(15000);
    colorCar.display();

    Company companyCar("SUV", "Toyota");
    companyCar.setPrice(18000);
    companyCar.display();

    return 0;
}
