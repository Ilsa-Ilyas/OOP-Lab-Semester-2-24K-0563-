#include <iostream>
#include <string>

using namespace std;

class Vehicle {
protected:
    double price;

public:
    Vehicle(double p) : price(p) {}

    void displayPrice() {
        cout << "The price of the vehicle is: $" << price << endl;
    }
};

class Car : public Vehicle {
private:
    int capacity;
    int numofdoors;
    string fueltype;

public:
    Car(double price, int c, int num, string type)
        : Vehicle(price), capacity(c), numofdoors(num), fueltype(type) {}

    void displayDetails() {
        cout << "Capacity: " << capacity << endl;
        cout << "Number of doors: " << numofdoors << endl;
        cout << "Type of fuel: " << fueltype << endl;
        displayPrice();
    }
};

class Motorcycle : public Vehicle {
private:
    int numofcylinders;
    int numofgears;
    int numofwheels;

public:
    Motorcycle(double price, int nc, int ng, int nw)
        : Vehicle(price), numofcylinders(nc), numofgears(ng), numofwheels(nw) {}

    void displayDetails() {
        cout << "Number of Cylinders: " << numofcylinders << endl;
        cout << "Number of Gears: " << numofgears << endl;
        cout << "Number of Wheels: " << numofwheels << endl;
        displayPrice();
    }
};

class Audi : public Car {
private:
    string modelType;

public:
    Audi(double price, int capacity, int doors, string fuel, string model)
        : Car(price, capacity, doors, fuel), modelType(model) {}

    void displayAudiDetails() {
        displayDetails();
        cout << "Model Type: " << modelType << endl;
    }
};

class Yamaha : public Motorcycle {
private:
    string makeType;

public:
    Yamaha(double price, int cylinders, int gears, int wheels, string make)
        : Motorcycle(price, cylinders, gears, wheels), makeType(make) {}

    void displayYamahaDetails() {
        displayDetails();
        cout << "Make Type: " << makeType << endl;
    }
};

int main() {
    Audi audiCar(55000, 5, 4, "Petrol", "A4");

    Yamaha yamahaMotorcycle(15000, 2, 6, 2, "Sports");

    cout << "Audi Car Details:" << endl;
    audiCar.displayAudiDetails();
    cout << endl;

    cout << "Yamaha Motorcycle Details:" << endl;
    yamahaMotorcycle.displayYamahaDetails();

    return 0;
}
