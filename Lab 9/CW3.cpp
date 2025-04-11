#include <iostream>
#include <string>

using namespace std;

class Doctor;
class Billing;

class PatientRecord
{
private:
    string name;
    string patientID;
    string dateOfBirth;
    string medicalHistory;
    string currentTreatment;
    string billingInfo;

public:
    PatientRecord(string pname, string pid, string dob)
        : name(pname), patientID(pid), dateOfBirth(dob), medicalHistory("None"), currentTreatment("None"), billingInfo("No charges") {}

    void getPublicData() const
    {
        cout << "Name: " << name << "\nID: " << patientID << "\nDOB: " << dateOfBirth << endl;
    }

    friend class Doctor;
    friend class Billing;
};

class Doctor
{
public:
    void updateMedicalHistory(PatientRecord &record, const string &history)
    {
        record.medicalHistory = history;
    }

    void updateTreatment(PatientRecord &record, const string &treatment)
    {
        record.currentTreatment = treatment;
    }

    void viewMedicalData(const PatientRecord &record)
    {
        cout << "[Doctor View]\nMedical History: " << record.medicalHistory << "\nCurrent Treatment: " << record.currentTreatment << endl;
    }
};

class Billing
{
public:
    void addBillingDetails(PatientRecord &record, const string &billing)
    {
        record.billingInfo = billing;
    }

    void viewBillingInfo(const PatientRecord &record)
    {
        cout << "[Billing View]\nBilling Info: " << record.billingInfo << endl;
    }
};

class Receptionist
{
public:
    void attemptAccess(const PatientRecord &record)
    {
        cout << "[Receptionist Access Attempt]\n";
        record.getPublicData();
    }
};

int main()
{
    PatientRecord patient("Ilsa", "P-1002", "2005-04-30");

    Doctor doc;
    doc.updateMedicalHistory(patient, "Asthma and seasonal allergies");
    doc.updateTreatment(patient, "Inhaler twice a day");
    doc.viewMedicalData(patient);

    Billing billing;
    billing.addBillingDetails(patient, "$200 - Consultation, $150 - Lab Tests");
    billing.viewBillingInfo(patient);

    Receptionist rec;
    rec.attemptAccess(patient);

    return 0;
}
