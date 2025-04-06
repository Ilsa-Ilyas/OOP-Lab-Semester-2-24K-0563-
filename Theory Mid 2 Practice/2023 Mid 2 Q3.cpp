class Employee {
protected:
    string employeeName;
    string employeeDesignation;
    string employeeDept;
    int employeeSalary;

public:
    Employee(string name, string desig, string dept, int salary)
        : employeeName(name), employeeDesignation(desig), employeeDept(dept), employeeSalary(salary) {}
        
 // Post-increment overload: increase salary by 10% and return the new salary       
int operator++(int) {
	employeeSalary+=employeeSalary*0.10;
	return employeeSalary;
}


class Faculty : public Employee {
protected:
    int workingHours;
    Course* courseList[10]; 
    int assignedCourseCount;

public:
    Faculty(string name, string desig, string dept, int salary, int hours)
        : Employee(name, desig, dept, salary)
        workingHours = hours;
        
// Post-increment overload: 20% salary increase + designation change
    Faculty operator++(int) {
        Faculty temp = *this; // store current object
        
		// Increase salary by 20%
        employeeSalary += employeeSalary * 0.20;

        // Update designation
        if (employeeDesignation == "Lecturer")
            employeeDesignation = "Instructor";
        else if (employeeDesignation == "Instructor")
            employeeDesignation = "Assistant Professor";

        return temp;
    }
};
	

class Staff : public Employee {
private:
    int overTimeHours;

public:
    Staff(string name, string desig, string dept, int salary, int ot)
        : Employee(name, desig, dept, salary), overTimeHours(ot) {}

    // Overload + operator for Staff + Faculty
    friend int operator+(const Staff& s, const Faculty& f);
};

int operator+(const Staff& s, const Faculty& f) {
    return s.employeeSalary + f.employeeSalary;
}
        
