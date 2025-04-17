#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    virtual void getData() {
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cin.ignore();
    }

    virtual void displayData() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    virtual void bonus() {
        cout << "No bonus for base Person class.\n";
    }

    virtual ~Person() {}
};

class Admin : virtual public Person {
protected:
    double salary;

public:
    void getData() override {
        Person::getData();
        cout << "Enter Admin salary: ";
        cin >> salary;
        cin.ignore();
    }

    void displayData() override {
        Person::displayData();
        cout << "Admin Salary: $" << salary << endl;
    }

    void bonus() override {
        cout << "Admin Bonus: $" << salary * 0.10 << endl;
    }
};

class Account : virtual public Person {
protected:
    double accountBalance;

public:
    void getData() override {
        Person::getData();
        cout << "Enter Account balance: ";
        cin >> accountBalance;
        cin.ignore();
    }

    void displayData() override {
        Person::displayData();
        cout << "Account Balance: $" << accountBalance << endl;
    }

    void bonus() override {
        cout << "Account Bonus: $" << accountBalance * 0.05 << endl;
    }
};

class Master : public Admin, public Account {
public:
    void getData() override {
        Person::getData();
        cout << "Enter Admin salary: ";
        cin >> salary;
        cout << "Enter Account balance: ";
        cin >> accountBalance;
        cin.ignore();
    }

    void displayData() override {
        Person::displayData();
        cout << "Admin Salary: $" << salary << ", Account Balance: $" << accountBalance << endl;
    }

    void bonus() override {
        double totalBonus = (salary * 0.10) + (accountBalance * 0.05);
        cout << "Master Bonus: $" << totalBonus << endl;
    }
};

int main() {
    Person* ptr;

    cout << "--- Master Employee ---\n";
    Master m;
    ptr = &m;
    ptr->getData();
    ptr->displayData();
    ptr->bonus();

    return 0;
}
