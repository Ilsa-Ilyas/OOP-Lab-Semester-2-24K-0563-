#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
    string firstName, lastName;
    double score1, score2, score3, score4, score5, average;

    cout << "Enter student's first name: ";
    cin >> firstName;
    
    cout << "Enter student's last name: ";
    cin >> lastName;

    cout << "Enter first test score: ";
    cin >> score1;

    cout << "Enter second test score: ";
    cin >> score2;

    cout << "Enter third test score: ";
    cin >> score3;

    cout << "Enter fourth test score: ";
    cin >> score4;

    cout << "Enter fifth test score: ";
    cin >> score5;

    average = (score1 + score2 + score3 + score4 + score5) / 5.0;

    cout << "\nStudent name: " << firstName << " " << lastName << endl;
    
    cout << fixed << setprecision(2); 
    cout << "Test scores: " << score1 << " " << score2 << " " << score3 << " " << score4 << " " << score5 << endl;
    cout << "Average test score: " << average << endl;

    return 0;
}
