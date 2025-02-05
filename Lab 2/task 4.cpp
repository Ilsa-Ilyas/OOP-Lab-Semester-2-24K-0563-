#include <iostream>
#include <cstring>
using namespace std;

struct Organisation
{
    string organsation_name;
    string organisation_number;

    struct Employee
    {
        int employee_id;
        string name;
        float salary;
    } emp;
};

int main()
{
    Organisation org;

    org.organisation_number = "123";
    org.organsation_name = "NU-FAST";
    org.organisation_number = "NUFAST123ABC";
    org.emp.employee_id = 127;
    org.emp.name = "Linus Sebastian";
    org.emp.salary = 400000;

    cout << "The size of structure organisation : " << sizeof(org) << " bytes" << endl;
    cout << "Organisation Name: " << org.organsation_name << endl;
    cout << "Organsation Number: " << org.organisation_number << endl;
    cout << "Employee ID: " << org.emp.employee_id << endl;
    cout << "Employee Name: " << org.emp.name << endl;
    cout << "Employee Salary: " << org.emp.salary << endl;

    return 0;
}
