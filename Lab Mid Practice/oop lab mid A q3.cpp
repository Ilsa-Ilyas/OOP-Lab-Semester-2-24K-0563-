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
    // Constructor
    Vehicle(string number, string name) : registrationNumber(number), ownerName(name), isTollPaid(false) {}

    // Mark toll as paid
    void markTollPaid() {
        isTollPaid = true;
    }

    // Check toll status
    bool checkTollStatus() const {
        return isTollPaid;
    }

    // Display vehicle details
    void displaydetails() const {
        cout << "Registration Number: " << registrationNumber << endl;
        cout << "Owner's Name: " << ownerName << endl;
        cout << "Toll Status: " << (isTollPaid ? "Paid" : "Unpaid") << endl;
    }
};

// Derived Class for Bus
class Bus : public Vehicle {
private:
    int passengerCount;

public:
    Bus(string number, string name, int count) : Vehicle(number, name), passengerCount(count) {}

    double calculateToll() {
        return 10 + (0.5 * passengerCount);
    }
};

// Derived Class for Van
class Van : public Vehicle {
private:
    double cargoWeight;

public:
    Van(string number, string name, double weight) : Vehicle(number, name), cargoWeight(weight) {}

    double calculateToll() {
        return 8 + (0.3 * cargoWeight);
    }
};

// TollGate Management Class
class TollGate {
private:
    Bus* busRecords[10];
    Van* vanRecords[10];
    int busCount, vanCount;
    double totalRevenue;

public:
    TollGate() : busCount(0), vanCount(0), totalRevenue(0) {}

    void addBus(Bus* b) {
        if (busCount < 10) {
            totalRevenue += b->calculateToll();
            b->markTollPaid();
            busRecords[busCount++] = b;
        }
    }

    void addVan(Van* v) {
        if (vanCount < 10) {
            totalRevenue += v->calculateToll();
            v->markTollPaid();
            vanRecords[vanCount++] = v;
        }
    }

    void displayAllVehicles() const {
        cout << "Vehicle Toll Details" << endl;
        for (int i = 0; i < busCount; i++) {
            busRecords[i]->displaydetails();
        }
        for (int i = 0; i < vanCount; i++) {
            vanRecords[i]->displaydetails();
        }
    }

    void showTollRateRevenue() const {
        cout << "Total Toll Revenue: $" << totalRevenue << endl;
    }
};

int main() {
    // Creating TollGate object
    TollGate gate;

    // Creating vehicle objects
    Bus* b1 = new Bus("BUS-101", "Alice", 20);
    Van* v1 = new Van("VAN-202", "Bob", 500);
    Bus* b2 = new Bus("BUS-404", "Charlie", 10);

    // Adding vehicles to toll gate
    gate.addBus(b1);
    gate.addVan(v1);
    gate.addBus(b2);

    // Displaying details
    gate.displayAllVehicles();

    // Showing total revenue
    gate.showTollRateRevenue();

    // Deallocating memory
    delete b1;
    delete v1;
    delete b2;

    return 0;
}
