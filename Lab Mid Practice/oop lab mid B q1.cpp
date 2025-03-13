#include <iostream>
#include <string>

using namespace std;

class Patient {
private:
    static int nextPatientID;        // Auto-incrementing unique ID for each patient
    static int totalPatients;        // Total number of admitted patients
    static const string hospitalName; // Constant hospital name for all patients
    
    const int patientID;             // Unique and immutable patient ID
    string patientName;
    double medicalExpenses;          // Total medical expenses for the patient

public:
    // Constructor
    Patient(const string& name) : patientID(nextPatientID++), patientName(name), medicalExpenses(0.0) {
        totalPatients++;
    }

    // Destructor
    ~Patient() {
        totalPatients--;
    }

    // Method to add medical expenses
    void addExpense(double amount) {
        if (amount > 0) {
            medicalExpenses += amount;
        }
    }

    // Method to display patient details
    void displayDetails() const {
        cout << "Patient Name: " << patientName << endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Hospital Name: " << hospitalName << endl;
        cout << "Medical Expenses: $" << medicalExpenses << endl;
    }

    // Static method to get the total admitted patients
    static int getTotalPatients() {
        return totalPatients;
    }
};

// Static member initialization
int Patient::nextPatientID = 1;
int Patient::totalPatients = 0;
const string Patient::hospitalName = "Happy Home";

int main() {
    Patient* p1 = new Patient("Sara");
    Patient* p2 = new Patient("Hassan");
    Patient* p3 = new Patient("Umais");

    p1->addExpense(56.09);
    p2->addExpense(178.97);
    p3->addExpense(78890.31);

    // Displaying patient details
    cout << "\nPatient Details:\n";
    p1->displayDetails();
    p2->displayDetails();
    p3->displayDetails();

    // Displaying total patients
    cout << "Total Patients: " << Patient::getTotalPatients() << endl;

    // Discharging a patient
    delete p1;
    cout << "Total Patients Now: " << Patient::getTotalPatients() << endl;

    // Clean up remaining memory
    delete p2;
    delete p3;
    cout << "Final Total Patients: " << Patient::getTotalPatients() << endl;

    return 0;
}