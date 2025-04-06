void AssignCourse(Course allCourses[]), int size{
	for(int i=0; i<size; ++i){
	    if (!allCourses[i].isAssigned()) {
                string code = allCourses[i].getCourseCode();
                char firstLetter = code[0];

    if ((employeeDept == "Computer Science" && firstLetter == 'C') ||
                    (employeeDept == "Management Science" && firstLetter == 'M') ||
                    (employeeDept == "Electrical Engineering" && firstLetter == 'E')) {
                    
                    // Assign course
                    courseList[assignedCourseCount++] = &allCourses[i];
                    totalCreditHours += allCourses[i].getCourseCreditHours();
                    allCourses[i].assignCourse();

                    cout << "Assigned course: " << code << " to " << employeeName << endl;

                    // Warning if > 12 credit hours
                    if (totalCreditHours > 12) {
                        cout << "?? Warning: Total assigned credit hours exceed 12!" << endl;
                    }
                    return; // assign one per call
                }
            }
        }
        cout << "No matching course available to assign.\n";
    }
    
void Salary() {
	cout << "Calculating Salary for: "<<employeeName<<endl;
	if (workingHours == 36) {
            cout << "Current Salary: Rs. " << employeeSalary << endl;
        } else if (workingHours > 36) {
            int extra = workingHours - 36;
            int updatedSalary = employeeSalary + (extra * 1000);
            cout << "Updated Salary (with " << extra << " extra hours): Rs. " << updatedSalary << endl;
        } else {
            cout << "Working hours less than 36. Salary remains: Rs. " << employeeSalary << endl;
        }
    }
}