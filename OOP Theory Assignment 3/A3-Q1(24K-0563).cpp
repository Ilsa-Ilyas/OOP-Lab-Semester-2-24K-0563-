#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

#define STUDENT_NAME "Ilsa Ilyas"
#define STUDENT_ID "24K-0563"

const int MAX_USERS = 100;
const int MAX_STOPS = 10;
const int MAX_ROUTES = 10;
const int MAX_ATTENDANCE = 200;

class Person; // Forward declaration

// -------------------- Transportation Card --------------------

class TransportationCard {
private:
    int cardId;
    Person* owner;
    
public:
    TransportationCard(int id, Person* o = nullptr) : cardId(id), owner(o) {}

    void activateCard() {

        cout << "Card " << cardId << " activated.\n";

    }



    void deactivateCard() {

        cout << "Card " << cardId << " deactivated.\n";

    }



    int getCardID() const {

        return cardId;

    }



    ~TransportationCard() {}

};



// -------------------- Person (Abstract Class) --------------------

class Person {

protected:

    int id;

    string name;

    TransportationCard* card;

    float balance;

    bool isActive;



public:

    Person(int id, string name, int cardID)

        : id(id), name(name), balance(0.0), isActive(false) {

        try {

            card = new TransportationCard(cardID, this);

        } catch (bad_alloc& e) {

            cerr << "Memory allocation failed for TransportationCard: " << e.what() << endl;

        }

    }



    virtual void payFees(float amount) = 0;

    virtual void payFees() {

        cout << "[Info] General fee inquiry. Balance: " << balance << endl;

    }

    virtual void payFees(int months) {

        cout << "[Info] Base class - monthly payment not defined.\n";

    }

    virtual void displayPerson() const = 0;

    virtual void login() = 0; // pure virtual login function



    virtual ~Person() {

        delete card;

    }



    bool getIsActive() const { return isActive; }

    int getID() const { return id; }

    string getName() const { return name; }

};



// -------------------- Student Class --------------------

class Student : public Person {

private:

    int assignedStop;



public:

    Student(int id, string name, int cardID)

        : Person(id, name, cardID), assignedStop(0) {}



    void assignStop(int stop) {

        assignedStop = stop;

        cout << "Stop " << stop << " assigned to student " << name << endl;

    }



    void payFees(float amount) override {

        balance += amount;

        isActive = (balance >= 0);

        cout << "[Student] Paid: " << amount << ". Status: " << (isActive ? "Active" : "Inactive") << endl;

    }



    void payFees() override {

        cout << "[Student] Current Balance: " << balance << endl;

    }



    void displayPerson() const override {

        cout << "[Student] ID: " << id << ", Name: " << name << ", Active: " << isActive

             << ", Stop: " << assignedStop << endl;

    }



    void login() override {

        string pwd;

        cout << "Enter password for Student (ID: " << id << "): ";

        cin >> pwd; // Simulated

        cout << "Student logged in successfully.\n";

    }

};



// -------------------- Teacher Class --------------------

class Teacher : public Person {

public:

    Teacher(int id, string name, int cardID)

        : Person(id, name, cardID) {}



    void payFees(float amount) override {

        balance += amount;

        isActive = (balance >= 0);

        cout << "[Teacher] Paid: " << amount << ". Status: " << (isActive ? "Active" : "Inactive") << endl;

    }



    void payFees(int months) override {

        float monthlyRate = 1500;

        float total = months * monthlyRate;

        payFees(total);

        cout << "[Teacher] Paid for " << months << " month(s): " << total << endl;

    }



    void displayPerson() const override {

        cout << "[Teacher] ID: " << id << ", Name: " << name << ", Active: " << isActive << endl;

    }



    void login() override {

        string otp;

        cout << "Enter OTP for Teacher (ID: " << id << "): ";

        cin >> otp;

        cout << "Teacher logged in successfully.\n";

    }

};



// -------------------- Staff Class --------------------

class Staff : public Person {

public:

    Staff(int id, string name, int cardID)

        : Person(id, name, cardID) {}



    void payFees(float amount) override {

        balance += amount;

        isActive = (balance >= 0);

        cout << "[Staff] Paid: " << amount << ". Status: " << (isActive ? "Active" : "Inactive") << endl;

    }



    void displayPerson() const override {

        cout << "[Staff] ID: " << id << ", Name: " << name << ", Active: " << isActive << endl;

    }



    void login() override {

        cout << "Staff logged in with ID verification.\n";

    }

};



// -------------------- Utility Template --------------------

template<typename T>

void displayList(const T arr[], int size) {

    for (int i = 0; i < size; ++i) {

        arr[i].getStopDetails();

    }

}



// -------------------- Stop Class with File Handling --------------------

class Stop {

private:

    int stopID;

    string stopName;

    int routeID;



public:

    Stop(int id = 0, string name = "", int route = 0) : stopID(id), stopName(name), routeID(route) {}



    void getStopDetails() const {

        cout << "Stop ID: " << stopID << ", Name: " << stopName << ", Route: " << routeID << endl;

    }



    void saveToFile(ofstream& out) const {

        out.write(reinterpret_cast<const char*>(&stopID), sizeof(stopID));

        size_t len = stopName.size();

        out.write(reinterpret_cast<const char*>(&len), sizeof(len));

        out.write(stopName.c_str(), len);

        out.write(reinterpret_cast<const char*>(&routeID), sizeof(routeID));

    }



