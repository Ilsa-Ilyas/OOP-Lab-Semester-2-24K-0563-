#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ------------------------ BASE CLASS ------------------------
class Vehicle {
protected:
    string VehicleID;
    float speed;
    float energyLevel;

public:
    // Constructor
    Vehicle(string id, float s, float e) : VehicleID(id), speed(s), energyLevel(e) {}

    virtual ~Vehicle() {}

    // Virtual accessors
    virtual string getID() const { return VehicleID; }
    virtual float getMaxSpeed() const { return speed; }
    virtual float getEnergyLevel() const { return energyLevel; }

    // Display function to be overridden if needed
    virtual void display() const {
        cout << VehicleID << " | Speed: " << speed << " | Energy: " << energyLevel;
    }
};

// ------------------------ DERIVED CLASSES ------------------------

// DeliveryVan adds cargo capacity
class DeliveryVan : public Vehicle {
private:
    float cargoCapacity;

public:
    DeliveryVan(string id, float speed, float energy, float capacity)
        : Vehicle(id, speed, energy), cargoCapacity(capacity) {}

    float getEnergyLevel() const override { return energyLevel; }
    float getCargoCapacity() const { return cargoCapacity; }
};

// PassengerCar adds number of seats
class PassengerCar : public Vehicle {
protected:
    int numberOfSeats;

public:
    PassengerCar(string id, float speed, float energy, int seats)
        : Vehicle(id, speed, energy), numberOfSeats(seats) {}

    float getEnergyLevel() const override { return energyLevel; }
    int getNumSeats() const { return numberOfSeats; }
};

// AutonomousDrone adds max altitude
class AutonomousDrone : public Vehicle {
protected:
    float maxAlt;

public:
    AutonomousDrone(string id, float speed, float energy, float alt)
        : Vehicle(id, speed, energy), maxAlt(alt) {}

    float getEnergyLevel() const override { return energyLevel; }
    float getAlt() const { return maxAlt; }
};

// ------------------------ PERMISSION VALIDATOR ------------------------

class Permission {
private:
    string requiredPermissions[5];
    int numRequired;

public:
    Permission(string perms[], int count) {
        numRequired = count;
        for (int i = 0; i < count; ++i) {
            requiredPermissions[i] = perms[i];
        }
    }

