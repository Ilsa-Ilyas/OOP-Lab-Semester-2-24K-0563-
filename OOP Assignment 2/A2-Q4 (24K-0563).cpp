#include <iostream>
#include <string>
using namespace std;

#define STUDENT_NAME "Ilsa Ilyas"
#define STUDENT_ID "24K-0563"

// === Global Constants ===
#define MAX_ASSIGNMENTS 5
#define MAX_STUDENTS 10
#define MAX_PROJECTS 2

// === Global Password Hash Function (DJB2) ===
unsigned long hashPassword(string password) {
    unsigned long hash = 5381;
    for (char c : password)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

// === Base User Class ===
class User {
protected:
    string name, id, email;
    unsigned long hashed_password;
    string permissions[5];
    int permissionCount;

public:
    User(string n, string i, string em, string pw) {
        name = n;
        id = i;
        email = em;
        hashed_password = hashPassword(pw);
        permissionCount = 0;
    }

    void addPermission(string perm) {
        if (permissionCount < 5)
            permissions[permissionCount++] = perm;
    }

    virtual void display() {
        cout << "\n[User Info]\n";
        cout << "Name: " << name << "\nID: " << id << "\nEmail: " << email << "\nPermissions: ";
        for (int i = 0; i < permissionCount; i++)
            cout << permissions[i] << ", ";
        cout << "\n";
    }

    bool authenticate(string pw) {
        return hashPassword(pw) == hashed_password;
    }

    virtual void accessLab() {
        for (int i = 0; i < permissionCount; i++) {
            if (permissions[i] == "full_lab_access") {
                cout << name << " has full lab access.\n";
                return;
            }
        }
        cout << name << " has limited or no lab access.\n";
    }

    bool hasPermission(string action) {
        for (int i = 0; i < permissionCount; i++) {
            if (permissions[i] == action)
                return true;
        }
        return false;
    }

    virtual string getRole() const = 0;
};

// === Student Class ===
class Student : public User {
protected:
    int assignments[MAX_ASSIGNMENTS];

public:
    Student(string n, string i, string em, string pw)
        : User(n, i, em, pw) {
        for (int i = 0; i < MAX_ASSIGNMENTS; i++)
            assignments[i] = 0;
        addPermission("submit_assignment");
    }

    void display() override {
        User::display();
        cout << "Assignment Status: ";
        for (int i = 0; i < MAX_ASSIGNMENTS; i++)
            cout << (assignments[i] ? "[?] " : "[ ] ");
        cout << "\n";
    }

    void giveAssignment(int index) {
        if (index >= 0 && index < MAX_ASSIGNMENTS)
            assignments[index] = 0;
    }

    void submitAssignment(int index) {
        if (index >= 0 && index < MAX_ASSIGNMENTS) {
            assignments[index] = 1;
            cout << name << " submitted assignment " << index << "\n";
        }
    }

    string getRole() const override {
        return "STUDENT";
    }
};

// === TA Class ===
class TA : public Student {
    Student* studentList[MAX_STUDENTS];
    int studentCount;
    string projects[MAX_PROJECTS];
    int projectCount;

public:
    TA(string n, string i, string em, string pw)
        : Student(n, i, em, pw) {
        addPermission("view_projects");
        addPermission("manage_students");
        studentCount = 0;
        projectCount = 0;
    }

    void display() override {
        User::display();
        cout << "Assigned Students: " << studentCount << "\n";
        cout << "Projects: ";
        for (int i = 0; i < projectCount; i++)
            cout << projects[i] << ", ";
        cout << "\n";
    }

    void assignStudent(Student* s) {
        if (studentCount < MAX_STUDENTS) {
            studentList[studentCount++] = s;
            cout << "Student assigned to TA " << name << "\n";
        } else {
            cout << "TA already has 10 students.\n";
        }
    }

    void startProject(string projectName) {
        if (projectCount < MAX_PROJECTS) {
            projects[projectCount++] = projectName;
            cout << name << " started project: " << projectName << "\n";
        } else {
            cout << name << " already has 2 projects.\n";
        }
    }

    string* getProjects() { return projects; }
    int getProjectCount() const { return projectCount; }

    string getRole() const override {
        return "TA";
    }
};

// === Professor Class ===
class Professor : public User {
public:
    Professor(string n, string i, string em, string pw)
        : User(n, i, em, pw) {
        addPermission("assign_projects");
        addPermission("full_lab_access");
    }

    void display() override {
        User::display();
    }

    void assignProjectToTA(TA& ta, string projectName) {
        ta.startProject(projectName);
    }

    string getRole() const override {
        return "PROFESSOR";
    }
};

// === Global Function: Authenticate and Perform Action ===
void authenticateAndPerformAction(User* user, string action) {
    if (user->hasPermission(action)) {
        cout << user->getRole() << " is allowed to perform: " << action << "\n";
    } else {
        cout << user->getRole() << " is NOT authorized to perform: " << action << "\n";
    }
}

// === MAIN ===
int main() {
    cout << "Student: " << STUDENT_NAME << " | ID: " << STUDENT_ID << "\n\n";

    Student s1("Ali", "S101", "ali@univ.edu", "studentpass");
    TA ta1("Sara", "T202", "sara@univ.edu", "tapass");
    Professor prof("Dr. Ahmed", "P303", "ahmed@univ.edu", "profpass");

    // Display Info
    s1.display();
    ta1.display();
    prof.display();

    // Authentication
    cout << "\n-- Authentication --\n";
    cout << (s1.authenticate("studentpass") ? "Student login success.\n" : "Login failed.\n");
    cout << (ta1.authenticate("wrongpass") ? "TA login success.\n" : "Login failed.\n");

    // Assignment Submission
    cout << "\n-- Assignments --\n";
    s1.giveAssignment(2);
    s1.submitAssignment(2);
    s1.display();

    // TA Management
    cout << "\n-- TA Assignments & Projects --\n";
    ta1.assignStudent(&s1);
    ta1.startProject("Data Structures");
    ta1.startProject("AI Project");
    ta1.startProject("Extra Project"); // Should not be allowed

    // Professor Assignments
    cout << "\n-- Professor Assigns Project --\n";
    prof.assignProjectToTA(ta1, "Vision System");

    // Access Lab
    cout << "\n-- Lab Access --\n";
    s1.accessLab();
    ta1.accessLab();
    prof.accessLab();

    // Action Permission Checks
    cout << "\n-- Action Permissions --\n";
    authenticateAndPerformAction(&s1, "submit_assignment");
    authenticateAndPerformAction(&ta1, "manage_students");
    authenticateAndPerformAction(&prof, "assign_projects");
    authenticateAndPerformAction(&s1, "assign_projects"); // Should not be allowed

    return 0;
}