    void loadFromFile(ifstream& in) {

        in.read(reinterpret_cast<char*>(&stopID), sizeof(stopID));

        size_t len;

        in.read(reinterpret_cast<char*>(&len), sizeof(len));

        stopName.resize(len);

        in.read(&stopName[0], len);

        in.read(reinterpret_cast<char*>(&routeID), sizeof(routeID));

    }

};



// -------------------- Bus Route Class with File Handling --------------------

class BusRoute {

private:

    int routeID;

    string routeName;

    Stop stops[MAX_STOPS];

    int stopCount;



public:

    BusRoute(int id = 0, string name = "") : routeID(id), routeName(name), stopCount(0) {}



    void addStop(const Stop& stop) {

        if (stopCount < MAX_STOPS) {

            stops[stopCount++] = stop;

        } else {

            cout << "Maximum stops reached for route " << routeID << endl;

        }

    }



    void displayRoute() const {

        cout << "Route " << routeID << ": " << routeName << endl;

        for (int i = 0; i < stopCount; ++i) {

            stops[i].getStopDetails();

        }

    }



    void saveToFile(ofstream& out) const {

        out.write(reinterpret_cast<const char*>(&routeID), sizeof(routeID));

        size_t len = routeName.size();

        out.write(reinterpret_cast<const char*>(&len), sizeof(len));

        out.write(routeName.c_str(), len);

        out.write(reinterpret_cast<const char*>(&stopCount), sizeof(stopCount));

        for (int i = 0; i < stopCount; ++i) {

            stops[i].saveToFile(out);

        }

    }



    void loadFromFile(ifstream& in) {

        in.read(reinterpret_cast<char*>(&routeID), sizeof(routeID));

        size_t len;

        in.read(reinterpret_cast<char*>(&len), sizeof(len));

        routeName.resize(len);

        in.read(&routeName[0], len);

        in.read(reinterpret_cast<char*>(&stopCount), sizeof(stopCount));

        for (int i = 0; i < stopCount; ++i) {

            stops[i].loadFromFile(in);

        }

    }



    int getRouteID() const { return routeID; }

    string getRouteName() const { return routeName; }



    bool operator==(const BusRoute& other) const {

        return routeID == other.routeID && routeName == other.routeName;

    }



    bool operator!=(const BusRoute& other) const {

        return !(*this == other);

    }

};



// -------------------- Attendance System with File Handling --------------------

class AttendanceSystem {

private:

    int ids[MAX_ATTENDANCE];

    string times[MAX_ATTENDANCE];

    int recordCount;



public:

    AttendanceSystem() : recordCount(0) {}



    void recordAttendance(int personID, const string& timestamp) {

        if (recordCount < MAX_ATTENDANCE) {

            ids[recordCount] = personID;

            times[recordCount] = timestamp;

            ++recordCount;

            cout << "Attendance recorded for ID " << personID << " at " << timestamp << endl;

        } else {

            cout << "Attendance log full.\n";

        }

    }



    void displayAttendance() const {

        if (recordCount == 0) {

            cout << "No attendance records found.\n";

            return;

        }



        for (int i = 0; i < recordCount; ++i) {

            cout << "ID: " << ids[i] << ", Time: " << times[i] << endl;

        }

}



    void saveToFile(const string& filename) {

        ofstream out(filename, ios::binary);

        if (!out) throw runtime_error("Failed to open attendance file for writing.");

        out.write(reinterpret_cast<const char*>(&recordCount), sizeof(recordCount));

        for (int i = 0; i < recordCount; ++i) {

            out.write(reinterpret_cast<const char*>(&ids[i]), sizeof(ids[i]));

            size_t len = times[i].size();

            out.write(reinterpret_cast<const char*>(&len), sizeof(len));

            out.write(times[i].c_str(), len);

        }

    }

    void loadFromFile(const string& filename) {

        ifstream in(filename, ios::binary);

        if (!in) throw runtime_error("Failed to open attendance file for reading.");

        in.read(reinterpret_cast<char*>(&recordCount), sizeof(recordCount));

        for (int i = 0; i < recordCount; ++i) {

            in.read(reinterpret_cast<char*>(&ids[i]), sizeof(ids[i]));

            size_t len;

            in.read(reinterpret_cast<char*>(&len), sizeof(len));

            times[i].resize(len);

            in.read(&times[i][0], len);

        }

    }

};

// -------------------- Main Function --------------------

int main() {
    cout << "=== FAST Transportation System ===";
    try {
        // Initialize attendance system and load data
        AttendanceSystem attendance;
        try {
            attendance.loadFromFile("attendance.bin");
        } catch (const runtime_error& e) {
            cerr << e.what() << endl;
        }

        // Create sample users
        Student student(1, "Sara", 101);
        Teacher teacher(2, "Dr. Raymon", 102);
        Staff staff(3, "Mr. Feeble", 103);

        // Simulate login and actions
        student.login();
        student.payFees(1200);
        student.assignStop(5);
        attendance.recordAttendance(student.getID(), "08:00 AM");

        teacher.login();
        teacher.payFees(2);
        attendance.recordAttendance(teacher.getID(), "08:05 AM");
        staff.login();
        staff.payFees(800);
        attendance.recordAttendance(staff.getID(), "08:10 AM");

        // Display users
        cout << "--- Users ---";
        student.displayPerson();
        teacher.displayPerson();
        staff.displayPerson();

        // Save attendance

        attendance.saveToFile("attendance.bin");
    } catch (exception& e) {

        cerr << "Unexpected error: " << e.what() << endl;

    }

    return 0;
}
