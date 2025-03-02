#include <iostream>
#include <string>
using namespace std;

class Mentor;
class Student;

class Skill {
private:
    string skillID;
    string skillName;
    string description;

public:
    Skill() = default; 

    void initialize(string id, string sn, string sd) {
        skillID = id;
        skillName = sn;
        description = sd;
    }

    void setSkillID(string nid) { skillID = nid; }
    void setSkillName(string nsn) { skillName = nsn; }
    void setDescription(string nsd) { description = nsd; }

    string getSkillID() { return skillID; }
    string getSkillName() { return skillName; }
    string getDescription() { return description; }

    void showSkillDetails() {
        cout << "Skill ID: " << skillID << "\nSkill Name: " << skillName 
             << "\nDescription: " << description << endl;
    }

    void updateSkillDescription(string newDescription) {
        description = newDescription;
    }
};

class Sport {
private:
    string sportID;
    string name;
    string description;
    Skill* requiredSkills[20] = {nullptr};  
    int numSkills = 0;

public:
    Sport() = default;

    void initialize(string sid, string sn, string d) {
        sportID = sid;
        name = sn;
        description = d;
        numSkills = 0;
    }

    void viewAllDetails() {
        cout << "ID: " << sportID << "\nName: " << name 
             << "\nDescription: " << description << "\nSkills required:\n";
        for (int i = 0; i < numSkills; i++) {
            if (requiredSkills[i] != nullptr) {
                requiredSkills[i]->showSkillDetails();
            }
        }
    }

    void setSportID(string nid) { sportID = nid; }
    void setName(string Nn) { name = Nn; }
    void setDescription(string nd) { description = nd; }

    string getSportID() { return sportID; }
    string getName() { return name; }
    string getDescription() { return description; }

    void addSkill(Skill* s) {
        if (numSkills < 20) {
            requiredSkills[numSkills++] = s;
            cout << "Skill added to " << name << endl;
        } else {
            cout << "Maximum skills reached for " << name << endl;
        }
    }

    void removeSkill(Skill* s) {
    if (numSkills == 0) {
        cout << "No skills to remove." << endl;
        return;
    }

    if (s == nullptr) {
        cout << "Invalid skill!" << endl;
        return;
    }

    for (int i = 0; i < numSkills; i++) {
        if (requiredSkills[i] != nullptr && s->getSkillID() == requiredSkills[i]->getSkillID()) {
            for (int j = i; j < numSkills - 1; j++) {
                requiredSkills[j] = requiredSkills[j + 1];
            }
            requiredSkills[--numSkills] = nullptr;
            cout << "Skill removed from " << name << endl;
            return;
        }
    }
    cout << "Skill not found." << endl;
}
};

class Mentor {
private:
    string mentorID;
    string name;
    Sport* sportsExpertise[4] = {nullptr}; 
    int numExpertise = 0;
    int maxLearners = 0; 
    Student* assignedLearners[30] = {nullptr};  
    int numLearners = 0; 

public:
    Mentor() = default;

    void initialize(string id, string n, int ml) {
    mentorID = id;
    name = n;
    maxLearners = (ml > 0) ? ml : 0;
    numExpertise = 0;
    numLearners = 0;

    for (int i = 0; i < 4; i++) {
        sportsExpertise[i] = nullptr; 
    }
    for (int i = 0; i < 30; i++) {
        assignedLearners[i] = nullptr; 
    }
}

    string getMentorID() { return mentorID; }
    string getMentorName() { return name; }
    int getMaxLearners() { return maxLearners; }

    void setMentorID(string mid) { mentorID = mid; }
    void setMentorName(string n) { name = n; }
    
    void setMaxLearner(int Max) {
        if (Max > 0) {
            maxLearners = Max;
        } else {
            cout << "Max learners must be greater than 0." << endl;
        }
    }

    void addExpertise(Sport* s) {
        if (numExpertise < 4) {
            sportsExpertise[numExpertise++] = s;
        } else {
            cout << "Maximum 4 expertise allowed. Remove one to add a new one." << endl;
        }
    }

    void viewAllExpertise() {
        for (int i = 0; i < numExpertise; i++) {
            if (sportsExpertise[i] != nullptr) {
                sportsExpertise[i]->viewAllDetails();
            }
        }
    }

    void removeExpertise(Sport* s) {
        for (int i = 0; i < numExpertise; i++) {
            if (sportsExpertise[i] != nullptr && s->getSportID() == sportsExpertise[i]->getSportID()) {
                for (int j = i; j < numExpertise - 1; j++) {
                    sportsExpertise[j] = sportsExpertise[j + 1];
                }
                sportsExpertise[--numExpertise] = nullptr;
                cout << "Expertise removed." << endl;
                return;
            }
        }
        cout << "Expertise not found." << endl;
    }

