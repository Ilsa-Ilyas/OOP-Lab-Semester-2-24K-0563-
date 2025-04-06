#include <iostream>
#include <string>

using namespace std;

class Course{
	string courseCode;
    string courseName;
    string courseCreditHours;
    bool assigned;

public:
    Course(string code, string name, string credit)
        : courseCode(code), courseName(name), courseCreditHours(credit), assigned(false) {}
    
	string getCourseCode() { return courseCode; }
    string getCourseName() { return courseName; }
    string getCourseCreditHours() { return courseCreditHours; }
    bool isAssigned() { return assigned; }

    void assignCourse() { assigned = true; }
};


class Employee {
protected:
    string employeeName;
    string employeeDesignation;
    string employeeDept;
    int employeeSalary;

public:
    Employee(string name, string desig, string dept, int salary)
        : employeeName(name), employeeDesignation(desig), employeeDept(dept), employeeSalary(salary) {}

    string getName() { return employeeName; }
    string getDesignation() { return employeeDesignation; }
    string getDept() { return employeeDept; }
    int getSalary() { return employeeSalary; }
};


class Faculty : public Employee {
protected:
    int workingHours;
    Course* courseList[10]; 
    int assignedCourseCount;

public:
    Faculty(string name, string desig, string dept, int salary, int hours)
        : Employee(name, desig, dept, salary) {
        workingHours = hours;
        assignedCourseCount = 0;
    }