#include <iostream>
#include <string>

using namespace std;

const int MAX_STOPS = 10;
const int MAX_ATTENDANCE = 100;
const int MAX_STUDENTS = 100;  
const int MAX_ROUTES = 10;   

class Student;  

class TransportationCard {
private:
    int cardId;
    Student* student;  

public:
    TransportationCard(int id, Student* s) : cardId(id), student(s) {}

    void activateCard() {
        cout << "Card " << cardId << " activated.\n";
    }

    void deactivateCard() {
        cout << "Card" << cardId << " deactivated.\n";
    }

    int getCardID() const {
        return cardId;
    }

    ~TransportationCard() {}
};

class Student {
private:
    int studentID;
    string name;
    float balance;
    bool isActive;
    int assignedStop;
    TransportationCard* card;

public:
    Student(int id = 0, string n = "", float bal = 0.0, bool active = false)
        : studentID(id), name(n), balance(bal), isActive(active), assignedStop(0), card(nullptr) {}

    Student(int id, string n, int cardID) 
        : studentID(id), name(n), balance(0.0), isActive(false), assignedStop(0) {
        card = new TransportationCard(cardID, this);
    }

    int getStudentID() const { return studentID; }
    string getName() const { return name; }
    float getBalance() const { return balance; }
    bool getIsActive() const { return isActive; }

    void setBalance(float bal) { balance = bal; }
    void setIsActive(bool active) { isActive = active; }

    void registerStudent() {
        cout << "Student " << name << " (ID: " << studentID << ") registered for transportation service." << endl;
    }

    void payFees(float amount) {
        balance += amount;
        if (balance < 0) {
            isActive = false; 
            cout << "Payment processed, but card is now deactivated due to insufficient balance." << endl;
            if (card) {
                card->deactivateCard();
            }
        } else {
            isActive = true; 
            cout << "Payment successful. Card activated." << endl;
        }
    }

    void checkBalance() const {
        cout << "Balance for " << name << " (ID: " << studentID << "): $" << balance << endl;
    }

    void assignStop(int stop) {
        assignedStop = stop;
        cout << "Stop " << stop << " assigned to student " << name << endl;
    }

    void displayStudent() const {
        cout << "Student ID: " << studentID << ", Name: " << name 
             << ", Balance: $" << balance << ", Active: " << (isActive ? "Yes" : "No")
             << ", Assigned Stop: " << assignedStop << endl;
    }

    ~Student() {
        delete card;
    }
};

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

    void setStopID(int id) { stopID = id; }
    void setStopName(string name) { stopName = name; }
    void setRouteID(int route) { routeID = route; }
};

class BusRoute {
private:
    int routeID;
    string routeName;
    Stop* stops[MAX_STOPS]; // Array of pointers to Stop objects
    int stopCount;

public:
    BusRoute(int id = 0, string name = "") : routeID(id), routeName(name), stopCount(0) {}

    void addStop(Stop* stop) {
        if (stopCount < MAX_STOPS) {
            stops[stopCount++] = stop;
        } else {
            cout << "Maximum stops reached for route " << routeID << endl;
        }
    }

    void displayRoute() const {
        cout << "Route " << routeID << ": " << routeName << endl;
        for (int i = 0; i < stopCount; i++) {
            stops[i]->getStopDetails();
        }
    }

    int getRouteID() const { return routeID; }
    string getRouteName() const { return routeName; }
    
    ~BusRoute() {
        for (int i = 0; i < stopCount; i++) {
            delete stops[i]; // Free dynamically allocated memory
        }
    }
};

class AttendanceSystem {
private:
    int studentIDs[MAX_ATTENDANCE];
    string timestamps[MAX_ATTENDANCE];
    int attendanceCount;

public:
    AttendanceSystem() : attendanceCount(0) {}

    void recordAttendance(int studentID, const string& timestamp) {
        if (attendanceCount < MAX_ATTENDANCE) {
            studentIDs[attendanceCount] = studentID;
            timestamps[attendanceCount] = timestamp;
            attendanceCount++;
            cout << "Attendance recorded for student ID: " << studentID << " at " << timestamp << endl;
        } else {
            cout << "Attendance log is full. Cannot record more entries.\n";
        }
    }

    void displayAttendance() const {
        if (attendanceCount == 0) {
            cout << "No attendance records found.\n";
            return;
        }

        for (int i = 0; i < attendanceCount; i++) {
            cout << "Student ID: " << studentIDs[i] << ", Time: " << timestamps[i] << endl;
        }
    }
};

