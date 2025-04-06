class Staff : public Employee {
private:
    int overtimeHours;

public:
    Staff(string name, string desig, string dept, int salary, int overtime)
        : Employee(name, desig, dept, salary), overtimeHours(overtime) {}

    // ? Verify department match
    bool Verify(string departmentName) {
        return (employeeDept == departmentName);
    }

    // ? Verify salary within range
    bool Verify(int lowerLimit, int upperLimit) {
        return (employeeSalary >= lowerLimit && employeeSalary <= upperLimit);
    }
};