#include <iostream>
using namespace std;

int main() {
    double kg, pounds;

    cout << "Enter weight in kilograms: ";
    cin >> kg;

    pounds = kg * 2.2;

    cout << "Weight in Kg: " << kg << " kg" << endl;
    cout << "Weight in lbs: " << pounds << " lbs" << endl;

    return 0;
}