    void provideGuidance() {
        cout << "Providing guidance" << endl;
    }

    int assignLearner(Student* s);
    void removeLearner(Student* s);
    void viewLearners();
};

class Student {
private:
    string name;
    string studentID;
    int age;
    Sport* sportsInterests[4] = {nullptr}; 
    int numInterests = 0;  
    Mentor* mentorAssigned = nullptr;

public:
    Student() = default;

    Student(string n, string id, int a)
        : name(n), studentID(id), age(a), numInterests(0), mentorAssigned(nullptr) {}

	void initialize(string n, string id, int a) {
    name = n;
    studentID = id;
    age = a;
    numInterests = 0;
    mentorAssigned = nullptr;
    
    for (int i = 0; i < 4; i++) {
        sportsInterests[i] = nullptr;
    }
}

    string getName() { return name; }
    string getID() { return studentID; }
    int getAge() { return age; }

    void setName(string n) { name = n; }
    void setID(string id) { studentID = id; }
    void setAge(int a) { age = a; }

    void viewAllInterests() {
        if (numInterests == 0) {
            cout << name << " has not added any sports interests yet." << endl;
            return;
        }

        cout << "Sports interests for " << name << ":" << endl;
        for (int i = 0; i < numInterests; i++) {
            if (sportsInterests[i] != nullptr) {
                sportsInterests[i]->viewAllDetails();
            }
        }
    }

    void addSport(Sport* s) {
        if (s == nullptr) {
            cout << "Invalid sport!" << endl;
            return;
        }
        if (numInterests < 4) {
            sportsInterests[numInterests++] = s;
            cout << "Added sport interest: " << s->getName() << endl;
        } else {
            cout << "Cannot add more than 4 sports." << endl;
        }
    }

    void removeSport(Sport* s) {
    if (numInterests == 0) {
        cout << "No sports to remove." << endl;
        return;
    }

    if (s == nullptr) {
        cout << "Invalid sport!" << endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < numInterests; i++) {
        if (sportsInterests[i] != nullptr && s->getSportID() == sportsInterests[i]->getSportID()) {
            found = true;
            for (int j = i; j < numInterests - 1; j++) {
                sportsInterests[j] = sportsInterests[j + 1];
            }
            sportsInterests[--numInterests] = nullptr; 
            cout << "Sport removed: " << s->getName() << endl;
            return;
        }
    }

    if (!found) {
        cout << "Sport not found in interests." << endl;
    }
}


    void updateSportsInterest(Sport* s) {
    if (s == nullptr) {
        cout << "Invalid sport!" << endl;
        return;
    }

    int choice;
    cout << "Update options:\n 1) Add interest\n 2) Remove interest \nOption: ";
    cin >> choice;

    if (choice == 1) {
        addSport(s);
    } else if (choice == 2) {
        removeSport(s);
    } else {
        cout << "Invalid option." << endl;
    }
}

    void registerForMentorship(Mentor* m);
    void viewMentorDetails();
};

void Mentor::removeLearner(Student* s) {
    if (numLearners == 0) {
        cout << "No learners to remove." << endl;
        return;
    }

    if (s == nullptr) {
        cout << "Invalid student!" << endl;
        return;
    }

    for (int i = 0; i < numLearners; i++) {
        if (assignedLearners[i] != nullptr && assignedLearners[i]->getID() == s->getID()) {
            for (int j = i; j < numLearners - 1; j++) {
                assignedLearners[j] = assignedLearners[j + 1]; 
            }
            assignedLearners[--numLearners] = nullptr;
            cout << "Learner removed successfully." << endl;
            return;
        }
    }
    cout << "Learner not found." << endl;
}

int Mentor::assignLearner(Student* s) {
    if (numLearners < maxLearners) { 
        assignedLearners[numLearners++] = s;
        cout << "Student assigned!" << endl;
        return 1;
    }
    cout << "Max learners already." << endl;
    return 0;
}

void Mentor::viewLearners() {
    if (numLearners == 0) {
        cout << "No learners assigned yet." << endl;
        return;
    }

    cout << "Mentor: " << name << " has " << numLearners << " learners:\n";
    for (int i = 0; i < numLearners; i++) {
        if (assignedLearners[i] != nullptr) {
            cout << "Student " << i + 1 << ":" << endl;
            cout << "Student ID: " << assignedLearners[i]->getID() << endl;
            cout << "Name: " << assignedLearners[i]->getName() << endl;
            cout << "Age: " << assignedLearners[i]->getAge() << endl;
            cout << "Interests: ";
            assignedLearners[i]->viewAllInterests();
            cout << endl;
        }
    }
}

