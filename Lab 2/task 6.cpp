#include <iostream>
#include <string>

using namespace std;

struct Student {
    int id; 

    struct Subject {
        string name; 
    } subjects[5]; 
};

int main() {
    int N;
    cout << "Enter the number of students: ";
    cin >> N;

    Student* students = new Student[N];

    for (int i = 0; i < N; i++) {
        cout << "Enter ID for student " << i + 1 << ": ";
        cin >> students[i].id;
        cin.ignore();  
        
        for (int j = 0; j < 5; j++) {
            cout << "Enter subject " << j + 1 << " for student " << students[i].id << ": ";
            getline(cin, students[i].subjects[j].name);
        }
    }

    cout << "\nStudent Information:\n";
    for (int i = 0; i < N; i++) {
        cout << "Student ID: " << students[i].id << endl;
        cout << "Subjects:\n";
        for (int j = 0; j < 5; j++) {
            cout << "  - " << students[i].subjects[j].name << endl;
        }
        cout << endl;
    }

    delete[] students;

    return 0;
}
