#include <iostream>
using namespace std;

class Student {
private:
    const string stdrollNumber; 
    
public:
    Student(string r) : stdrollNumber(r) {}

    void display() {
        cout << "Student's' Roll #: " << stdrollNumber << endl;
    }
};

int main() {
    string rN;
    cout << "Enter student's roll number: ";
    cin >> rN;

    Student s1(rN); 
    s1.display();

    return 0;
}
