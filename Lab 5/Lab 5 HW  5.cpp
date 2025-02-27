#include <iostream>
#include <string>
using namespace std;

class Car {
public:
    int eng_horsepower;
    int seating_capacity;
    int noSpeakers;

    void modifyCar() const {
        Car* nonConstThis = const_cast<Car*>(this);
        nonConstThis->seating_capacity = 7;        
        nonConstThis->noSpeakers = 12;  
    }
};

int main() {
    Car myCar;
    
    myCar.eng_horsepower = 9000;
    myCar.seating_capacity = 5;
    myCar.noSpeakers = 3;

    cout << "Before modification:\n";
    cout << "Horsepower: " << myCar.eng_horsepower << endl;
    cout << "Seating Capacity: " << myCar.seating_capacity << endl;
    cout << "# of Speakers: " << myCar.noSpeakers << endl;

    myCar.modifyCar();

    cout << "\nAfter modification:\n";
    cout << "Horsepower: " << myCar.eng_horsepower << " (Unchanged due to const function)" << endl;
    cout << "Seating Capacity: " << myCar.seating_capacity << endl;
    cout << "# of Speakers: " << myCar.noSpeakers << endl;

    return 0;
}