    bool hasPermissions(string userCredentials[], int userCount) const {
        for (int i = 0; i < numRequired; ++i) {
            bool found = false;
            for (int j = 0; j < userCount; ++j) {
                if (requiredPermissions[i] == userCredentials[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    }
};

// ------------------------ EXTENDED CLASSES ------------------------

// ElectricDeliveryVan tracks battery instead of fuel
class ElectricDeliveryVan : public DeliveryVan {
private:
    float batteryLevel;

public:
    ElectricDeliveryVan(string id, float speed, float battery, float capacity)
        : DeliveryVan(id, speed, battery, capacity), batteryLevel(battery) {}

    float getEnergyLevel() const override { return batteryLevel; }

    void consumeBattery(float amount) {
        batteryLevel -= amount;
        if (batteryLevel < 0) batteryLevel = 0;
    }
};

// HybridPassengerCar can switch modes between fuel and electric
class HybridPassengerCar : public PassengerCar {
private:
    float fuelLevel;
    float batteryLevel;
    string mode;

public:
    HybridPassengerCar(string id, float speed, float fuel, float battery, int seats, string initialMode)
        : PassengerCar(id, speed, 0.0, seats), fuelLevel(fuel), batteryLevel(battery), mode(initialMode) {
        if (initialMode == "fuel") energyLevel = fuelLevel;
        else if (initialMode == "electric") energyLevel = batteryLevel;
        else {
            cout << "Invalid mode, defaulting to fuel.\n";
            mode = "fuel";
            energyLevel = fuelLevel;
        }
    }

    void switchMode(string newMode) {
        if (newMode == "fuel") {
            mode = "fuel";
            energyLevel = fuelLevel;
        } else if (newMode == "electric") {
            mode = "electric";
            energyLevel = batteryLevel;
        } else {
            cout << "Invalid mode.\n";
        }
    }

    string getMode() const { return mode; }

    float getEnergyLevel() const override {
        return (mode == "fuel") ? fuelLevel : batteryLevel;
    }

    void consumeEnergy(float amount) {
        if (mode == "fuel") {
            fuelLevel -= amount;
            if (fuelLevel < 0) fuelLevel = 0;
            energyLevel = fuelLevel;
        } else {
            batteryLevel -= amount;
            if (batteryLevel < 0) batteryLevel = 0;
            energyLevel = batteryLevel;
        }
    }
};

// ------------------------ MANAGER CLASS ------------------------

class Manager {
private:
    Vehicle* vehicles[10];
    string vehicleIDs[10];
    Permission* permissions[10];
    int count;

public:
    Manager() : count(0) {
        for (int i = 0; i < 10; ++i) {
            vehicles[i] = nullptr;
            permissions[i] = nullptr;
            vehicleIDs[i] = "";
        }
    }

    void addVehicle(Vehicle* v, Permission* p = nullptr) {
        if (count < 10) {
            vehicles[count] = v;
            permissions[count] = p;
            vehicleIDs[count] = v->getID();
            count++;
        } else {
            cout << "Fleet is full.\n";
        }
    }

    void displayDetails() const {
        for (int i = 0; i < count; ++i) {
            cout << "Vehicle " << (i + 1) << ": ";
            vehicles[i]->display();
            cout << endl;
        }
    }

    void saveToFile() {
        ofstream file("fleet.txt");
        if (!file) throw "Could not open fleet.txt for writing.";

        for (int i = 0; i < count; ++i) {
            file << vehicles[i]->getID() << " "
                 << vehicles[i]->getMaxSpeed() << " "
                 << vehicles[i]->getEnergyLevel() << endl;
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file("fleet.txt");
        if (!file) throw "fleet.txt not found.";

        string id;
        float speed, energy;

        while (file >> id >> speed >> energy) {
            for (int i = 0; i < count; ++i) {
                if (vehicleIDs[i] == id) throw "Duplicate vehicle ID.";
            }

            if (count >= 10) throw "Fleet is full.";

            // Dummy loading logic
            Vehicle* v = new Vehicle(id, speed, energy);
            vehicles[count] = v;
            vehicleIDs[count] = id;
            count++;
        }
        file.close();
    }

    float getAverageEnergyLevel() const {
        float sum = 0;
        for (int i = 0; i < count; ++i) {
            sum += vehicles[i]->getEnergyLevel();
        }
        return (count > 0) ? sum / count : 0;
    }

    void checkAccess(int index, string userPerms[], int userCount) const {
        if (index < 0 || index >= count) {
            cout << "Invalid vehicle index.\n";
            return;
        }

        if (permissions[index] == nullptr) {
            cout << "No permission required. Access granted.\n";
        } else if (permissions[index]->hasPermissions(userPerms, userCount)) {
            cout << "Access granted.\n";
        } else {
            cout << "Access denied.\n";
        }
    }
};

// ------------------------ MAIN FUNCTION ------------------------

int main() {
    Manager fleetManager;

    // Permissions
    string dronePerms[] = {"airspace_license"};
    string vanPerms[] = {"heavy_duty"};

    Permission* dronePermission = new Permission(dronePerms, 1);
    Permission* vanPermission = new Permission(vanPerms, 1);

    // Vehicles
    Vehicle* van = new DeliveryVan("V001", 80, 60, 500);
    Vehicle* car = new PassengerCar("C001", 100, 50, 4);
    Vehicle* drone = new AutonomousDrone("D001", 120, 40, 1000);

    // Add to manager
    fleetManager.addVehicle(van, vanPermission);
    fleetManager.addVehicle(car);
    fleetManager.addVehicle(drone, dronePermission);

    try {
        fleetManager.saveToFile();
        cout << "Fleet saved successfully.\n";

        Manager newManager;
        newManager.loadFromFile();
        cout << "Fleet loaded successfully.\n";

        newManager.displayDetails();

        string user1[] = {"airspace_license"};
        cout << "\nChecking access for drone (allowed):\n";
        newManager.checkAccess(2, user1, 1);

        string user2[] = {"basic_license"};
        cout << "\nChecking access for van (denied):\n";
        newManager.checkAccess(0, user2, 1);

    } catch (const char* msg) {
        cerr << "Exception: " << msg << endl;
    }

    return 0;
}
