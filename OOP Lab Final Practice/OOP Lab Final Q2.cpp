#include <iostream>
#include <string>

using namespace std;

class Device {
protected:
    string model;                // Device model name, e.g., "SmartFridge X100"
    int energyConsumption;      // Energy used by device (starts at 10 kWh)

public:
    // Constructor to initialize model name and energy consumption
    Device(string model) : model(model), energyConsumption(10) {}

    // Pure virtual function to be implemented in each derived device class
    virtual void runCycle() = 0;

    // Getter function for model name (const to prevent modification)
    string getModel() const { return model; }

    // Overloaded > operator to compare energy usage between two devices
    bool operator>(const Device& d) const {
        return energyConsumption > d.energyConsumption;
    }

    // Overloaded prefix ++ operator (SmartOven will override this)
    virtual Device& operator++() { return *this; }

    // Virtual status display function, allows polymorphic printing
    virtual void printStatus(ostream& os) const {
        os << model << ": " << energyConsumption << " kWh";
    }

    // Overloaded << operator to print any Device using cout << device;
    friend ostream& operator<<(ostream& os, const Device& device) {
        device.printStatus(os);  // polymorphic call
        return os;
    }

    // Virtual destructor to ensure proper cleanup of derived objects
    virtual ~Device() {}
};

class SmartFridge : public Device {
    const int energyIncrease = 15;  // Fixed energy increase per cycle

public:
    SmartFridge(string model) : Device(model) {}

    void runCycle() override {
        cout << model << " is Cooling groceries..." << endl;

        // Safely add energy with 100 kWh cap
        if (energyConsumption + energyIncrease <= 100)
            energyConsumption += energyIncrease;
        else
            energyConsumption = 100;
    }

    void printStatus(ostream& os) const override {
        os << model << ": " << energyConsumption << " kWh";
    }
};

class SmartWasher : public Device {
    const int energyIncrease = 30;  // Washer uses 30 kWh per cycle

public:
    SmartWasher(string model) : Device(model) {}

    void runCycle() override {
        cout << model << " is Running laundry cycle..." << endl;

        // Increase energy with cap at 100
        if (energyConsumption + energyIncrease <= 100)
            energyConsumption += energyIncrease;
        else
            energyConsumption = 100;
    }

    void printStatus(ostream& os) const override {
        os << model << ": " << energyConsumption << " kWh";
    }
};

class SmartOven : public Device {
    const int energyIncrease = 20; // Energy added per cycle
    int temperature;

public:
    SmartOven(string model) : Device(model), temperature(180) {}

    // Override ++ operator to increase temperature by 20°C
    Device& operator++() override {
        temperature += 20;
        return *this;
    }

    // Simulate running a baking cycle
    void runCycle() override {
        cout << model << " is Baking at " << temperature << "°C..." << endl;

        if (energyConsumption + energyIncrease <= 100)
            energyConsumption += energyIncrease;
        else
            energyConsumption = 100;
    }

    // Override print to include temperature
    void printStatus(ostream& os) const override {
        os << model << ": " << energyConsumption << " kWh, Oven Temp: " << temperature << "°C";
    }
};

int main() {
    Device* devices[3];
    devices[0] = new SmartFridge("SmartFridge X100");
    devices[1] = new SmartWasher("SmartWasher Turbo");
    devices[2] = new SmartOven("SmartOven Pro");

    for (int i = 0; i < 2; ++i)
        devices[i]->runCycle();

    ++(*devices[2]); // increase oven temperature
    devices[2]->runCycle();

    for (int i = 0; i < 3; ++i)
        std::cout << *devices[i] << std::endl;

    if (*devices[1] > *devices[0])
        std::cout << devices[1]->getModel() << " is more energy-intensive than " << devices[0]->getModel() << std::endl;

    // Clean up memory
    for (int i = 0; i < 3; ++i)
        delete devices[i];

    return 0;
}

