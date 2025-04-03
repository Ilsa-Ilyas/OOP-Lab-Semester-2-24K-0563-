#include <iostream>
#include <string>
using namespace std;

#define STUDENT_NAME "Ilsa Ilyas"
#define STUDENT_ID   "24K-0563"

// === Base Vehicle Class ===
class Vehicle {
protected:
    int vehicleID;
    double speed;
    double capacity;
    double efficiency;
    static int activeDeliveries;

public:
    Vehicle(int id, double spd, double cap, double eff)
        : vehicleID(id), speed(spd), capacity(cap), efficiency(eff) {}

    virtual void calculateRoute(const string& destination) {
        cout << "Calculating default route to " << destination << "...\n";
    }

    virtual double estimateDeliveryTime(double distance) {
        return distance / speed;
    }

    virtual void command(const string& action, int packageID) {
        if (action == "Deliver") {
            cout << "Vehicle " << vehicleID << " processing package " << packageID << "\n";
            activeDeliveries++;
        }
    }

    virtual void command(const string& action, int packageID, const string& urgency) {
        if (action == "Deliver") {
            cout << "Vehicle " << vehicleID << " processing package " << packageID << " with urgency: " << urgency << "\n";
            activeDeliveries++;
        }
    }

    virtual ~Vehicle() {}

    bool operator==(const Vehicle& v) const {
        if (speed == v.speed && capacity == v.capacity && efficiency == v.efficiency) {
            return true;
        } else {
            return false;
        }
    }

    int getID() const { return vehicleID; }
    double getSpeed() const { return speed; }
    double getCapacity() const { return capacity; }
    double getEfficiency() const { return efficiency; }

    static int getActiveDeliveries() {
        return activeDeliveries;
    }

    friend void resolveConflict(const Vehicle& v1, const Vehicle& v2, double distance, double weight, const string& urgency);
};

int Vehicle::activeDeliveries = 0;

// === Specialized Vehicles ===

class RamzanDrone : public Vehicle {
    int maxAltitude;

public:
    RamzanDrone(int id, double spd, double cap, double eff, int alt)
        : Vehicle(id, spd, cap, eff), maxAltitude(alt) {}

    void calculateRoute(const string& destination) override {
        cout << "Drone " << vehicleID << " plotting aerial path to " << destination << " (Max Altitude: " << maxAltitude << " ft)\n";
    }

    double estimateDeliveryTime(double distance) override {
        return distance / (speed * 0.2);
    }

    void command(const string& action, int packageID) override {
        cout << "Drone " << vehicleID << " dispatching package " << packageID << " for Iftar delivery.\n";
        activeDeliveries++;
    }

    void command(const string& action, int packageID, const string& urgency) override {
        if (urgency == "High") {
            cout << "Drone " << vehicleID << " engaging turbo mode for urgent Iftar package " << packageID << "\n";
        } else {
            cout << "Drone " << vehicleID << " processing " << packageID << " with urgency: " << urgency << "\n";
        }
        activeDeliveries++;
    }
};

class RamzanTimeShip : public Vehicle {
    int timeAccuracy;

    void validateHistory(int packageID) {
        cout << "TimeShip " << vehicleID << " validating historical data for package " << packageID << "... ✓\n";
    }

public:
    RamzanTimeShip(int id, double spd, double cap, double eff, int accuracy)
        : Vehicle(id, spd, cap, eff), timeAccuracy(accuracy) {}

    void calculateRoute(const string& destination) override {
        cout << "TimeShip " << vehicleID << " engaging chrono-path to " << destination << " (±" << timeAccuracy << " years)\n";
    }

    void command(const string& action, int packageID, const string& urgency) override {
        if (urgency == "High") {
            validateHistory(packageID);
            cout << "TimeShip " << vehicleID << " delivering historically-sensitive package " << packageID << "\n";
        } else {
            cout << "TimeShip " << vehicleID << " dispatching package " << packageID << " with urgency: " << urgency << "\n";
        }
        activeDeliveries++;
    }
};

class RamzanHyperPod : public Vehicle {
    string tunnel;

public:
    RamzanHyperPod(int id, double spd, double cap, double eff, const string& t)
        : Vehicle(id, spd, cap, eff), tunnel(t) {}

    void calculateRoute(const string& destination) override {
        cout << "HyperPod " << vehicleID << " navigating through tunnel [" << tunnel << "] to " << destination << "\n";
    }

    double estimateDeliveryTime(double distance) override {
        if (distance > 50) {
            return distance / (speed * 1.5);
        } else {
            return distance / speed;
        }
    }

    void command(const string& action, int packageID, const string& urgency) override {
        cout << "HyperPod " << vehicleID << " prioritizing " << urgency << " package " << packageID << " via " << tunnel << "\n";
        activeDeliveries++;
    }
};

// === Conflict Resolution ===
void resolveConflict(const Vehicle& v1, const Vehicle& v2, double distance, double weight, const string& urgency) {
    double score1 = (v1.speed / distance * 0.5) + (v1.capacity / weight * 0.3);
    if (urgency == "High") {
        score1 += v1.efficiency * 0.2;
    }

    double score2 = (v2.speed / distance * 0.5) + (v2.capacity / weight * 0.3);
    if (urgency == "High") {
        score2 += v2.efficiency * 0.2;
    }

    cout << "\n--- AI Conflict Resolution ---\n";
    cout << "Vehicle " << v1.vehicleID << " Score: " << score1 << "\n";
    cout << "Vehicle " << v2.vehicleID << " Score: " << score2 << "\n";

    if (score1 > score2) {
        cout << "Selected Vehicle: " << v1.vehicleID << " (more efficient)\n";
    } else if (score2 > score1) {
        cout << "Selected Vehicle: " << v2.vehicleID << " (more efficient)\n";
    } else {
        cout << "Tie detected. Defaulting to Vehicle " << v1.vehicleID << "\n";
    }
}

// === Main ===
int main() {
    cout << "Student: " << STUDENT_NAME << " | ID: " << STUDENT_ID << "\n\n";

    RamzanDrone drone(1, 100, 5, 0.95, 4000);
    RamzanTimeShip timeship(2, 90, 10, 0.9, 150);
    RamzanHyperPod hyperpod(3, 150, 20, 0.85, "GreenLine");

    // Polymorphic Routing
    Vehicle* fleet[3] = { &drone, &timeship, &hyperpod };
    cout << "--- Polymorphic Routing (Clifton) ---\n";
    for (int i = 0; i < 3; i++) {
        fleet[i]->calculateRoute("Clifton");
    }

    // Commands
    cout << "\n--- Delivery Commands ---\n";
    drone.command("Deliver", 1001);
    timeship.command("Deliver", 1002, "High");
    hyperpod.command("Deliver", 1003, "Medium");

    // Estimates
    cout << "\n--- Estimated Delivery Times ---\n";
    cout << "Drone: " << drone.estimateDeliveryTime(15) << " hours\n";
    cout << "TimeShip: " << timeship.estimateDeliveryTime(15) << " hours\n";
    cout << "HyperPod: " << hyperpod.estimateDeliveryTime(60) << " hours\n";

    // Comparison
    cout << "\n--- Vehicle Comparison ---\n";
    if (drone == timeship) {
        cout << "Drone == TimeShip: Yes\n";
    } else {
        cout << "Drone == TimeShip: No\n";
    }

    // Conflict Resolution
    resolveConflict(drone, hyperpod, 30, 7, "High");

    // Total Deliveries
    cout << "\nTotal Active Deliveries: " << Vehicle::getActiveDeliveries() << "\n";

    return 0;
}
