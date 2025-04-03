#include <iostream>
#include <string>
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

// -------------------- Person (Base Class) --------------------
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
        card = new TransportationCard(cardID, this);
    }

    virtual void payFees(float amount) = 0;  // Dynamic Polymorphism

    // --- Static Polymorphism: Function Overloading ---
    virtual void payFees() {
        cout << "[Info] General fee inquiry. Balance: " << balance << endl;
    }

    virtual void payFees(int months) {
        cout << "[Info] Base class - monthly payment not defined.\n";
    }

    virtual void displayPerson() const = 0;

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
        payFees(total); // call float version
        cout << "[Teacher] Paid for " << months << " month(s): " << total << endl;
    }

    void displayPerson() const override {
        cout << "[Teacher] ID: " << id << ", Name: " << name << ", Active: " << isActive << endl;
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
};

// -------------------- Stop Class --------------------
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

    int getStopID() const { return stopID; }
    string getStopName() const { return stopName; }
    int getRouteID() const { return routeID; }
};

// -------------------- Bus Route --------------------
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

    int getRouteID() const { return routeID; }
    string getRouteName() const { return routeName; }

    // Operator Overloading
    bool operator==(const BusRoute& other) const {
        return routeID == other.routeID && routeName == other.routeName;
    }

    bool operator!=(const BusRoute& other) const {
        return !(*this == other);
    }
};

// -------------------- Attendance System --------------------
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
};

// -------------------- Transportation System --------------------
class TransportationSystem {
private:
    Person* users[MAX_USERS];
    int userCount;

    BusRoute routes[MAX_ROUTES];
    int routeCount;

    AttendanceSystem attendance;

public:
    TransportationSystem() : userCount(0), routeCount(0) {}

    ~TransportationSystem() {
        for (int i = 0; i < userCount; ++i) {
            delete users[i];
        }
    }

    void addUser(Person* p) {
        if (userCount < MAX_USERS) {
            users[userCount++] = p;
        } else {
            cout << "User limit reached.\n";
        }
    }

    void recordAttendance(int personID) {
        string time = "10:00 AM"; // Placeholder
        attendance.recordAttendance(personID, time);
    }

    void displayAllUsers() const {
        for (int i = 0; i < userCount; ++i) {
            users[i]->displayPerson();
        }
    }

    void displayActiveUsers() const {
        for (int i = 0; i < userCount; ++i) {
            if (users[i]->getIsActive()) {
                users[i]->displayPerson();
            }
        }
    }

    Person* findUserByID(int id) {
        for (int i = 0; i < userCount; ++i) {
            if (users[i]->getID() == id) {
                return users[i];
            }
        }
        return nullptr;
    }

    void addRoute(const BusRoute& route) {
        if (routeCount < MAX_ROUTES) {
            routes[routeCount++] = route;
        } else {
            cout << "Route limit reached.\n";
        }
    }

    void displayRoutes() const {
        for (int i = 0; i < routeCount; ++i) {
            routes[i].displayRoute();
        }
    }
};

// -------------------- Main --------------------
int main() {
    TransportationSystem system;

    // Add routes
    BusRoute route1(1, "Campus Route");
    route1.addStop(Stop(1, "Gate A", 1));
    route1.addStop(Stop(2, "Library", 1));

    BusRoute route2(2, "City Route");
    route2.addStop(Stop(3, "Downtown", 2));
    route2.addStop(Stop(4, "Central Park", 2));

    system.addRoute(route1);
    system.addRoute(route2);

    // Add users
    system.addUser(new Student(101, "Alice", 201));
    system.addUser(new Teacher(102, "Dr. Smith", 202));
    system.addUser(new Staff(103, "Mr. John", 203));

    // Payments & Overloading
    Person* p = system.findUserByID(101);
    if (p) {
        p->payFees(1000); // dynamic
        p->payFees();     // static
    }

    p = system.findUserByID(102);
    if (p) {
        p->payFees(1500); // dynamic
        p->payFees(2);    // static: monthly fee
    }

    // Attendance
    system.recordAttendance(101);
    system.recordAttendance(102);

    // Display
    cout << "\n=== All Users ===\n";
    system.displayAllUsers();

    cout << "\n=== Active Users ===\n";
    system.displayActiveUsers();

    cout << "\n=== Routes ===\n";
    system.displayRoutes();

    // Operator Overloading Demo
    cout << "\n=== Route Comparison ===\n";
    if (route1 == route2)
        cout << "Routes are the same.\n";
    else
        cout << "Routes are different.\n";

    return 0;
}