class TransportationSystem {
private:
    Student students[MAX_STUDENTS];
    BusRoute routes[MAX_ROUTES];
    AttendanceSystem attendance;
    static int studentCount;
    int studentIndex;
    int routeIndex;

public:
    TransportationSystem() : studentIndex(0), routeIndex(0) {}

    void registerStudent(int id, string name, int cardID) {
        if (studentIndex < MAX_STUDENTS) {
            students[studentIndex] = Student(id, name, cardID);
            students[studentIndex].registerStudent();
            studentIndex++;
            studentCount++;
        } else {
            cout << "Student registration limit reached.\n";
        }
    }

    void assignStop(int studentID, int stopID) {
        for (int i = 0; i < studentIndex; i++) {
            if (students[i].getStudentID() == studentID) {
                students[i].assignStop(stopID);
                return;
            }
        }
        cout << "Student ID " << studentID << " not found." << endl;
    }

    void displayAllStudents() const {
        for (int i = 0; i < studentIndex; i++) {
            students[i].displayStudent();
        }
    }

    void recordAttendance(int studentID) {
        string timestamp = "current_time";
        attendance.recordAttendance(studentID, timestamp);
    }

    void displayActiveStudents() const {
        cout << "Total Students: " << studentCount << endl;
        for (int i = 0; i < studentIndex; i++) {
            if (students[i].getIsActive()) {
                students[i].displayStudent();
            }
        }
    }

    Student* findStudent(int studentID) {
        for (int i = 0; i < studentIndex; i++) {
            if (students[i].getStudentID() == studentID) {
                return &students[i];
            }
        }
        return nullptr;
    }

    void addBusRoute(const BusRoute& route) {
        if (routeIndex < MAX_ROUTES) {
            routes[routeIndex] = route;
            routeIndex++;
        } else {
            cout << "Cannot add more routes, limit reached.\n";
        }
    }

    void displayAllRoutes() const {
        for (int i = 0; i < routeIndex; i++) {
            routes[i].displayRoute();
        }
    }
};

int TransportationSystem::studentCount = 0;

int main() {
    TransportationSystem system;
    int choice;

    BusRoute* route1 = new BusRoute(1, "Main Campus Route");
    route1->addStop(new Stop(1, "Gate A", 1));
    route1->addStop(new Stop(2, "Library", 1));
    system.addBusRoute(*route1);

    BusRoute* route2 = new BusRoute(2, "City Center Route");
    route2->addStop(new Stop(3, "Downtown", 2));
    route2->addStop(new Stop(4, "Central Park", 2));
    system.addBusRoute(*route2);

    do {
        cout << "\n===== Transportation Management System =====\n";
        cout << "1. Register Student\n";
        cout << "2. Pay Fees\n";
        cout << "3. Assign Route\n";
        cout << "4. Record Attendance\n";
        cout << "5. Display Active Students\n";
        cout << "6. Display All Routes\n";
        cout << "7. Display All Students\n";
        cout << "8. Exit\n";
        cout << "============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, cardID;
                string name;
                cout << "Enter Student ID: ";
                cin >> id;
                cout << "Enter Student Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Card ID: ";
                cin >> cardID;
                system.registerStudent(id, name, cardID);
                break;
            }
            case 2: {
                int id;
                float amount;
                cout << "Enter Student ID: ";
                cin >> id;
                cout << "Enter Amount to Pay: ";
                cin >> amount;

                Student* student = system.findStudent(id);
                if (student) {
                    student->payFees(amount);
                } else {
                    cout << "Student ID " << id << " not found.\n";
                }
                break;
            }
            case 3: {
                int studentID, stopID;
                cout << "Enter Student ID: ";
                cin >> studentID;
                cout << "Enter Stop ID: ";
                cin >> stopID;
                system.assignStop(studentID, stopID);
                break;
            }
            case 4: {
                int studentID;
                cout << "Enter Student ID: ";
                cin >> studentID;
                system.recordAttendance(studentID);
                break;
            }
            case 5: {
                system.displayActiveStudents();
                break;
            }
            case 6: {
                system.displayAllRoutes();
                break;
            }
            case 7: {
                system.displayAllStudents();
                break;
            }
            case 8: {
                cout << "Exiting the system.\n";
                delete route1;
                delete route2;
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (true);

    return 0;
}

