#include <iostream>
#include <string>

class Member {
protected:
    int memberId;
public:
    void setId(int id) {
        memberId = id;
    }

    void showId() {
        std::cout << "Member ID: " << memberId << std::endl;
    }
};

class Manager : public Member {
private:
    std::string fullName;
    double monthlySalary;
public:
    void setData(int id, const std::string& name, double salary) {
        Member::setId(id);
        fullName = name;
        monthlySalary = salary;
    }

    void displayInfo() {
        Member::showId();
        std::cout << "Name: " << fullName 
                  << "\nSalary: " << monthlySalary 
                  << "\nYearly Bonus: " << monthlySalary * 0.05 * 12 << std::endl;
    }
};

class Finance : public Member {
private:
    std::string fullName;
    double monthlySalary;
public:
    void setData(int id, const std::string& name, double salary) {
        Member::setId(id);
        fullName = name;
        monthlySalary = salary;
    }

    void displayInfo() {
        Member::showId();
        std::cout << "Name: " << fullName 
                  << "\nSalary: " << monthlySalary 
                  << "\nYearly Bonus: " << monthlySalary * 0.05 * 12 << std::endl;
    }
};

int main() {
    Manager teamLead;
    teamLead.setData(101, "Ali Khan", 5000);
    teamLead.displayInfo();

    Finance accountant;
    accountant.setData(102, "Sara Ahmed", 4500);
    accountant.displayInfo();

    return 0;
}