void Student::registerForMentorship(Mentor* m) {
    if (m == nullptr) {
        cout << "Invalid!" << endl;
        return;
    }

    if (mentorAssigned == nullptr) {
        if (m->assignLearner(this)) {
            mentorAssigned = m;
            cout << "Mentor assigned!" << endl;
        } else {
            cout << "Cannot register, already full." << endl;
        }
    } else {
        cout << "Mentor assigned already. Do you want to update? (1. Yes, 2. No): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            mentorAssigned->removeLearner(this); 
            if (m->assignLearner(this)) {
                mentorAssigned = m;
                cout << "Mentor updated!" << endl;
            } else {
                cout << "Can't update'. Class is full." << endl;
            }
        } else {
            cout << "Mentor remains unchanged." << endl;
        }
    }
}

void Student::viewMentorDetails() {
    if (mentorAssigned == nullptr) {
        cout << "No mentor assigned." << endl;
        return;
    }

    cout << "Mentor Details:\n";
    cout << "Mentor ID: " << mentorAssigned->getMentorID() << endl;
    cout << "Name: " << mentorAssigned->getMentorName() << endl;
    cout << "Expertise of Mentor:\n";
    mentorAssigned->viewAllExpertise();
    cout << "Maximum Mentors: " << mentorAssigned->getMaxLearners() << endl;
}

void displaySkills(Skill skills[], int size) {
    cout << "\n--- Skills ---\n" << endl;
    if (size == 0) {
        cout << "No skills available.\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        cout << "ID: " << skills[i].getSkillID() 
             << "\tName: " << skills[i].getSkillName()
             << "\tDescription: " << skills[i].getDescription() << endl;
    }
}

void displaySports(Sport sports[], int size) {
    cout << "\n--- Sports ---\n" << endl;
    if (size == 0) {
        cout << "No sports available.\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        cout << "ID: " << sports[i].getSportID() 
             << "\tName: " << sports[i].getName()
             << "\tDescription: " << sports[i].getDescription() << endl;
    }
}

void displayMentors(Mentor mentors[], int size) {
    cout << "\n--- Mentors ---\n" << endl;
    if (size == 0) {
        cout << "No mentors available.\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        cout << "ID: " << mentors[i].getMentorID() 
             << "\tName: " << mentors[i].getMentorName()
             << "\tMax Learners: " << mentors[i].getMaxLearners() << endl;
    }
}

void displayStudents(Student students[], int size) {
    cout << "\n--- Students ---\n" << endl;
    if (size == 0) {
        cout << "No students available.\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        cout << "ID: " << students[i].getID() 
             << "\tName: " << students[i].getName()
             << "\tAge: " << students[i].getAge() << endl;
    }
}

