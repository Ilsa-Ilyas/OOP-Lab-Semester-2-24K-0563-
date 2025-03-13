#include <iostream>
#include <string>

using namespace std;

// Department class to represent each university department
class Department {
private:
    const string name;      // Department name, constant once assigned and cannot be changed
    static int totaldept;   // Static variable to track total number of departments

public:
    // Constructor to initialize the department name and increment the department count
    Department(const string& deptname) : name(deptname) {
        totaldept++;
    }

    // Destructor to decrement the department count upon object deletion
    ~Department() {
        totaldept--;
    }

    // Getter function to return the department name
    string getname() const {
        return name;
    }

    // Static function to get the total number of active departments
    static int gettotaldept() {
        return totaldept;
    }
};

// Definition and initialization of the static member for Department class
int Department::totaldept = 0;

// Professor class to represent each professor and their respective department
class Professor {
private:
    static int nextprofessorID;   // Static variable to auto-increment and assign unique professor IDs
    static int totalprofessors;   // Static variable to track total number of professors
    const int ID;                 // Unique ID for each professor, constant once assigned
    const string name;            // Professor's name, constant once assigned and cannot be changed
    Department* const department; // Pointer to the assigned department, fixed after assignment

public:
    // Constructor to initialize professor details and increment professor count
    Professor(const string& profName, Department* dept)
        : ID(nextprofessorID++), name(profName), department(dept) {
        totalprofessors++;
    }

    // Destructor to decrement the professor count upon object deletion
    ~Professor() {
        totalprofessors--;
    }

    // Function to display the details of the professor
    void displayDetails() const {
        cout << "Professor ID: " << ID << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department->getname() << endl;
    }

    // Static function to return the total number of active professors
    static int gettotalprofessors() {
        return totalprofessors;
    }
};

// Definition and initialization of static members for the Professor class
int Professor::nextprofessorID = 1;
int Professor::totalprofessors = 0;

int main() {
    // Dynamically creating department objects
    Department* csDept = new Department("Computer Science");
    Department* cyDept = new Department("Cyber Security");

    // Displaying total departments after creation
    cout << "Total Departments: " << Department::gettotaldept() << endl;

    // Dynamically creating professor objects and assigning them to respective departments
    Professor* p1 = new Professor("LALA", csDept);
    Professor* p2 = new Professor("VAVA", cyDept);

    // Displaying total professors after creation
    cout << "Total Professors: " << Professor::gettotalprofessors() << endl;

    // Displaying detailed information of each professor
    cout << "\nProfessor Details: " << endl;
    p1->displayDetails();
    p2->displayDetails();

    // Deleting professors and updating the total count
    delete p1;
    delete p2;
    cout << "Total Professors Now: " << Professor::gettotalprofessors() << endl;

    // Deleting departments and updating the total count
    delete csDept;
    delete cyDept;
    cout << "Total Departments Now: " << Department::gettotaldept() << endl;

    return 0;
}



