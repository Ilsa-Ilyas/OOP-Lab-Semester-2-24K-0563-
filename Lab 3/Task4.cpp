#include <iostream>
#include <string>
using namespace std;
class Employee
{
private:
    string firstName;
    string lastName;
    double salary;

public:
    void setDetails(string n, string l, double s)
    {
        firstName = n;
        lastName = l;
        if (s < 0.0)
        {
            salary = 0.0;
        }
        else
        {
            salary = s;
        }
    };
    void getSalary()
    {
        cout << "\n Yearly Salary : " << salary * 12;
        cout << "\n After 10% Raise : " << (salary * 12) * 1.1;
    };
};


int main(int argc, char const *argv[])
{
    Employee e[2];
    e[0].setDetails(argv[1], argv[2], stod(argv[3]));
    e[1].setDetails(argv[4], argv[5], stod(argv[6]));
    cout << "\n Employee 1 salary : ";
    e[0].getSalary();
    cout << "\n Employee 2 salary : ";
    e[1].getSalary();
    return 0;
}