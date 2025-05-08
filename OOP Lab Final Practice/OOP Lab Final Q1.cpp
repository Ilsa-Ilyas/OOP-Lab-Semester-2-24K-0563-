#include <iostream>
#include <string>
using namespace std;

// Forward declaration of AcademicAudit class
class AcademicAudit;

// Base class: Staff
class Staff {
protected:
    string StaffID;  // Unique staff identifier
    string name;     // Full name of the staff member

public:
    Staff(string id, string n) {
        StaffID = id;
        name = n;
    }

    virtual void displayinfo() {
        cout << "Staff Name: " << name << endl;
        cout << "Staff ID: " << StaffID << endl;
    }
};

// Forward declaration for friend function
class Lecturer;
void update(Lecturer& l, int hours, float feedback);

// Lecturer class
class Lecturer : virtual public Staff {
protected:
    int teachinghours;
    float studentFeedback;

public:
    Lecturer(string id, string n, int hours, float feedback)
        : Staff(id, n) {
        teachinghours = hours;
        studentFeedback = feedback;
    }

    void displayinfo() override {
        cout << "\n--- Lecturer Info ---\n";
        cout << "Staff Name: " << name << endl;
        cout << "Staff ID: " << StaffID << endl;
        cout << "Teaching Hours: " << teachinghours << endl;
        cout << "Student Feedback: " << studentFeedback << endl;
    }

    friend void update(Lecturer& l, int hours, float feedback);
    friend class AcademicAudit;
};

void update(Lecturer& l, int hours, float feedback) {
    if (feedback >= 0.0 && feedback <= 5.0) {
        l.studentFeedback = feedback;
    } else {
        cout << "Invalid feedback: must be in range 0–5!" << endl;
    }

    if (hours < 0) {
        cout << "Invalid! Must work at least 0 hours." << endl;
    } else if (hours > 8) {
        cout << "Invalid! Must not work more than 8 hours." << endl;
    } else {
        l.teachinghours = hours;
    }
}

// Forward declaration for CourseCoordinator update
class CourseCoordinator;
void update(CourseCoordinator& C, int cm, float cr);

// CourseCoordinator class
class CourseCoordinator : virtual public Staff {
protected:
    int coursesManaged;
    float curriculumRating;

public:
    CourseCoordinator(string id, string n, int cm, float cr)
        : Staff(id, n) {
        coursesManaged = cm;
        curriculumRating = cr;
    }

    void displayinfo() override {
        cout << "\n--- Course Coordinator Info ---\n";
        cout << "Staff Name: " << name << endl;
        cout << "Staff ID: " << StaffID << endl;
        cout << "Courses Managed: " << coursesManaged << endl;
        cout << "Curriculum Rating: " << curriculumRating << endl;
    }

    friend void update(CourseCoordinator& C, int cm, float cr);
    friend class AcademicAudit;
};

void update(CourseCoordinator& C, int cm, float cr) {
    if (cm >= 1) {
        C.coursesManaged = cm;
    } else {
        cout << "Invalid! Courses managed must be at least 1." << endl;
    }

    if (cr >= 0.0 && cr <= 10.0) {
        C.curriculumRating = cr;
    } else {
        cout << "Invalid curriculum rating: must be between 0 and 10!" << endl;
    }
}

// DualRoleStaff class
class DualRoleStaff : public Lecturer, public CourseCoordinator {
private:
    float score;

public:
    DualRoleStaff(string id, string n, int cm, float cr, int hours, float feedback)
        : Staff(id, n), Lecturer(id, n, hours, feedback), CourseCoordinator(id, n, cm, cr) {
        score = studentFeedback * 2 + curriculumRating;
    }

    void displayinfo() override {
        cout << "\n--- Dual Role Staff Info ---\n";
        cout << "Staff Name: " << name << endl;
        cout << "Staff ID: " << StaffID << endl;
        cout << "Courses Managed: " << coursesManaged << endl;
        cout << "Curriculum Rating: " << curriculumRating << endl;
        cout << "Teaching Hours: " << teachinghours << endl;
        cout << "Student Feedback: " << studentFeedback << endl;
        cout << "Combined Performance Score: " << score << endl;
    }
};

// AcademicAudit class
class AcademicAudit {
public:
    void inspectL(const Lecturer& l) {
        cout << "\n[Academic Audit] Lecturer Metrics:\n";
        cout << "Teaching Hours: " << l.teachinghours << endl;
        cout << "Student Feedback: " << l.studentFeedback << endl;
    }

    void inspectCoordinator(const CourseCoordinator& c) {
        cout << "\n[Academic Audit] Course Coordinator Metrics:\n";
        cout << "Courses Managed: " << c.coursesManaged << endl;
        cout << "Curriculum Rating: " << c.curriculumRating << endl;
    }
};

int main() {
    Lecturer l1("01", "Dr. Ali", 3, 4.7);               // Valid feedback
    CourseCoordinator c1("02", "Prof. Fatima", 3, 6.9);
    DualRoleStaff d1("03", "Dr. Sara", 5, 8.5, 4, 4.2); // Valid all

    l1.displayinfo();
    c1.displayinfo();
    d1.displayinfo();

    AcademicAudit audit;
    audit.inspectL(l1);
    audit.inspectCoordinator(c1);

    return 0;
}