int main() {
    cout << "=====================================\n";
    cout << "Welcome to the Sport Mentorship System\n";
    cout << "=====================================\n";

    Skill skills[6];
    skills[0].initialize("S1", "Serve", "An overhead shot in tennis.");
    skills[1].initialize("S2", "Dribble", "Bouncing the ball in basketball.");
    skills[2].initialize("S3", "Curve Kick", "A technique in football.");
    skills[3].initialize("S4", "Layup", "A one-handed shot near the hoop.");
    skills[4].initialize("S5", "Tackle", "A defensive move in football.");
    skills[5].initialize("S6", "Volley", "Hitting the ball before it bounces.");

    Sport sports[3];
    sports[0].initialize("SP1", "Badminton", "A racket sport played with a shuttlecock.");
    sports[1].initialize("SP2", "Cricket", "A bat-and-ball game.");
    sports[2].initialize("SP3", "Hockey", "A team sport played with a stick and ball.");

    Mentor mentors[3];
    mentors[0].initialize("M1", "Coach Zain Khan", 2);
    mentors[1].initialize("M2", "Coach Aisha Malik", 3);
    mentors[2].initialize("M3", "Coach Omar Sheikh", 4);

    Student students[3];
    students[0].initialize("Hassan", "ST1", 16);
    students[1].initialize("Ayesha", "ST2", 17);
    students[2].initialize("Bilal", "ST3", 18);

    while (true) {
        int choice;
        cout << "\n=========================\n";
        cout << "1. Skills Menu\n";
        cout << "2. Sports Menu\n";
        cout << "3. Student Menu\n";
        cout << "4. Mentor Menu\n";
        cout << "5. View All Data\n";
        cout << "6. Exit\n";
        cout << "=========================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 6) {
            cout << "Exiting program...\n";
            break;
        }

        switch (choice) {
            case 1: {
                cout << "\n--- Skills Menu ---\n";
                cout << "1. Display Skill Details\n";
                cout << "2. Update Skill Description\n";
                cout << "3. Exit\n";
                cout << "Enter your choice: ";
                int skillChoice;
                cin >> skillChoice;

                if (skillChoice == 3) break;

                string skillID;
                cout << "Enter Skill ID: ";
                cin >> skillID;

                for (int i = 0; i < 6; i++) {
                    if (skills[i].getSkillID() == skillID) {
                        if (skillChoice == 1) {
                            skills[i].showSkillDetails();
                        } else if (skillChoice == 2) {
                            string newDesc;
                            cout << "Enter new description: ";
                            cin.ignore();
                            getline(cin, newDesc);
                            skills[i].updateSkillDescription(newDesc);
                            cout << "Skill description updated!\n";
                        }
                        break;
                    }
                }
                break;
            }

            case 2: {
                cout << "\n--- Sports Menu ---\n";
                cout << "1. Add a Skill\n";
                cout << "2. Remove a Skill\n";
                cout << "3. Exit\n";
                cout << "Enter your choice: ";
                int sportChoice;
                cin >> sportChoice;

                if (sportChoice == 3) break;

                string sportID;
                cout << "Enter Sport ID: ";
                cin >> sportID;

                for (int i = 0; i < 3; i++) {
                    if (sports[i].getSportID() == sportID) {
                        string skillID;
                        cout << "Enter Skill ID: ";
                        cin >> skillID;

                        for (int j = 0; j < 6; j++) {
                            if (skills[j].getSkillID() == skillID) {
                                if (sportChoice == 1) {
                                    sports[i].addSkill(&skills[j]);
                                } else if (sportChoice == 2) {
                                    sports[i].removeSkill(&skills[j]);
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }

            case 3: {
                cout << "\n--- Student Menu ---\n";
                cout << "1. Register for Mentorship\n";
                cout << "2. View Mentor Details\n";
                cout << "3. Update Sports Interests\n";
                cout << "4. Exit\n";
                cout << "Enter your choice: ";
                int studentChoice;
                cin >> studentChoice;

                if (studentChoice == 4) break;

                string studentID;
                cout << "Enter Student ID: ";
                cin >> studentID;

                for (int i = 0; i < 3; i++) {
                    if (students[i].getID() == studentID) {
                        if (studentChoice == 1) {
                            string mentorID;
                            cout << "Enter Mentor ID: ";
                            cin >> mentorID;

                            for (int j = 0; j < 3; j++) {
                                if (mentors[j].getMentorID() == mentorID) {
                                    students[i].registerForMentorship(&mentors[j]);
                                    break;
                                }
                            }
                        } else if (studentChoice == 2) {
                            students[i].viewMentorDetails();
                        } else if (studentChoice == 3) {
                            string sportID;
                            cout << "Enter Sport ID: ";
                            cin >> sportID;

                            for (int j = 0; j < 3; j++) {
                                if (sports[j].getSportID() == sportID) {
                                    students[i].updateSportsInterest(&sports[j]);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                break;
            }

            case 4: {
                cout << "\n--- Mentor Menu ---\n";
                cout << "1. Assign a Learner\n";
                cout << "2. View Learners\n";
                cout << "3. Remove a Learner\n";
                cout << "4. Exit\n";
                cout << "Enter your choice: ";
                int mentorChoice;
                cin >> mentorChoice;

                if (mentorChoice == 4) break;

                string mentorID;
                cout << "Enter Mentor ID: ";
                cin >> mentorID;

                for (int i = 0; i < 3; i++) {
                    if (mentors[i].getMentorID() == mentorID) {
                        if (mentorChoice == 1) {
                            string studentID;
                            cout << "Enter Student ID: ";
                            cin >> studentID;

                            for (int j = 0; j < 3; j++) {
                                if (students[j].getID() == studentID) {
                                    mentors[i].assignLearner(&students[j]);
                                    break;
                                }
                            }
                        } else if (mentorChoice == 2) {
                            mentors[i].viewLearners();
                        } else if (mentorChoice == 3) {
                            string studentID;
                            cout << "Enter Student ID: ";
                            cin >> studentID;

                            for (int j = 0; j < 3; j++) {
                                if (students[j].getID() == studentID) {
                                    mentors[i].removeLearner(&students[j]);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                break;
            }

            case 5:
                displaySkills(skills, 6);
                displaySports(sports, 3);
                displayMentors(mentors, 3);
                displayStudents(students, 3);
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

