#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  // For formatting output to file
using namespace std;

//
// ---------- A. TelemetryDataClass ----------
// Holds fuel consumption, speed, and engine status info
//
class TelemetryDataClass {
    float FuelConsumption;   // Liters per hour
    float Speed;             // km/h
    bool EngineStatus;       // true = engine running

public:
    // Constructor
    TelemetryDataClass(float fuel = 0.0, float s = 0.0, bool engine = false) {
        FuelConsumption = fuel;
        Speed = s;
        EngineStatus = engine;
    }

    // Getter methods
    float getFuelConsumption() const { return FuelConsumption; }
    float getSpeed() const { return Speed; }
    bool isEngineRunning() const { return EngineStatus; }

    // Setter methods
    void setFuelConsumption(float fuel) { FuelConsumption = fuel; }
    void setSpeed(float s) { Speed = s; }
    void setEngineStatus(bool engine) { EngineStatus = engine; }

    // Print telemetry data
    void display() const {
        cout << "Fuel Consumption: " << FuelConsumption << " L/h\n";
        cout << "Speed: " << Speed << " km/h\n";
        cout << "Engine Status: " << (EngineStatus ? "Running" : "Off") << "\n";
    }
};

//
// ---------- B. Base Vehicle Class ----------
// Stores basic vehicle info and telemetry
//
class Vehicle {
protected:
    string vehicleID;
    string model;
    string fuelType;
    string currentLocation;
    TelemetryDataClass telemetryData;

public:
    // Constructor
    Vehicle(string id, string mdl, string fuel, string location, TelemetryDataClass tData)
        : vehicleID(id), model(mdl), fuelType(fuel), currentLocation(location), telemetryData(tData) {}

    // Virtual display function (for polymorphism)
    virtual void displayDetails() const {
        cout << "Vehicle ID: " << vehicleID << endl;
        cout << "Model: " << model << endl;
        cout << "Fuel Type: " << fuelType << endl;
        cout << "Current Location: " << currentLocation << endl;
        cout << "--- Telemetry Data ---" << endl;
        telemetryData.display();
    }

    // Update current location
    void updateLocation(const string& newLocation) {
        if (newLocation.empty()) {
            cerr << "Error: Location cannot be empty.\n";
            return;
        }
        currentLocation = newLocation;
    }

    // Retrieve vehicle ID
    string getVehicleID() const {
        return vehicleID;
    }

    // Declare VehicleManager as a friend to allow access to protected members
    friend class VehicleManager;
};

//
// ---------- C. VehicleManager Class ----------
// Tracks, writes, and reads vehicle info
//
class VehicleManager {
public:
    // Track and print current location
    void trackVehicleLocation(Vehicle& vehicle) {
        cout << "Tracking Vehicle ID: " << vehicle.vehicleID
             << " — Current Location: " << vehicle.currentLocation << endl;
    }

    // Write all vehicle info to file
    void WriteToFile(Vehicle* vehiclesArray[], int size) {
        ofstream file("vehicle_info.txt");
        if (!file.is_open()) {
            cerr << "Could not open file for writing.\n";
            return;
        }

        for (int i = 0; i < size; ++i) {
            file << vehicleToString(*vehiclesArray[i]) << endl;
        }

        file.close();
        cout << "Vehicle data written to vehicle_info.txt\n";
    }

    // Read file and display vehicles in Karachi
    void ReadFromFile() {
        ifstream file("vehicle_info.txt");
        if (!file.is_open()) {
            cerr << "Couldn't open file\n";
            return;
        }

        string line;
        cout << "Vehicles in Karachi:\n";
        while (getline(file, line)) {
            if (line.find("Location: Karachi") != string::npos) {
                cout << line << endl;
            }
        }

        file.close();
    }

private:
    // Helper function to convert vehicle to string (used for file writing)
    string vehicleToString(const Vehicle& v) {
        stringstream ss;
        ss << "ID: " << v.vehicleID
           << ", Model: " << v.model
           << ", Fuel: " << v.fuelType
           << ", Location: " << v.currentLocation
           << ", FuelConsumption: " << v.telemetryData.getFuelConsumption()
           << ", Speed: " << v.telemetryData.getSpeed()
           << ", EngineStatus: " << (v.telemetryData.isEngineRunning() ? "Running" : "Off");
        return ss.str();
    }
};

//
// ---------- D. MeterReadingVehicle Subclass ----------
// Adds reading capacity for meter reading tasks
//
class MeterReadingVehicle : public Vehicle {
private:
    int readingCapacity;

public:
    MeterReadingVehicle(int capacity, string id, string mdl, string fuel, string location, TelemetryDataClass tData)
        : Vehicle(id, mdl, fuel, location, tData), readingCapacity(capacity) {}

    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Reading Capacity: " << readingCapacity << " meters\n";
    }
};

//
// ---------- E. PipelineInspectionVehicle Subclass ----------
// Adds inspection range for pipeline tasks
//
class PipelineInspectionVehicle : public Vehicle {
private:
    int inspectionRange;

public:
    PipelineInspectionVehicle(string id, string mdl, string fuel, string location, TelemetryDataClass tData, int range)
        : Vehicle(id, mdl, fuel, location, tData), inspectionRange(range) {}

    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Inspection Range: " << inspectionRange << " meters\n";
    }
};

//
// ---------- F. MaintenanceVehicle Subclass ----------
// Adds equipment capacity for maintenance tasks
//
class MaintenanceVehicle : public Vehicle {
private:
    int equipmentCapacity;

public:
    MaintenanceVehicle(string id, string mdl, string fuel, string location, TelemetryDataClass tData, int capacity)
        : Vehicle(id, mdl, fuel, location, tData), equipmentCapacity(capacity) {}

    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Equipment Capacity: " << equipmentCapacity << " units\n";
    }
};

//
// ---------- Main Function (Example Demo) ----------
// Creates instances, writes to file, reads Karachi vehicles
//
int main() {
    // Create telemetry data
    TelemetryDataClass t1(5.5, 60, true);
    TelemetryDataClass t2(6.3, 50, false);
    TelemetryDataClass t3(7.8, 55, true);

    // Create specialized vehicle objects
    MeterReadingVehicle v1(150, "V1001", "Toyota Hilux 2020", "Diesel", "Karachi", t1);
    PipelineInspectionVehicle v2("V1002", "Land Cruiser 2021", "Diesel", "Hyderabad", t2, 500);
    MaintenanceVehicle v3("V1003", "Isuzu D-Max 2019", "Diesel", "Karachi", t3, 40);

    // Store all vehicles in a pointer array for polymorphism
    Vehicle* fleet[3] = { &v1, &v2, &v3 };

    // Create vehicle manager and perform operations
    VehicleManager vm;
    vm.trackVehicleLocation(v1);
    vm.WriteToFile(fleet, 3);
    vm.ReadFromFile();

    return 0;
}
