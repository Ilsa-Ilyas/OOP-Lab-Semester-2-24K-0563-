#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
    string name;
    string ID;
    double salary;

public:
    Employee(string n, string id, double s) {
        name = n;
        ID = id;
        salary = s;
    }
};

class Analyst : virtual public Employee {
private:
    string specialization;
    bool isCertified;
    string certificationName;

public:
    Analyst(string n, string id, double s, string spec, bool cert, string certName = "")
        : Employee(n, id, s) {
        if (spec == "Network" || spec == "Incident Response" || spec == "Threat Intelligence") {
            specialization = spec;
        } else {
            specialization = "Invalid Specialization";
        }

        isCertified = cert;
        certificationName = certName;
    }

    void HasCertifications() {
        cout << "Specialization: " << specialization << endl;
        if (isCertified && !certificationName.empty()) {
            cout << "Certified in: " << certificationName << endl;
        } else {
            cout << "Not Certified" << endl;
        }
    }
};

class Engineer : virtual public Employee {
protected:
    bool isExpert;
    bool isAssigned;
    string* projects;
    int prjcount;
    int capacity;

public:
    Engineer(string n, string id, double s, bool expert, int cap = 5)
        : Employee(n, id, s) {
        isExpert = expert;
        isAssigned = false;
        capacity = cap;
        prjcount = 0;
        projects = new string[capacity];
    }

    void AssignProject() {
        if (isExpert) {
            isAssigned = true;
