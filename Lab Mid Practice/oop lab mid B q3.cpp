#include <iostream>
#include <string>

using namespace std;

// Base Class
class Vehicle {
protected:
    string registrationNumber;
    string ownerName;
    bool isTollPaid;

public:
    Vehicle(string number, string name) : registrationNumber(number), ownerName(name), isTollPaid(false) {}

    void markTollPaid() {
        isTollPaid = true;
    }

    bool checkTollStatus() const {
        return isTollPaid;
    }

    void displayDetails() const {
        cout << "Reg: " << registrationNumber << " | Owner: " << ownerName << " | Toll Status: " << (isTollPaid ? "Paid" : "Unpaid") << endl;
    }
};

// Derived Class for Car
class Car : public Vehicle {
private:
    bool isLuxury;

public:
    Car(string number, string name, bool luxury) : Vehicle(number, name), isLuxury(luxury) {}

    double calculateToll() const {
        return isLuxury ? 10 : 5;
    }
};

// Derived Class for Motorcycle
class Motorcycle : public Vehicle {
private:
    bool hasSidecar;

public:
    Motorcycle(string number, string name, bool sidecar) : Vehicle(number, name), hasSidecar(sidecar) {}

    double calculateToll() const {
        return hasSidecar ? 3 : 2;
    }
};

// TollGate Management Class
class TollGate {
private:
    Car* carRecords[10];
    Motorcycle* motoRecords[10];
    int carCount, motoCount;
    double totalRevenue;

public:
    TollGate() : carCount(0), motoCount(0), totalRevenue(0) {}

    void addCar(Car* c) {
    if (carCount < 10) { // Check if the car array has space for another record
        totalRevenue += c->calculateToll(); // Add the calculated toll for this car to the total revenue
        c->markTollPaid(); // Mark this car's toll status as 'Paid'
        carRecords[carCount++] = c; // Add the car to the carRecords array and increment the car count
    }
}
    void addMotorcycle(Motorcycle* m) {
    if (motoCount < 10) { // Check if the motorcycle array has space for another record
        totalRevenue += m->calculateToll(); // Add the calculated toll for this motorcycle to the total revenue
        m->markTollPaid(); // Mark this motorcycle's toll status as 'Paid'
        motoRecords[motoCount++] = m; // Add the motorcycle to the motoRecords array and increment the motorcycle count
    }
}

    void displayAllVehicles() const {
        cout << "Vehicle Toll Details:" << endl;
        for (int i = 0; i < carCount; i++) {
            carRecords[i]->displayDetails();
        }
        for (int i = 0; i < motoCount; i++) {
            motoRecords[i]->displayDetails();
        }
    }

    void showTotalRevenue() const {
        cout << "\nTotal Toll Revenue: $" << totalRevenue << endl;
    }
};

int main() {
    // Creating TollGate object
    TollGate gate;

    // Creating vehicle objects
    Car* car1 = new Car("CAR-101", "Abdullah Shaikh", false);   // Regular Car
    Car* car2 = new Car("CAR-202", "Abdullah Yaqoob", true);    // Luxury Car
    Motorcycle* moto1 = new Motorcycle("MOTO-404", "Mubashir", false); // Motorcycle without sidecar

    // Adding vehicles to toll gate
    gate.addCar(car1);
    gate.addCar(car2);
    gate.addMotorcycle(moto1);

    // Displaying vehicle details
    gate.displayAllVehicles();

    // Showing total revenue
    gate.showTotalRevenue();

    // Deallocating memory
    delete car1;
    delete car2;
    delete moto1;

    return 0;
}
