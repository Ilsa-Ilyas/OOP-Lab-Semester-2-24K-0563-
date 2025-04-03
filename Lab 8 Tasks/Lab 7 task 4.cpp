#include<iostream>
#include<string>
using namespace std;

// Base class representing a person
class Person {
protected:
    string name;
    string id;
    string address;
    string email;
    string phonenum;

public:
    Person(string a, string b, string c, string d, string e) 
        : name(a), id(b), address(c), email(d), phonenum(e) {}

    virtual void displaydetails() {
        cout << "Person Details" << endl;
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
        cout << "Phone Number: " << phonenum << endl;
    }

    void updatedetails(string a, string b, string c, string d, string e) {
        name = a;
        id = b;
        address = c;
        email = d;
        phonenum = e;
    }
};

// Student derived from Person
class Student : public Person {
    int coursesEnrolled;
    float GPA;
    int EnrollmentYear;

public:
    Student(string a, string b, string c, string d, string e, int f, float g, int h) 
        : Person(a, b, c, d, e), coursesEnrolled(f), GPA(g), EnrollmentYear(h) {}

    void displaydetails() override {
        cout << "Student Details" << endl;
        Person::displaydetails();
        cout << "Courses Enrolled: " << coursesEnrolled << endl;
        cout << "GPA: " << GPA << endl;
        cout << "Enrollment Year: " << EnrollmentYear << endl;
    }

    string get_name() {
        return name;
    }
};

// Professor derived from Person
class Professor : public Person {
    string department;
    int coursestaught;
    float salary;

public:
    Professor(string a, string b, string c, string d, string e, string f, int g, float h) 
        : Person(a, b, c, d, e), department(f), coursestaught(g), salary(h) {}

    void displaydetails() override {
        cout << "Professor Details" << endl;
        Person::displaydetails();
        cout << "Department: " << department << endl;
        cout << "Courses Taught: " << coursestaught << endl;
        cout << "Salary: " << salary << endl;
    }
};

// Staff derived from Person
class Staff : public Person {
    string department;
    string position;
    float salary;

public:
    Staff(string a, string b, string c, string d, string e, string f, string g, float h) 
        : Person(a, b, c, d, e), department(f), position(g), salary(h) {}

    void displaydetails() override {
        cout << "Staff Details" << endl;
        Person::displaydetails();
        cout << "Department: " << department << endl;
        cout << "Position: " << position << endl;
        cout << "Salary: " << salary << endl;
    }
};

// Course class
class Course {
    string courseId;
    string courseName;
    int credits;
    string instructor;
    string schedule;

public:
    Course(string id, string name, int cred, string instr, string sched) 
        : courseId(id), courseName(name), credits(cred), instructor(instr), schedule(sched) {}

    void registerStudent(Student& s) {
        cout << "Student " << s.get_name() << " registered for " << courseName << endl;
    }

    void calculateGrades() {
        cout << "Grades calculated for course " << courseName << endl;
    }

    void displayCourseInfo() {
        cout << "Course ID: " << courseId << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Credits: " << credits << endl;
        cout << "Instructor: " << instructor << endl;
        cout << "Schedule: " << schedule << endl;
    }
};

int main() {
    // Updated names and data
    Student student1("Ayaan Khan", "S2001", "12 Beacon St", "ayaan@college.edu", "0300-1234567", 6, 3.9, 2021);
    Professor professor1("Dr. Amna Raza", "P3501", "89 Elm Dr", "amna@college.edu", "0315-6543210", "Mathematics", 3, 85000);
    Staff staff1("Bilal Ahmed", "ST4021", "23 Admin Lane", "bilal@college.edu", "0345-7891234", "Facilities", "Supervisor", 48000);
    Course course1("MATH204", "Linear Algebra", 3, "Dr. Amna Raza", "Tue/Thu 9-10:30");

    // Display details
    student1.displaydetails();
    cout << "--------------------------\n";
    professor1.displaydetails();
    cout << "--------------------------\n";
    staff1.displaydetails();
    cout << "--------------------------\n";

    // Course information and operations
    course1.displayCourseInfo();
    course1.registerStudent(student1);
    course1.calculateGrades();

    return 0;
}
