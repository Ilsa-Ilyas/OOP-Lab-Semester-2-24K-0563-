#include <iostream>
#include <string>

using namespace std;

// ServiceStation class representing each station
class ServiceStation {
private:
    static int totalStations;     // Total number of service stations
    const string stationName;     // Unique and immutable station name

public:
    // Constructor
    ServiceStation(const string& name) : stationName(name) {
        totalStations++;
    }

    // Destructor
    ~ServiceStation() {
        totalStations--;
    }

    // Display station details
    void displayDetails() const {
        cout << "Station Name: " << stationName << endl;
    }

    // Static method to get total stations
    static int getTotalStations() {
        return totalStations;
    }

    // Getter for station name
    string getStationName() const {
        return stationName;
    }
};

// Static member initialization
int ServiceStation::totalStations = 0;

// Attendant class representing each attendant
class Attendant {
private:
    static int nextAttendantID;   // Auto-incrementing unique ID for each attendant
    static int totalAttendants;   // Total number of attendants

    const int attendantID;        // Unique and immutable attendant ID
    const string attendantName;   // Immutable attendant name
    ServiceStation* const station; // Permanently assigned station

public:
    // Constructor
    Attendant(const string& name, ServiceStation* assignedStation) 
        : attendantID(nextAttendantID++), attendantName(name), station(assignedStation) {
        totalAttendants++;
    }

    // Destructor
    ~Attendant() {
        totalAttendants--;
    }

    // Display attendant details
    void displayDetails() const {
        cout << "Attendant ID: " << attendantID << endl;
        cout << "Name: " << attendantName << endl;
        cout << "Station: " << station->getStationName() << endl;
    }

    // Static method to get total attendants
    static int getTotalAttendants() {
        return totalAttendants;
    }
};

// Static member initialization
int Attendant::nextAttendantID = 1;
int Attendant::totalAttendants = 0;

int main() {
    // Creating service stations
    ServiceStation* burgerStation = new ServiceStation("Burger Station");
    ServiceStation* drinkStation = new ServiceStation("Drinks Station");

    // Creating attendants
    Attendant* a1 = new Attendant("Alice", burgerStation);
    Attendant* a2 = new Attendant("Bob", drinkStation);
    Attendant* a3 = new Attendant("Charlie", burgerStation);

    // Displaying station details
    cout << "\nService Stations Details:\n";
    burgerStation->displayDetails();
    drinkStation->displayDetails();

    // Displaying attendant details
    cout << "\nAttendants Details:\n";
    a1->displayDetails();
    a2->displayDetails();
    a3->displayDetails();

    // Display total counts
    cout << "\nTotal Stations: " << ServiceStation::getTotalStations() << endl;
    cout << "Total Attendants: " << Attendant::getTotalAttendants() << endl;

    // Deallocating memory for attendants
    delete a1;
    delete a2;
    delete a3;

    cout << "\nAfter attendants leave, Total Attendants: " << Attendant::getTotalAttendants() << endl;

    // Deallocating memory for stations
    delete burgerStation;
    delete drinkStation;

    cout << "After removing stations, Total Stations: " << ServiceStation::getTotalStations() << endl;

    return 0;
}