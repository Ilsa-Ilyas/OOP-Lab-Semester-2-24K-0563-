#include <iostream>
#include <string>

using namespace std;

class Student {
protected:
    string name;

public:
    void setName(const string& n) {
        name = n;
    }

    string getName() const {
        return name;
    }

    virtual double getTuition(const string& status, int creditHours) = 0;

    virtual ~Student() {}
};

class GraduateStudent : public Student {
private:
    string researchTopic;

public:
    void setResearchTopic(const string& topic) {
        researchTopic = topic;
    }

    string getResearchTopic() const {
        return researchTopic;
    }

    double getTuition(const string& status, int creditHours) override {
        if (status == "undergraduate") {
            return creditHours * 200.0;
        } else if (status == "graduate") {
            return creditHours * 300.0;
        } else if (status == "doctoral") {
            return creditHours * 400.0;
        } else {
            cout << "Invalid status provided.\n";
            return 0.0;
        }
    }

    void displayInfo(const string& status, int creditHours) {
        cout << "Name: " << name << endl;
        cout << "Research Topic: " << researchTopic << endl;
        cout << "Status: " << status << ", Credit Hours: " << creditHours << endl;
        cout << "Total Tuition: $" << getTuition(status, creditHours) << endl;
    }
};

// Main function
int main() {
    GraduateStudent gs;
    gs.setName("Ilsa Ilyas");
    gs.setResearchTopic("Artificial Intelligence in Education");

    string status = "graduate";
    int creditHours = 9;

    gs.displayInfo(status, creditHours);

    return 0;
}
